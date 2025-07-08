#include "Shift.hpp"

#include "CanDriverManager.hpp"

using OneMotor::Can::CanDriver;
using OneMotor::Motor::DJI::M3508;
using enum OneMotor::Motor::DJI::MotorMode;
using OneMotor::Control::PID_Params;

static constexpr PID_Params<float> POS_DEFAULT_PARAMS{
    .Kp = 2.0,
    .Ki = 0.005,
    .Kd = 0,
    .MaxOutput = 10000,
    .Deadband = 100,
    .IntegralLimit = 500,
};
static constexpr PID_Params<float> ANG_DEFAULT_PARAMS{
    .Kp = 3,
    .Ki = 0.2,
    .Kd = 0.1,
    .MaxOutput = 10000,
    .Deadband = 130,
    .IntegralLimit = 1000,
};


Xeno::Shift& Xeno::Shift::getInstance()
{
    static Shift _instance;
    return _instance;
}

void Xeno::Shift::posAngControl(const float pos, const float ang) const
{
    m3508_->setPosRef(pos);
    m3508_->setAngRef(ang);
}

Xeno::Shift::Shift()
{
    auto& driver = CanDriverManager::getInstance().getArmDriver();
    m3508_ = std::make_unique<M3508<1, Position>>(driver, POS_DEFAULT_PARAMS, ANG_DEFAULT_PARAMS);
    m3508_->enable().or_else([](const auto& e)
    {
        throw std::runtime_error(e.message);
    });
}
