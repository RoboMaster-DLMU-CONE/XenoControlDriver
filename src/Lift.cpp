#include "Lift.hpp"

#include <mutex>

#include "CanDriverManager.hpp"

using OneMotor::Can::CanDriver;
using OneMotor::Motor::DJI::M3508;
using enum OneMotor::Motor::DJI::MotorMode;
using OneMotor::Control::PID_Params;

using std::chrono_literals::operator ""ms;

static constexpr PID_Params<float> POS_DEFAULT_PARAMS{
    .Kp = 2.2,
    .Ki = 0.008,
    .Kd = 0,
    .MaxOutput = 5000,
    .Deadband = 50,
    .IntegralLimit = 150,
    .DerivativeFilterRC = 0.1,
    .OutputFilterRC = 0.02,
};
static constexpr PID_Params<float> ANG_DEFAULT_PARAMS{
    .Kp = 6.5,
    .Ki = 0.04,
    .Kd = 0.08,
    .MaxOutput = 18000,
    .Deadband = 200,
    .IntegralLimit = 1500,
    .DerivativeFilterRC = 0.08,
    .OutputFilterRC = 0.05,
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
    m3508_1->enable()
           .and_then([this] { return m3508_2->enable(); })
           .or_else([](const auto& e) -> tl::expected<void, OneMotor::Error>
           {
               throw std::runtime_error(e.message);
           });
}

