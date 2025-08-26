#!/usr/bin/env python3
import re
import argparse
import bisect
import matplotlib.pyplot as plt


# Parse the log, extracting id 0x200 and ids 0x201-0x204
def parse_log(fp):
    pattern = re.compile(r"\((?P<ts>\d+\.\d+)\)\s+\w+\s+(?P<id>[0-9A-Fa-f]+)#(?P<data>[0-9A-Fa-f]+)")
    data200 = {'ts': [], 'vals': []}
    data_ids = {0x201: {'ts': [], 'y': []},
                0x202: {'ts': [], 'y': []},
                0x203: {'ts': [], 'y': []},
                0x204: {'ts': [], 'y': []}}
    for line in fp:
        m = pattern.search(line)
        if not m:
            continue
        ts = float(m.group('ts'))
        idhex = int(m.group('id'), 16)
        data = m.group('data')
        if idhex == 0x200:
            # split into four 4-hex-digit groups and convert to signed int16
            vals = []
            for i in range(4):
                raw = int(data[i * 4:(i + 1) * 4], 16)
                if raw >= 0x8000:
                    raw -= 0x10000
                vals.append(raw)
            data200['ts'].append(ts)
            data200['vals'].append(vals)
        elif idhex in data_ids:
            # first four hex digits to uint16
            val = int(data[0:4], 16)
            data_ids[idhex]['ts'].append(ts)
            data_ids[idhex]['y'].append(val)
    return data200, data_ids


# get the most recent id200 value for group idx at time t
def get_id200_val(data200, t, idx):
    i = bisect.bisect_right(data200['ts'], t) - 1
    if i >= 0:
        return data200['vals'][i][idx]
    return None


# Plot four subplots, one per id
def plot_curves(data200, data_ids):
    fig, axs = plt.subplots(4, 1, sharex=True, figsize=(12, 10))
    for idx, id_hex in enumerate(sorted(data_ids.keys())):
        ts = data_ids[id_hex]['ts']
        y_id = data_ids[id_hex]['y']
        y200 = [get_id200_val(data200, t, idx) for t in ts]
        axs[idx].plot(ts, y_id, label=f'id {hex(id_hex)}')
        axs[idx].plot(ts, y200, label='id 0x200')
        axs[idx].set_ylabel('value')
        axs[idx].set_ylim(-20000, 20000)
        axs[idx].set_title(f'ID {hex(id_hex)} vs ID 0x200 group {idx}')
        axs[idx].legend()
    axs[-1].set_xlabel('timestamp')
    plt.tight_layout()
    plt.show()


# main entrypoint
if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Analyze CAN log and plot curves')
    parser.add_argument('logfile', help='path to CAN log file')
    args = parser.parse_args()
    with open(args.logfile, 'r') as fp:
        data200, data_ids = parse_log(fp)
    plot_curves(data200, data_ids)
