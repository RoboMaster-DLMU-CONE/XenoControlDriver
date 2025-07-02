add_subdirectory(OnePacket)
add_subdirectory(serialib)

add_executable(XenoControlExample_Serial main.cpp)
target_link_libraries(XenoControlExample_Serial PRIVATE ${PROJECT_NAME} OnePacket serialib)