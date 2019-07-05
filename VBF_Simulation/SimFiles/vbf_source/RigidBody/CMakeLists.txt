#add appropriate path to src code from which the lib is to be made
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-g -std=c++14 -Wall -Werror -fno-elide-constructors")

LINK_LIBRARIES(ConvexDecomposition GIMPACTUtils HACD BulletInverseDynamicsUtils)

add_library(
    VBF_RigidBody STATIC #name of target library
    VBF_RigidBody.cpp
    )

#make the library PUBLIC
target_include_directories(VBF_RigidBody PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

add_subdirectory(DynamicBodies)
add_subdirectory(KinematicBodies)
add_subdirectory(StaticBodies)

