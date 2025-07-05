#ifndef SHIFT_HPP
#define SHIFT_HPP
#include <memory>
#include <OneMotor/Motor/DJI/M3508.hpp>

namespace Xeno
{
    class Shift
    {
    public:
        static Shift& getInstance();
        void posAngControl(float pos, float ang) const;
        Shift(Shift&) = delete;
        Shift& operator=(const Shift&) = delete;
        ~Shift() = default;

    private:
        Shift();
        std::unique_ptr<OneMotor::Motor::DJI::M3508<1, OneMotor::Motor::DJI::MotorMode::Position>> m3508_;
    };
}

#endif //SHIFT_HPP
