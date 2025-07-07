#include "MotorGuardRunner.hpp"

#include <subprocess.hpp>
static const std::string GUARD_PATH = XENO_MOTOR_GUARD_PATH;


namespace Xeno
{
    void MotorGuardRunner::startGuard()
    {
        static MotorGuardRunner _;
    }

    MotorGuardRunner::MotorGuardRunner()
    {
        try
        {
            auto _ = std::make_unique<subprocess::Popen>(
                std::vector{GUARD_PATH},
                subprocess::output{subprocess::STDOUT},
                subprocess::error{subprocess::STDERR}
            );
        }
        catch (...)
        {
            throw std::runtime_error("Failed to start Motor Guard.");
        }
    }
}
