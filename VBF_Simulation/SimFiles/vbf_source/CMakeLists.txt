cmake_minimum_required(VERSION 3.2.3)
set(CMAKE_CXX_STANDARD 14)

## set up of build specific compiler options 
## goal is to have strict compiler checks even in 
##debug mode 

set(CMAKE_CXX_FLAGS "-std=c++14")
message(STATUS "compilation of VBF_Simulation components to library")
if(${CMAKE_BUILD_TYPE}  STREQUAL "Debug")
    message(STATUS "CMAKE build type is DEBUG ")
    list(APPEND flags "-g" "-Wall" "-Werror" "-fno-elide-constructors")
elseif(${CMAKE_BUILD_TYPE} STREQUAL "Release")
    message(STATUS "CMAKE build type is RELEASE ")
    list(APPEND flags "-fPIC" "-Wall" "-Werror" "-fno-elide-constructors" )
endif()

## set Linux Specific flags
if(UNIX)
    message(STATUS "Compiling VBF_Simulation library for Unix like system")
    list(APPEND flags "-Wextra" "-Wpedantic")
endif(UNIX)

message(STATUS "CMAKE_BUILD_TYPE is ${CMAKE_BUILD_TYPE}")

add_subdirectory(RigidBody)

LINK_LIBRARIES(OpenGLSupport OpenGLWindow GL GLU glut GLEW X11 pthread 
              BulletDynamics BulletCollision LinearMath Bullet3Common)

## append all DynamicBody source files in a list
set(USE_LIBRARY ON)
set(BUILD_SHARED_LIBS OFF)

## append all DynamicBody source files in a list
list(APPEND
    _sources3
    VBF_World.cpp
    VBF_CommonPhysics.cpp
    VBF_SimLoop.hpp
    RigidBody/KinematicBodies/VBF_KinematicMesh.cpp ##need to resolve circular dependency
    )
if(USE_LIBRARY AND NOT BUILD_SHARED_LIBS)

    message(STATUS "Compiling VBF Simulation components to a STATIC LIBRARY")
    add_library(VBF_Simulation
                ${_sources3}
                  )
elseif(USE_LIBRARY AND BUILD_SHARED_LIBS)

    message(STATUS "Compiling VBF Simulation components to a SHARED LIBRARY")
    ADD_LIBRARY(VBF_Simulation
                SHARED 
                ${_sources3}
                  )
endif()

target_compile_options(VBF_Simulation
                      PRIVATE
                      ${flags})

#link the current library with other VBF rigid body libraries
target_link_libraries(VBF_Simulation PUBLIC VBF_RigidBody VBF_StaticBodies VBF_KinematicBodies VBF_DynamicBodies)

#make the library available publicly
target_include_directories(VBF_Simulation PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
