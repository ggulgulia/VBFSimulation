#add appropriate path to src code from which the lib is to be made
cmake_minimum_required(VERSION 3.2.3)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "-std=c++17")
message(STATUS "Compilation of StaticBodies sources to a library")

## set up of build specific compiler options
## goal is to have strict compiler checks even 
## for both Release and Debug builds

if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    message(STATUS "CMake build type for StaticBodies library is Debug")
    list(APPEND flags "-g" "-Wall" "-Werror" "-fno-elide-constructors")
elseif(${CMAKE_BUILD_TYPE} STREQUAL "Release")
    message(STATUS "CMake build type for StaticBodies library is Release")
    list(APPEND flags "-O3" "-fPIC" "-Wall" "-Werror" "-fno-elide-constructors")
endif()

#Linux/Gcc Specific compiler flags
if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    message(STATUS "Compiling StaticBody library on/for LINUX")
    list(APPEND flags "-Wextra" "-Wpedantic")
endif()

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
    add_library(VBF_StaticBody
     STATIC 
    ${_sources1}
    )
elseif(USE_LIBRARY AND BUILD_SHARED_LIBS)
    message(STATUS "compiling Static_Body sources to shared library")
    add_library(VBF_StaticBody 
               SHARED
               ${_sources1}
               )

endif()

set_target_properties(VBF_StaticBody
                      PROPERTIES
                      POSITION_INDEPENDENT_CODE 1)

target_compile_options(VBF_StaticBody
                      PRIVATE
                      ${flags})


## link VBF_RigidBody library with VBF_StaticBody library
target_link_libraries(VBF_StaticBody -L../VBF_RigidBody)

#make the library PUBLIC
#this enables includes of header files
#using the angled brackets and without the
#user being aware of the relative location 
#of the header
target_include_directories(VBF_StaticBody PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
