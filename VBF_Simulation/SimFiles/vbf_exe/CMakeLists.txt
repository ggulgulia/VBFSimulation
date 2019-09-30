cmake_minimum_required(VERSION 3.2.3)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-std=c++17")
if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    list(APPEND flags "-g" "-fPIC" "-Wall" "-Werror")
elseif(${CMAKE_BUILD_TYPE} STREQUAL "Release")
    list(APPEND flags "-O3" "-fPIC" "-Wall" "-Werror")
endif()

add_executable(vbf_sim.out
              main.cpp
              )


target_link_libraries(vbf_sim.out PRIVATE VBF_Simulation)
