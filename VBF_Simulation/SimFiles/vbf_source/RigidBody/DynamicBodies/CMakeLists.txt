#add appropriate path to src code from which the lib is to be made
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-g -std=c++11 -Wall -Werror -fno-elide-constructors")

set(USE_LIBRARY ON)
set(BUILD_SHARED_LIBS OFF)
message(STATUS "Compile sources for VBF_KinematicBody into a libary? " ${USE_LIBRARY})

LINK_LIBRARIES(OpenGLSupport OpenGLWindow GL GLU glut GLEW X11 pthread 
              BulletDynamics BulletCollision LinearMath Bullet3Common)


## append all DynamicBody source files in a list
list(APPEND
    _sources3
    VBF_DynamicBody.cpp
    VBF_Dynamic_Cube.cpp
    VBF_Dynamic_Cylinder.cpp
    VBF_Dynamic_Sphere.cpp
    VBF_DynamicMesh.cpp
    )


if(USE_LIBRARY AND NOT BUILD_SHARED_LIBS)
message(STATUS "compiling Kinematic_Body sources to static library")
add_library(VBF_DynamicBodies 
            STATIC #name of target library
            ${_sources3}
            )
elseif(USE_LIBRARY AND BUILD_SHARED_LIBS)
message(STATUS "compiling Rigid_Body sources to shared library")
    add_library(VBF_DynamicBodies
               SHARED
               ${_sources3}
               )
endif()

target_link_libraries(VBF_DynamicBodies -L../VBF_RigidBody)

#make the library PUBLIC
target_include_directories(VBF_DynamicBodies PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
