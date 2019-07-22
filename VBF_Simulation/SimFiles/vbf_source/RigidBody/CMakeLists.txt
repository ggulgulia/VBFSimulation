#add appropriate path to src code from which the lib is to be made
cmake_minimum_required(VERSION 3.2.3)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-std=c++14")

message(STATUS "Compiling RigidBody source to a library")

## set Release type specific type compiler flags
if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    list(APPEND flags "-g" "-Wall" "-Werror" "-fno-elide-constructors")
elseif(${CMAKE_BUILD_TYPE} STREQUAL "Release")
    list(APPEND flags "-fPIC" "-Wall" "-Werror" "-fno-elide-constructors" )
endif()

## add extra compilation flags for linux type machines
if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    message(STATUS "Compiling RigidBody library on/for LINUX")
    list(APPEND flags "-Wextra" "-Wpedantic")
endif()

set(USE_LIBRARY ON)
set(BUILD_SHARED_LIBS OFF)
message(STATUS "Compile sources for VBF_RigidBody into a libary?" ${USE_LIBRARY})

## create a variable called "_sources" and append the source
## files that we wish to compile as the library
list(APPEND _sources VBF_RigidBody.hpp VBF_RigidBody.cpp)

if(USE_LIBRARY AND NOT BUILD_SHARED_LIBS)
message(STATUS "compiling Rigid_Body sources to static library")
add_library(
    VBF_RigidBody STATIC #name of target library
    ${_sources}
    )
elseif(USE_LIBRARY AND BUILD_SHARED_LIBS)
message(STATUS "compiling Rigid_Body sources to shared library")
    add_library(VBF_RigidBody
               SHARED
               ${_sources}
               )
endif()

##this attribute sets the flags only for the target library 
## and no other targets using the VBF_RigidBody library
target_compile_options(VBF_RigidBody
                      PRIVATE
                      ${flags})


#make the library PUBLIC
target_include_directories(VBF_RigidBody PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

add_subdirectory(DynamicBodies)
add_subdirectory(KinematicBodies)
add_subdirectory(StaticBodies)

