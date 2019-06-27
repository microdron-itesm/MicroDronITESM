cmake_minimum_required(VERSION 3.0)
project(microdron)

#include (ProcessorCount)
#ProcessorCount(N)

#SET(CMAKE_C_COMPILER "/opt/microchip/xc32/v2.10/bin/xc32-g++")
#SET(CMAKE_CXX_COMPILER "/opt/microchip/xc32/v2.10/bin/xc32-gcc")


#add_custom_target(build)
#add_custom_command(TARGET "build" COMMAND cd ${PROJECT_SOURCE_DIR}/MicroDron.X && make build -j${N})
#
#add_custom_target("clean_project")
#add_custom_command(TARGET "clean_project" COMMAND cd ${PROJECT_SOURCE_DIR}/MicroDron.X && make clean)
#
#add_custom_target("generate_makefile")
#add_custom_command(TARGET "generate_makefile" COMMAND cd ${PROJECT_SOURCE_DIR} && prjMakefilesGenerator MicroDron.X -v)

#include_directories(/opt/microchip/xc32/v2.10/pic32mx/include)
#include_directories(../../Harmony)
#include_directories(../../Harmony/framework)
include_directories(microdron src/system_config/default)
#include_directories(src/)
#include_directories(src/drone_control)