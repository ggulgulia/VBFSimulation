# HelloWorld is a minimal sample creating, stepping and deleting a Bullet dynamics world
cmake_minimum_required(VERSION 3.2.3)
project(VBF_iwb_TUM CXX)

add_subdirectory(vbf_source)
add_subdirectory(vbf_exe)
if(${WITH_UNIT_TESTS})
    message(STATUS "building with unit tests")
    add_subdirectory(unit_tests)
endif()

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
#set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Werror")
set(CMAKE_CXX_FLAGS "-std=c++14 -g -Wall -Werror -fno-elide-constructors")
message("CMAKE_BUILD_TYPE is ${CMAKE_BUILD_TYPE}")
message(STATUS "compiling the ${PROJECT_NAME} with CXX ${COMPILER_FLAGS}")

#LINK_LIBRARIES(OpenGLSupport OpenGLWindow GL GLU glut GLEW X11 pthread BulletDynamics BulletCollision LinearMath Bullet3Common)

#target_link_libraries(vbf_test.out PRIVATE VBF_RigidBody VBF_StaticBodies VBF_KinematicBodies VBF_DynamicBodies)
