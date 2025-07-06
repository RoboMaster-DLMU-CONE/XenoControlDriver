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
                subprocess::output{subprocess::PIPE},
                subprocess::error{subprocess::PIPE}
            );
        }
        catch (...)
        {
            throw std::runtime_error("Failed to start Motor Guard.");
        }
    }
}
