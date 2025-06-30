#ifndef CANDRIVERMANAGER_HPP
#define CANDRIVERMANAGER_HPP

#include <memory>
#include <OneMotor/Can/CanDriver.hpp>

namespace Xeno
{
    class CanDriverManager
    {
    public:
        static CanDriverManager& getInstance();
        [[nodiscard]] OneMotor::Can::CanDriver& getBaseDriver() const;
        [[nodiscard]] OneMotor::Can::CanDriver& getArmDriver() const;
        CanDriverManager(CanDriverManager&) = delete;
        CanDriverManager& operator=(const CanDriverManager&) = delete;
    private:
        CanDriverManager();
        std::unique_ptr<OneMotor::Can::CanDriver> base_driver;
        std::unique_ptr<OneMotor::Can::CanDriver> arm_driver;
    };
}

#endif //CANDRIVERMANAGER_HPP
