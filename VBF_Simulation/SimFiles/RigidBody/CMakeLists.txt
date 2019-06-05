#add appropriate path to src code from which the lib is to be made
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-g -std=c++14 -Wall -Werror -fno-elide-constructors")

add_library(
    VBF_RigidBody SHARED #name of target library
    VBF_RigidBody.cpp
    VBF_DynamicBody.cpp
    VBF_KinematicBody.cpp
    VBF_StaticBody.cpp
    VBF_Dynamic_Cube.cpp
    VBF_Static_Cube.cpp
    VBF_Kinematic_Cube.cpp
    VBF_Dynamic_Sphere.cpp
    VBF_Kinematic_Sphere.cpp
    VBF_Static_Sphere.cpp
    VBF_KinematicMesh.cpp
    VBF_StaticMesh.cpp
    )

#make the library PUBLIC
target_include_directories(VBF_RigidBody PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
