#include <iostream>
#include <limits>

#include "Arm.hpp"
#include "Lift.hpp"
#include "Shift.hpp"
#include "Stretch.hpp"

void clearInputBuffer()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main()
{
    float lift{};
    float stretch{};
    float r1{};
    float r2{};
    float r3{};

    std::unordered_map<std::string, float*> commandMap;
    commandMap["lift"] = &lift;
    commandMap["stretch"] = &stretch;
    commandMap["r1"] = &r1;
    commandMap["r2"] = &r2;
    commandMap["r3"] = &r3;

    std::string command;
    float value;

    std::cout << "Enter 'exit' to quit the program.\n";
    while (true)
    {
        // Get command
        std::cout << "\nEnter command (lift/stretch/shift/suck_rotate/r1/r2/r3): ";
        std::cin >> command;

        if (command == "exit")
        {
            break;
        }

        // Check if command is valid
        if (!commandMap.contains(command))
        {
            std::cout << "Invalid command. Please try again.\n";
            clearInputBuffer();
            continue;
        }

        // Get value
        std::cout << "Enter value for " << command << ": ";
        if (!(std::cin >> value))
        {
            std::cout << "Invalid value. Please enter a number.\n";
            clearInputBuffer();
            continue;
        }

        // Update value
        *commandMap[command] = value;

        // Display current state
        std::cout << "\nCurrent state:\n";
        std::cout << "  lift: " << lift << "\n";
        std::cout << "  stretch: " << stretch << "\n";
        // std::cout << "  shift: " << packet.shift << "\n";
        // std::cout << "  suck_rotate: " << packet.suck_rotate << "\n";
        std::cout << "  r1: " << r1 << "\n";
        std::cout << "  r2: " << r2 << "\n";
        std::cout << "  r3: " << r3 << "\n";
        Xeno::Lift::getInstance().posAngControl(lift, 80);
        Xeno::Stretch::getInstance().posAngControl(stretch, 80);
        // auto _ = Xeno::Arm::getInstance().posVelControl(1, r1, 2);
        // _ = Xeno::Arm::getInstance().posVelControl(2, r2, 2);
        // _ = Xeno::Arm::getInstance().posVelControl(3, r3, 2);
    }

    std::cout << "Program terminated.\n";
    return 0;
}
