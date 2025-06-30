#include "Stretch.hpp"
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
    .Kp = 20,
    .Ki = 2.5,
    .Kd = 1.0,
    .MaxOutput = 20000,
    .Deadband = 30,
    .IntegralLimit = 5000,
};

Xeno::Stretch& Xeno::Stretch::getInstance()
{
    static Stretch _instance;
    return _instance;
}

void Xeno::Stretch::posAngControl(const float pos, const float ang) const
{
    m3508_1->setPosRef(pos);
    m3508_1->setAngRef(ang);
    m3508_2->setPosRef(-pos);
    m3508_2->setAngRef(-ang);
}

Xeno::Stretch::Stretch()
{
    auto& driver = CanDriverManager::getInstance().getBaseDriver();
    m3508_1 = std::make_unique<M3508<1, Position>>(driver, POS_DEFAULT_PARAMS, ANG_DEFAULT_PARAMS);
    m3508_2 = std::make_unique<M3508<2, Position>>(driver, POS_DEFAULT_PARAMS, ANG_DEFAULT_PARAMS);
    auto result = m3508_1->enable();
    result = m3508_2->enable();
    if (!result) throw std::runtime_error(result.error());
}
