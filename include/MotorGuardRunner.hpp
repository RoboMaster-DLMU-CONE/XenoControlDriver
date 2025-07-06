#ifndef MOTORGUARDRUNNER_HPP
#define MOTORGUARDRUNNER_HPP

namespace Xeno
{
    class MotorGuardRunner
    {
    public:
        static void startGuard();
        MotorGuardRunner(MotorGuardRunner&) = delete;
        MotorGuardRunner& operator=(const MotorGuardRunner&) = delete;

    private:
        MotorGuardRunner();
    };
}

#endif //MOTORGUARDRUNNER_HPP
