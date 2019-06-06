#add appropriate path to src code from which the lib is to be made
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-g -std=c++11 -Wall -Werror -fno-elide-constructors")

add_library(
    VBF_DynamicBodies SHARED #name of target library
    VBF_DynamicBody.cpp
    VBF_Dynamic_Cube.cpp
    VBF_Dynamic_Sphere.cpp
    VBF_DynamicMesh.cpp
    )

target_link_libraries(VBF_DynamicBodies -L../VBF_RigidBody)

#make the library PUBLIC
target_include_directories(VBF_DynamicBodies PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
