
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-std=c++14 -g -Wall -Werror -fno-elide-constructors")
message("CMAKE_BUILD_TYPE is ${CMAKE_BUILD_TYPE}")

add_subdirectory(RigidBody)

LINK_LIBRARIES(OpenGLSupport OpenGLWindow GL GLU glut GLEW X11 pthread BulletDynamics BulletCollision LinearMath Bullet3Common)

ADD_LIBRARY(vbf_simulation STATIC
              VBF_World.cpp
              VBF_CommonPhysics.cpp
              RigidBody/KinematicBodies/VBF_KinematicMesh.cpp ##need to resolve circular dependency
              )


target_link_libraries(vbf_simulation PUBLIC VBF_RigidBody VBF_StaticBodies VBF_KinematicBodies VBF_DynamicBodies)
target_include_directories(vbf_simulation PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
