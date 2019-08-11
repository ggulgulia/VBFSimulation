cmake_minimum_required(VERSION 3.2.3)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

## set up of build specific compiler options 
## goal is to have strict compiler checks even in 
##debug mode 

set(CMAKE_CXX_FLAGS "-std=c++14")
message(STATUS "compilation of VBF_Simulation components to library")
if(${CMAKE_BUILD_TYPE}  STREQUAL "Debug")
    list(APPEND flags "-g" "-Wall" "-Werror" "-fno-elide-constructors")
elseif(${CMAKE_BUILD_TYPE} STREQUAL "Release")
    list(APPEND flags "-fPIC" "-Wall" "-Werror" "-fno-elide-constructors" )
endif()

## set Linux Specific flags
if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    message(STATUS "Compiling VBF_Simulation library on/for LINUX")
    list(APPEND flags "-Wextra" "-Wpedantic")
endif()

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
    VBF_ReadInputData.cpp
    VBF_ReadInputData.hpp
    RigidBody/KinematicBodies/VBF_KinematicMesh.cpp ##need to resolve circular dependency
    )
if(USE_LIBRARY AND NOT BUILD_SHARED_LIBS)

    message(STATUS "Compiling VBF Simulation components to a STATIC LIBRARY")
    add_library(VBF_Simulation
                ${_sources3}
               )
elseif(USE_LIBRARY AND BUILD_SHARED_LIBS)

    message(STATUS "Compiling VBF Simulation components to a SHARED LIBRARY")
    add_library(VBF_Simulation
                SHARED 
                ${_sources3}
                  )
endif()

set_target_properties(VBF_Simulation
                      PROPERTIES
                      POSITION_INDEPENDENT_CODE 1)

target_compile_options(VBF_Simulation
                      PRIVATE
                      ${flags})

#link the current library with other VBF rigid body libraries
target_link_libraries(VBF_Simulation PUBLIC VBF_RigidBody VBF_StaticBody VBF_KinematicBody VBF_DynamicBody)

#make the library available publicly
target_include_directories(VBF_Simulation PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
