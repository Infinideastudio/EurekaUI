cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 11)

include_directories(./../../src)

if (CMAKE_SYSTEM_NAME MATCHES Windows)
    add_definitions(-DDO_GET_GETFUNCTIONS)
    link_libraries(SDL2 SDL2main)
else()
    if (CMAKE_SYSTEM_NAME MATCHES Darwin)
        link_directories(/usr/local/lib)
        include_directories(/usr/local/include)
        add_definitions(-DDO_GET_GETFUNCTIONS)
        link_libraries(SDL2 SDL2main)
    else()
        link_libraries(SDL2 SDL2main GLESv2 EGL)
    endif ()
endif ()

aux_source_directory(./ SRC_HW)
link_libraries(eurekaui)

add_executable(SDLEGL2 ${SRC_HW})
