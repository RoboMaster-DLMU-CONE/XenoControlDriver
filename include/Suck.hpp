#ifndef SUCK_HPP
#define SUCK_HPP
#include <memory>
#include <OneMotor/Motor/DJI/M3508.hpp>

namespace Xeno
{
    class Suck
    {
    public:
        static Suck& getInstance();
        Suck(Suck&) = delete;
        void posAngControl(float pos, float ang) const;
        Suck& operator=(const Suck&) = delete;

    private:
        Suck();
        std::unique_ptr<OneMotor::Motor::DJI::M3508<2, OneMotor::Motor::DJI::MotorMode::Position>> m3508_;
    };
}

#endif //SUCK_HPP
