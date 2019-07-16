#add appropriate path to src code from which the lib is to be made
cmake_minimum_required(VERSION 3.2.3)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-std=c++14")
message(STATUS "Compilation of StaticBodies sources to a library")

## set up of build specific compiler options
## goal is to have strict compiler checks even 
## for both Release and Debug builds

if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    message(STATUS "CMake build type for StaticBodies library is Debug")
    list(APPEND flags "-g" "-Wall" "-Werror" "-fno-elide-constructors")
elseif(${CMAKE_BUILD_TYPE} STREQUAL "Release")
    message(STATUS "CMake build type for StaticBodies library is Release")
    list(APPEND flags "-fPIC" "-Wall" "-Werror" "-fno-elide-constructors")
endif()

if(UNIX)
    message(STATUS "Compiling StaticBodies library for Unix like system")
    list(APPEND flags "-Wextra" "-Wpedantic")
endif(UNIX)

set(USE_LIBRARY ON)
set(BUILD_SHARED_LIBS OFF)

## create a variable called _sources1 and append the source files
## we wish to compile in a library
list(APPEND _sources1
    VBF_StaticBody.cpp
    VBF_Static_Cube.cpp
    VBF_StaticMesh.cpp
    VBF_Static_Ground.cpp
    VBF_Static_Cylinder.cpp
    VBF_Static_Sphere.cpp)
LINK_LIBRARIES(OpenGLSupport OpenGLWindow GL GLU glut GLEW X11 pthread BulletDynamics BulletCollision LinearMath Bullet3Common)

if(USE_LIBRARY AND NOT BUILD_SHARED_LIBS)
    message(STATUS "compiling Static_Body sources to static library")
    add_library(VBF_StaticBodies
     STATIC 
    ${_sources1}
    )
elseif(USE_LIBRARY AND BUILD_SHARED_LIBS)
    message(STATUS "compiling Static_Body sources to shared library")
    add_library(VBF_StaticBodies 
               SHARED
               ${_sources1}
               )

endif()
target_compile_options(VBF_StaticBodies
                      PRIVATE
                      ${flags})


## link VBF_RigidBody library with VBF_StaticBodies library
target_link_libraries(VBF_StaticBodies -L../VBF_RigidBody)

#make the library PUBLIC
target_include_directories(VBF_StaticBodies PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
