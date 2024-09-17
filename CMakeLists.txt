cmake_minimum_required(VERSION 3.5.0)
project(Intuos VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(Intuos src/main.cpp src/Device.cpp src/Utilities.cpp)
target_link_libraries(Intuos PRIVATE Hid.lib SetupAPI.lib)
