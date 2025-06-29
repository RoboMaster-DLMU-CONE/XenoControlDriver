cmake_minimum_required(VERSION 3.31)
project(XenoControlDriver)

set(CMAKE_CXX_STANDARD 23)

include(FetchContent)

find_package(OneMotor QUIET)

if (NOT OneMotor_FOUND)
    message(STATUS "本地未找到 OneMotor 包，尝试从 GitHub 获取...")
    FetchContent_Declare(
            OneMotor_fetched
            GIT_REPOSITORY "https://github.com/RoboMaster-DLMU-CONE/OneMotor"
            GIT_TAG "main"
    )
    FetchContent_MakeAvailable(OneMotor_fetched)
else ()
    message(STATUS "已找到 OneMotor 版本 ${OneMotor_VERSION}")
endif ()

file(GLOB_RECURSE SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")
add_library(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} PRIVATE OneMotor::OneMotor)

add_executable(XenoControlExample example/main.cpp)
target_link_libraries(XenoControlExample PUBLIC ${PROJECT_NAME})