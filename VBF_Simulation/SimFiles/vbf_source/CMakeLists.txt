set(CMAKE_CXX_STANDARD 14)

## set up of build specific compiler options 
## goal is to have strict compiler checks even in 
##debug mode 

set(CMAKE_CXX_FLAGS "-std=c++14")
message(STATUS "compilation of VBF Simulation components to library")
if(${CMAKE_BUILD_TYPE}  STREQUAL "Debug")
    message("CMAKE build type is DEBUG ")
    list(APPEND flags "-g -Wall -Werror -fno-elide-conostructors")
elseif(${CMAKE_BUILD_TYPE} STREQUAL "Release")
    message("CMAKE build type is RELEASE ")
    list(APPEND flags "-O1 -fPIC -Wall -Werror -fno-elide-constructors" )
endif()

## set Linux Specific flags
if(UNIX)
    message("Compiling for Unix like system")
    list(APPEND flags "-Wextra" "-Wpedantic")
endif(UNIX)

message("CMAKE_BUILD_TYPE is ${CMAKE_BUILD_TYPE}")

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
    add_library(vbf_simulation
                ${_sources3}
                  )
elseif(USE_LIBRARY AND BUILD_SHARED_LIBS)

    message(STATUS "Compiling VBF Simulation components to a SHARED LIBRARY")
    ADD_LIBRARY(vbf_simulation
                SHARED 
                ${_sources3}
                  )
endif()

target_compile_options(vbf_simulation
                      PRIVATE
                      ${flags})

#link the current library with other VBF rigid body libraries
target_link_libraries(vbf_simulation PUBLIC VBF_RigidBody VBF_StaticBodies VBF_KinematicBodies VBF_DynamicBodies)

#make the library available publicly
target_include_directories(vbf_simulation PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
