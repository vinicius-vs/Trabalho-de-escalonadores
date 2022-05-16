cmake_minimum_required(VERSION 3.22)
project(Round_Rubi_FIFO)

set(CMAKE_CXX_STANDARD 14)

add_executable(Round_Rubi_FIFO driver.c CPU.c CPU.h list.c list.h schedule_rr_FIFO.h schedule_rr_FIFO.c task.h)
