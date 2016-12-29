cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 11)

include_directories(./../../src)

if (CMAKE_SYSTEM_NAME MATCHES Darwin)
    link_libraries("-framework OpenGL")
endif ()

if (CMAKE_SYSTEM_NAME MATCHES Windows)
    link_libraries()
    add_definitions(-DDO_GET_GETFUNCTIONS)
    link_libraries(SDL2)
else()
    link_libraries(SDL2 GLESv2 EGL)
endif ()

add_definitions(-DSDL_MAIN_HANDLED)
aux_source_directory(./ SRC_HW)

add_executable(SDLEGL2 ${SRC_HW})
