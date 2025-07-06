add_executable(XenoMotorGuard
        MotorGuard.cpp
)
target_link_libraries(XenoMotorGuard PRIVATE OneMotor::OneMotor)