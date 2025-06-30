#include "CanDriverManager.hpp"

Xeno::CanDriverManager& Xeno::CanDriverManager::getInstance()
{
    static CanDriverManager _instance;
    return _instance;
}

OneMotor::Can::CanDriver& Xeno::CanDriverManager::getBaseDriver() const
{
    return *base_driver;
}

OneMotor::Can::CanDriver& Xeno::CanDriverManager::getArmDriver() const
{
    return *arm_driver;
}

Xeno::CanDriverManager::CanDriverManager()
{
    base_driver = std::make_unique<OneMotor::Can::CanDriver>("can0");
    arm_driver = std::make_unique<OneMotor::Can::CanDriver>("can1");
    if (const auto result = base_driver->open(); !result)
    {
        throw std::runtime_error(result.error());
    }
    if (const auto result = arm_driver->open(); !result)
    {
        throw std::runtime_error(result.error());
    }
}
