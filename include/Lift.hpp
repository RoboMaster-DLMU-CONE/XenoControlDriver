#ifndef LIFTSTRETCH_HPP
#define LIFTSTRETCH_HPP
#include <memory>
#include <OneMotor/Motor/DJI/M3508.hpp>

namespace Xeno
{
    class Lift
    {
    public:
        static Lift& getInstance();
        void posAngControl(float pos, float ang) const noexcept;
        Lift(Lift&) = delete;
        Lift& operator=(const Lift&) = delete;
        ~Lift();

    private:
        Lift();
        std::unique_ptr<OneMotor::Can::CanDriver> driver_;
        std::unique_ptr<OneMotor::Motor::DJI::M3508<3, OneMotor::Motor::DJI::MotorMode::Position>> m3508_1;
        std::unique_ptr<OneMotor::Motor::DJI::M3508<4, OneMotor::Motor::DJI::MotorMode::Position>> m3508_2;
    };
}

#endif //LIFTSTRETCH_HPP
