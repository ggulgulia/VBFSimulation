#add appropriate path to src code from which the lib is to be made
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-g -std=c++14 -Wall -Werror -fno-elide-constructors")


set(USE_LIBRARY ON)
set(BUILD_SHARED_LIBS OFF)
message(STATUS "Compile sources for VBF_KinematicBody into a libary?" ${USE_LIBRARY})

LINK_LIBRARIES(OpenGLSupport OpenGLWindow GL GLU glut GLEW X11 pthread 
              BulletDynamics BulletCollision LinearMath Bullet3Common)


## append all DynamicBody source files in a list
list(APPEND
    _sources2
    VBF_KinematicBody.cpp
    VBF_Kinematic_Cube.cpp
    VBF_Kinematic_Sphere.cpp
    VBF_Kinematic_Cylinder.cpp
    VBF_KinematicMesh.cpp
    )

if(USE_LIBRARY AND NOT BUILD_SHARED_LIBS)
    message(STATUS "compiling Kinematic_Body sources to STATIC LIBRARY")
add_library(VBF_KinematicBodies 
            STATIC #name of target library
            ${_sources2}
            )
elseif(USE_LIBRARY AND BUILD_SHARED_LIBS)
    message(STATUS "compiling Rigid_Body sources to SHARED LIBRARY")
    add_library(VBF_KinematicBodies
               SHARED
               ${_sources2}
               )
endif()

#link the new library with VBF_RididBody library
target_link_libraries(VBF_KinematicBodies -L../VBF_RigidBody)

#make the library PUBLIC
target_include_directories(VBF_KinematicBodies PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
