#add appropriate path to src code from which the lib is to be made
cmake_minimum_required(VERSION 3.2.3)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "-std=c++14")
set(USE_LIBRARY ON)
set(BUILD_SHARED_LIBS OFF)
message(STATUS "Compile sources for VBF_DynamicBody into a libary? " ${USE_LIBRARY})

LINK_LIBRARIES(OpenGLSupport OpenGLWindow GL GLU glut GLEW X11 pthread 
              BulletDynamics BulletCollision LinearMath Bullet3Common)

## set up of build specific compiler options
## goal is to have strict compiler checks even 
## for both Release and Debug builds

if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    message(STATUS "CMake build type for DynamicBodies library is Debug")
    list(APPEND flags "-g" "-Wall" "-Werror" "-fno-elide-constructors")
elseif(${CMAKE_BUILD_TYPE} STREQUAL "Release")
    message(STATUS "CMake build type for DynamicBodies library is Release")
    list(APPEND flags "-fPIC" "-Wall" "-Werror" "-fno-elide-constructors")
endif()

#Linux/Gcc Specific compiler flags
if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    message(STATUS "Compiling DynamicBody library on/for LINUX")
    list(APPEND flags "-Wextra" "-Wpedantic")
endif()


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
add_library(VBF_DynamicBody 
            STATIC #name of target library
            ${_sources3}
            )
elseif(USE_LIBRARY AND BUILD_SHARED_LIBS)
message(STATUS "compiling Rigid_Body sources to shared library")
    add_library(VBF_DynamicBody
               SHARED
               ${_sources3}
               )
endif()

set_target_properties(VBF_DynamicBody
                      PROPERTIES
                      POSITION_INDEPENDENT_CODE 1)

target_compile_options(VBF_DynamicBody
                      PRIVATE
                      ${flags})

target_link_libraries(VBF_DynamicBody -L../VBF_RigidBody)

#make the library PUBLIC
target_include_directories(VBF_DynamicBody PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
