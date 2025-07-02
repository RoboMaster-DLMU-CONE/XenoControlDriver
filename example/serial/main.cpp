#include <Arm.hpp>
#include <filesystem>
#include <Lift.hpp>
#include <Suck.hpp>
#include <Shift.hpp>
#include <packets/XenoSlavePacket.h>
#include <serialib.h>

#include <format>
#include <thread>
#include <iostream>
#include <regex>

#include "deserialize.h"

#define BAUD_RATE 115200

XenoSlavePacket packet{};

std::string findLatestTtyACM()
{
    std::vector<int> acmNumbers;
    const std::regex acmRegex(R"(ttyACM(\d+))");
    for (const auto& entry : std::filesystem::directory_iterator("/dev"))
    {
        std::string filename = entry.path().filename().string();
        if (std::smatch match; std::regex_match(filename, match, acmRegex))
        {
            acmNumbers.push_back(std::stoi(match[1].str()));
        }
    }

    if (acmNumbers.empty())
    {
        return "";
    }

    const int maxACM = *std::max_element(acmNumbers.begin(), acmNumbers.end());
    return "/dev/ttyACM" + std::to_string(maxACM);
}

void clearScreen()
{
    std::cout << "\033[2J\033[H" << std::flush;
}

int main()
{
    init_xeno_slave_packet(&packet);
    serialib serial;

    const std::string latestPort = findLatestTtyACM();
    if (latestPort.empty())
    {
        std::cerr << "No ttyACM ports found" << std::endl;
        return 1;
    }
    if (serial.openDevice(latestPort.c_str(), BAUD_RATE) != 1)
    {
        std::cerr << "Error opening serial port" << std::endl;
    }

    constexpr size_t PACKET_SIZE = 33;
    std::vector<uint8_t> dataPacket(PACKET_SIZE);

    while (true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(3));

        if (const int bytesRead = serial.readBytes(dataPacket.data(), PACKET_SIZE, 30); bytesRead > 0)
        {
            clearScreen();
            std::cout << "Received " << bytesRead << " bytes" << std::endl;
            deserialize(dataPacket.data(), &packet);
            float lift = packet.lift;
            float stretch = packet.stretch;
            float shift = packet.shift;
            float suck_rotate = packet.suck_rotate;
            float r1 = packet.r1;
            float r2 = packet.r2;
            float r3 = packet.r3;

            std::cout << std::format("lift: {} \n stretch: {}, shift: {} \n suck_rotate: {} \n r1 {} r2 {} r3 {}\n",
                                     lift, stretch, shift,
                                     suck_rotate, r1, r2, r3);
        }
    }

    return 0;
}
