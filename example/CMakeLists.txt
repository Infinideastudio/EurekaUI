cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 11)

include_directories(../src)

link_libraries("-framework opengl" SDL2 glew eurekaui)

add_executable(helloworld helloworld.cpp)
