cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

aux_source_directory(. SOURCE_FILES)
aux_source_directory(./drivers/video SOURCE_FILES)
add_library(eurekaui ${SOURCE_FILES})

install(TARGETS eurekaui
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib/static
        )
install(DIRECTORY eurekaui DESTINATION include)

