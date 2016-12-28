cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 11)

include_directories(../src)

if (CMAKE_SYSTEM_NAME MATCHES Darwin)
    link_libraries("-framework OpenGL")
endif ()

if (CMAKE_SYSTEM_NAME MATCHES Windows)
    link_libraries("opengl32")
endif ()

link_libraries(SDL2 GLEW eurekaui)

add_executable(helloworld helloworld.cpp)
