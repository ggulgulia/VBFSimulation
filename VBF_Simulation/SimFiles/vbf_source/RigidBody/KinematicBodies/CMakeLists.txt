#add appropriate path to src code from which the lib is to be made
cmake_minimum_required(VERSION 3.2.3)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "-g -std=c++14 -Wall -Werror -fno-elide-constructors")


set(USE_LIBRARY ON)
set(BUILD_SHARED_LIBS OFF)
message(STATUS "Compile sources for VBF_KinematicBodes into a libary?" ${USE_LIBRARY})

LINK_LIBRARIES(OpenGLSupport OpenGLWindow GL GLU glut GLEW X11 pthread 
              BulletDynamics BulletCollision LinearMath Bullet3Common)

if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    message(STATUS "CMake build type for KinematicBodes library is Debug")
    list(APPEND flags "-g" "-Wall" "-Werror" "-fno-elide-constructors")
elseif(${CMAKE_BUILD_TYPE} STREQUAL "Release")
    message(STATUS "CMake build type for KinematicBodes library is Release")
    list(APPEND flags "-fPIC" "-Wall" "-Werror" "-fno-elide-constructors")
endif()

#Linux/Gcc Specific compiler flags
if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    message(STATUS "Compiling KinematicBody library on/for LINUX")
    list(APPEND flags "-Wextra" "-Wpedantic")
endif()


## append all KinematicBody source files in a list
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
add_library(VBF_KinematicBody 
            STATIC #name of target library
            ${_sources2}
            )
elseif(USE_LIBRARY AND BUILD_SHARED_LIBS)
    message(STATUS "compiling Rigid_Body sources to SHARED LIBRARY")
    add_library(VBF_KinematicBody
               SHARED
               ${_sources2}
               )
endif()

set_target_properties(VBF_KinematicBody
                      PROPERTIES
                      POSITION_INDEPENDENT_CODE 1)

target_compile_options(VBF_KinematicBody
                      PRIVATE
                      ${flags})

#link the new library with VBF_RididBody library
target_link_libraries(VBF_KinematicBody -L../VBF_RigidBody)

#make the library PUBLIC
target_include_directories(VBF_KinematicBody PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
