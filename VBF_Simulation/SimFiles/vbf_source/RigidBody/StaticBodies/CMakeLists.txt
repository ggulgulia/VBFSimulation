#add appropriate path to src code from which the lib is to be made
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-g -std=c++14 -Wall -fno-elide-constructors")

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

## link VBF_RigidBody library with VBF_StaticBodies library
target_link_libraries(VBF_StaticBodies -L../VBF_RigidBody)

#make the library PUBLIC
target_include_directories(VBF_StaticBodies PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
