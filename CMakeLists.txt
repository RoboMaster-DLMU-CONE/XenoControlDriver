cmake_minimum_required(VERSION 3.20)
project(XenoControlDriver VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

find_package(OneMotor QUIET)

if (NOT OneMotor_FOUND)
    FetchContent_Declare(
            OneMotor_fetched
            GIT_REPOSITORY "https://github.com/RoboMaster-DLMU-CONE/OneMotor"
            GIT_TAG "main"
    )
    FetchContent_MakeAvailable(OneMotor_fetched)
endif ()

add_subdirectory(src/MotorGuard)

file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")
add_library(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} PUBLIC OneMotor::OneMotor)
add_dependencies(${PROJECT_NAME} XenoMotorGuard)
target_compile_definitions(${PROJECT_NAME} PRIVATE
        XENO_MOTOR_GUARD_PATH="$<TARGET_FILE:XenoMotorGuard>"
)

add_subdirectory(example)