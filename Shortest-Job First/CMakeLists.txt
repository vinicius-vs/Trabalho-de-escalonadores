cmake_minimum_required(VERSION 3.22)
project(Shortest_Job_First)

set(CMAKE_CXX_STANDARD 14)

add_executable(Shortest_Job_First driver.c CPU.c CPU.h list.c list.h schedule_sjf.h schedule_sfj.c task.h)
