cmake_minimum_required(VERSION 3.22)
project(untitled)

set(CMAKE_CXX_STANDARD 14)

add_executable(untitled driver.c CPU.c CPU.h list.c list.h schedule_rr.h schedule_rr.c task.h)
