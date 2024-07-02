cmake_minimum_required(VERSION 3.22)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(BOARD stm32f4_disco )

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(003_gpio_interrupt)

target_sources(app PRIVATE src/main.c)

