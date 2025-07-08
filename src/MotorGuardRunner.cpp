#include "MotorGuardRunner.hpp"

#include <stdexcept>
#include <unistd.h>
#include <sys/types.h>

namespace Xeno
{
    void MotorGuardRunner::startGuard()
    {
        static MotorGuardRunner _;
    }

    MotorGuardRunner::MotorGuardRunner()
    {
        const pid_t pid = fork();
        if (pid < 0)
        {
            throw std::runtime_error("Failed to fork process for Motor Guard.");
        }
        if (pid == 0)
        {
            if (setsid() < 0)
            {
                _exit(EXIT_FAILURE);
            }

            execl(XENO_MOTOR_GUARD_PATH, XENO_MOTOR_GUARD_PATH, nullptr);
            _exit(EXIT_FAILURE);
        }
    }
}

