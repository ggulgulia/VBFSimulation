cmake_minimum_required(VERSION 3.2.3)
project(VBF_iwb_TUM CXX) 
enable_testing()

set(CMAKE_CXX_FLAGS "-g -std=c++17 -Wall -Werror -Wextra -Wpedantic")

find_package(PkgConfig REQUIRED)

pkg_check_modules(gtest REQUIRED gtest>=1.8.1)


include_directories(${gtest_INCLUDE_DIRS})

add_executable(vbf_unit_test.out 
                main_test.cpp 
               )

target_link_libraries(vbf_unit_test.out VBF_Simulation -L VBF_RigidBody
                      ${gtest_LIBRARIES})

add_test(NAME test COMMAND vbf_unit_test)
