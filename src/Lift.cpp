#include "Lift.hpp"

#include <csignal>
#include <mutex>

#include "CanDriverManager.hpp"

using OneMotor::Can::CanDriver;
using OneMotor::Motor::DJI::M3508;
using enum OneMotor::Motor::DJI::MotorMode;
using OneMotor::Control::PID_Params;

using std::chrono_literals::operator ""ms;

static constexpr PID_Params<float> POS_DEFAULT_PARAMS{
    .Kp = 5,
    .Ki = 0.2,
    .Kd = 0,
    .MaxOutput = 3000,
    .Deadband = 100,
    .IntegralLimit = 500,
};
static constexpr PID_Params<float> ANG_DEFAULT_PARAMS{
    .Kp = 12,
    .Ki = 2.0,
    .Kd = 0.1,
    .MaxOutput = 20000,
    .Deadband = 300,
    .IntegralLimit = 3000,
};

Xeno::Lift& Xeno::Lift::getInstance()
{
    static Lift _instance;
    return _instance;
}

void Xeno::Lift::posAngControl(const float pos, const float ang) const noexcept
{
    m3508_1->setPosRef(pos);
    m3508_1->setAngRef(ang);
    m3508_2->setPosRef(-pos);
    m3508_2->setAngRef(-ang);
}

Xeno::Lift::Lift()
{
    auto& driver = CanDriverManager::getInstance().getBaseDriver();
    m3508_1 = std::make_unique<M3508<3, Position>>(driver, POS_DEFAULT_PARAMS, ANG_DEFAULT_PARAMS);
    m3508_2 = std::make_unique<M3508<4, Position>>(driver, POS_DEFAULT_PARAMS, ANG_DEFAULT_PARAMS);
    auto result = m3508_1->enable();
    result = m3508_2->enable();
    if (!result) throw std::runtime_error(result.error());
}

