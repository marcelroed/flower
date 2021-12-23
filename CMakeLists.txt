cmake_minimum_required(VERSION 3.20)
project(flower)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)


file(GLOB flower_SRC
        "src/*.h"
        "src/*.cpp"
        )

add_executable(flower ${flower_SRC})
target_link_libraries(flower sfml-system sfml-window sfml-graphics sfml-network sfml-audio)
