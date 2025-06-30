#include "Suck.hpp"

#include "CanDriverManager.hpp"

using OneMotor::Can::CanDriver;
using OneMotor::Motor::DJI::M3508;
using enum OneMotor::Motor::DJI::MotorMode;
using OneMotor::Control::PID_Params;

static constexpr PID_Params<float> POS_DEFAULT_PARAMS{
    .Kp = 5,
    .Ki = 0,
    .Kd = 0,
    .MaxOutput = 3000,
    .Deadband = 30,
    .IntegralLimit = 500,
};
static constexpr PID_Params<float> ANG_DEFAULT_PARAMS{
    .Kp = 8,
    .Ki = 0.2,
    .Kd = 0.1,
    .MaxOutput = 10000,
    .Deadband = 30,
    .IntegralLimit = 1000,
};

Xeno::Suck& Xeno::Suck::getInstance()
{
    static Suck _instance;
    return _instance;
}

void Xeno::Suck::posAngControl(const float pos, const float ang) const
{
    m3508_->setPosRef(pos);
    m3508_->setAngRef(ang);
}

Xeno::Suck::Suck()
{
    auto& driver = CanDriverManager::getInstance().getArmDriver();
    m3508_ = std::make_unique<M3508<2, Position>>(driver, POS_DEFAULT_PARAMS, ANG_DEFAULT_PARAMS);
    if (const auto result = m3508_->enable(); !result)
    {
        throw std::runtime_error(result.error());
    }
}
