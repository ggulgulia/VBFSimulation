# HelloWorld is a minimal sample creating, stepping and deleting a Bullet dynamics world
cmake_minimum_required(VERSION 2.8)
project(VBF_IWB_TUM CXX)

#set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
#set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Werror")
set(CMAKE_CXX_FLAGS "-std=c++14 -g -Wall -Werror -fno-elide-constructors")
message("CMAKE_BUILD_TYPE is ${CMAKE_BUILD_TYPE}")

add_subdirectory(RigidBody)

LINK_LIBRARIES(OpenGLSupport OpenGLWindow GL GLU glut GLEW X11 pthread BulletDynamics BulletCollision LinearMath Bullet3Common)

ADD_EXECUTABLE(vbf_test.out
              VBF_World.cpp
              VBF_CommonPhysics.cpp
              RigidBody/KinematicBodies/VBF_KinematicMesh.cpp ##need to resolve circular dependency
              main.cpp
              )


target_link_libraries(vbf_test.out PRIVATE VBF_RigidBody VBF_StaticBodies VBF_KinematicBodies VBF_DynamicBodies)
