#ifndef ARM_HPP
#define ARM_HPP
#include <expected>
#include <memory>
#include <OneMotor/Motor/DM/J4310.hpp>

namespace Xeno
{
    class Arm
    {
        using Result = std::expected<void, std::string>;

    public:
        static Arm& getInstance();
        [[nodiscard]] Result posVelControl(uint8_t id, float position, float velocity) const;
        Arm(Arm&) = delete;
        Arm& operator=(const Arm&) = delete;
        ~Arm();

    private:
        Arm();
        std::unique_ptr<OneMotor::Can::CanDriver> driver_;
        std::array<std::unique_ptr<OneMotor::Motor::DM::J4310>, 3> j4310_array_;
    };
}

#endif //ARM_HPP
