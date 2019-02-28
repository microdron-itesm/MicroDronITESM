cmake_minimum_required(VERSION 3.13)
project(ControlTests)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5 REQUIRED network audio graphics window system)

set(TARGET_LIBS sfml-graphics sfml-window sfml-system pthread GL)
link_libraries(${TARGET_LIBS})

file(GLOB_RECURSE ControlTests_SRC
        "src/*.h"
        "src/*.cpp"
        "src/**/*.cpp"
        "src/**/*.hpp"
        "src/**/*.h"
        "src/*.hpp"
        )


add_executable(ControlTests ${ControlTests_SRC} src/main.cpp src/DroneDrawable.cpp src/DroneDrawable.h src/PropellerDrawable.cpp src/PropellerDrawable.h)