#include "Arm.hpp"

using OneMotor::Motor::DM::J4310;
using OneMotor::Can::CanDriver;
using Result = std::expected<void, std::string>;

Xeno::Arm& Xeno::Arm::getInstance()
{
    static Arm _instance;
    return _instance;
}

Result Xeno::Arm::posVelControl(const uint8_t id, const float position, const float velocity) const
{
    return j4310_array_[id - 1]->posVelControl(position, velocity);
}

Xeno::Arm::Arm()
{
    driver_ = std::make_unique<CanDriver>("can0");
    if (const auto result = driver_->open(); !result)
    {
        throw std::runtime_error(result.error());
    }
    for (int i = 0; i < 3; i++)
    {
        j4310_array_[i] = std::make_unique<J4310>(*driver_, 0x51 + i, 0x41 + i);
        auto result = j4310_array_[i]->enable();
        result = j4310_array_[i]->setZeroPosition();
        if (!result) throw std::runtime_error(result.error());
    }
}

Xeno::Arm::~Arm() = default;
