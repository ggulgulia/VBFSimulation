#add appropriate path to src code from which the lib is to be made
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-g -std=c++11 -Wall -Werror -fno-elide-constructors")

add_library(
    VBF_RigidBody SHARED #name of target library
    VBF_RigidBody.hpp
    VBF_RigidBody.cpp
    VBF_StaticBody.hpp
    VBF_StaticBody.cpp
    VBF_KinematicBody.hpp
    VBF_KinematicBody.cpp
    VBF_Static_Cube.hpp
    VBF_Static_Cube.cpp
    VBF_Static_Sphere.hpp
    VBF_Static_Sphere.cpp
    LoadMeshFromSTL.hpp
    VBF_Kinematic_Cube.hpp
    VBF_Kinematic_Cube.cpp
    VBF_KinematicMesh.hpp
    VBF_KinematicMesh.cpp
    VBF_StaticMesh.hpp
    VBF_StaticMesh.cpp
    )

#make the library PUBLIC
target_include_directories(VBF_RigidBody PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
