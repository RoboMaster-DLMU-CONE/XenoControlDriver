#include "Arm.hpp"

using OneMotor::Motor::DM::J4310;
using OneMotor::Can::CanDriver;

Xeno::Arm& Xeno::Arm::getInstance()
{
    static Arm _instance;
    return _instance;
}

tl::expected<void, OneMotor::Error> Xeno::Arm::posVelControl(const uint8_t id, const float position,
                                                             const float velocity) const
{
    return j4310_array_[id - 1]->posVelControl(position, velocity);
}

Xeno::Arm::Arm()
{
    driver_ = std::make_unique<CanDriver>("can0");
    (void)driver_->open().or_else([](const auto& e)
    {
        throw std::runtime_error(e.message);
    });
    for (int i = 0; i < 3; i++)
    {
        j4310_array_[i] = std::make_unique<J4310>(*driver_, 0x51 + i, 0x41 + i);
        (void)j4310_array_[i]->enable().and_then([&] { return j4310_array_[i]->setZeroPosition(); });
    }
}

Xeno::Arm::~Arm() = default;
