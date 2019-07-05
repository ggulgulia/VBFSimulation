#add appropriate path to src code from which the lib is to be made
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-g -std=c++14 -Wall -Werror -fno-elide-constructors")

add_library(
    VBF_KinematicBodies STATIC #name of target library
    #VBF_RigidBody.cpp
    VBF_KinematicBody.cpp
    VBF_Kinematic_Cube.cpp
    VBF_Kinematic_Sphere.cpp
    VBF_KinematicMesh.cpp
    )
target_link_libraries(VBF_KinematicBodies -L../VBF_RigidBody)
#make the library PUBLIC
target_include_directories(VBF_KinematicBodies PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
