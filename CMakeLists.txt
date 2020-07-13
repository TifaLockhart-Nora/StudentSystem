cmake_minimum_required(VERSION 2.8.0)
project(Demo)
aux_source_directory(./src SOURCE)
include_directories(./include)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../release)
add_definitions("-g" "-Wall")
add_executable(StuendV1 ${SOURCE})

