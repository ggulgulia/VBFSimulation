set(CMAKE_CXX_FLAGS "-std=c++14 -g -Wall -Werror -fno-elide-constructors")

add_executable(vbf_sim.out
              main.cpp
              )


target_link_libraries(vbf_sim.out PRIVATE vbf_simulation)
