#include <Arm.hpp>
#include <Lift.hpp>
#include <Suck.hpp>
#include <Shift.hpp>
#include <packets/XenoSlavePacket.h>
#include <serialib.h>

#include <format>
#include <thread>

#include "deserialize.h"

#define SERIAL_PORT "/dev/ttyACM0"
#define SERIAL_PORT_2 "/dev/ttyACM1"
#define BAUD_RATE 115200

XenoSlavePacket packet{};

int main()
{
    init_xeno_slave_packet(&packet);
    serialib serial;
    if (serial.openDevice(SERIAL_PORT, BAUD_RATE) != 1)
    {
        if (serial.openDevice(SERIAL_PORT_2, BAUD_RATE) != 1)
        {
            std::cerr << "Error opening serial port" << std::endl;
            return 1;
        }
    }

    constexpr size_t PACKET_SIZE = 33;
    std::vector<uint8_t> dataPacket(PACKET_SIZE);

    while (true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(3));

        if (const int bytesRead = serial.readBytes(dataPacket.data(), PACKET_SIZE, 30); bytesRead > 0)
        {
            std::cout << "Received " << bytesRead << " bytes" << std::endl;
            deserialize(dataPacket.data(), &packet);
            float lift = packet.lift;
            float stretch = packet.stretch;
            float shift = packet.shift;
            float suck_rotate = packet.suck_rotate;
            float r1 = packet.r1;
            float r2 = packet.r2;
            float r3 = packet.r3;

            std::cout << std::format("lift: {} \n stretch: {}, shift: {} \n suck_rotate: {} \n r1 {} r2 {} r3 {}",
                                     lift, stretch, shift,
                                     suck_rotate, r1, r2, r3);
        }
    }

    return 0;
}
