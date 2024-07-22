cmake_minimum_required(VERSION 3.22)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(BOARD stg_800 )

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(008_pwm_tutoria)

target_sources(app PRIVATE src/main.c)


