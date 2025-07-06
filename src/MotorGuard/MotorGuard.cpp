#include <thread>
#include <OneMotor/Motor/DJI/MotorGuard.hpp>

using std::chrono_literals::operator ""s;
using OneMotor::Motor::DJI::MotorGuard;

[[noreturn]] int main()
{
    MotorGuard::getInstance().guard({{"can0", {}}, {"can1", {}}});
    while (true)
    {
        std::this_thread::sleep_for(1s);
    }
}
