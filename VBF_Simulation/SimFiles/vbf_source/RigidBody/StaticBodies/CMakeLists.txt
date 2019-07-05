#add appropriate path to src code from which the lib is to be made
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-g -std=c++14 -Wall -Werror -fno-elide-constructors")

LINK_LIBRARIES(OpenGLSupport OpenGLWindow GL GLU glut GLEW X11 pthread BulletDynamics BulletCollision LinearMath Bullet3Common)

add_library(
    VBF_StaticBodies STATIC#name of target library
    #VBF_RigidBody.cpp
    VBF_StaticBody.cpp
    VBF_Static_Ground.cpp
    VBF_Static_Cube.cpp
    VBF_Static_Sphere.cpp
    VBF_StaticMesh.cpp
    )
target_link_libraries(VBF_StaticBodies -L../VBF_RigidBody)

#make the library PUBLIC
target_include_directories(VBF_StaticBodies PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
