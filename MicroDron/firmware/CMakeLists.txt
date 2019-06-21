cmake_minimum_required(VERSION 3.0)

include (ProcessorCount)
ProcessorCount(N)

add_custom_target(build)
add_custom_command(TARGET "build" COMMAND cd ${PROJECT_SOURCE_DIR}/MicroDron.X && make build -j${N})

add_custom_target("clean_project")
add_custom_command(TARGET "clean_project" COMMAND cd ${PROJECT_SOURCE_DIR}/MicroDron.X && make clean)

add_custom_target("generate_makefile")
add_custom_command(TARGET "generate_makefile" COMMAND cd ${PROJECT_SOURCE_DIR} && prjMakefilesGenerator MicroDron.X -v)
