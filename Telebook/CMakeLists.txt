cmake_minimum_required(VERSION 3.12)
project(Telebook C)

set(CMAKE_C_STANDARD 11)

add_executable(Telebook main.c telbook.c telbook.h)