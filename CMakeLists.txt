cmake_minimum_required(VERSION 4.0)
project(TimeCalkV2_0 C)

set(CMAKE_C_STANDARD 11)

add_executable(TimeCalkV2_0 main.c timecalk.h timecalk.c string-functions.h string-functions.c)
