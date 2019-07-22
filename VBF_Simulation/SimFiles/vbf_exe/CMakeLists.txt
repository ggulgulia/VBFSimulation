cmake_minimum_required(VERSION 3.2.3)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-std=c++14 -g -Wall -Werror -fno-elide-constructors")

add_executable(vbf_sim.out
              main.cpp
              )


target_link_libraries(vbf_sim.out PRIVATE VBF_Simulation)
