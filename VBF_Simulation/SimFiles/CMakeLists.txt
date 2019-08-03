# HelloWorld is a minimal sample creating, stepping and deleting a Bullet dynamics world
cmake_minimum_required(VERSION 3.2.3)
project(VBF_iwb_TUM LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
message(STATUS "Configuring ${PROJECT_NAME} project with ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION} Compiler")

# set a default configure type of DEBUG
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build Type" FORCE)
endif()

message(STATUS "Configuring project ${project} on/for ${CMAKE_SYSTEM_NAME}")
message(STATUS "Build Type: " ${CMAKE_BUILD_TYPE})
add_subdirectory(vbf_source)
add_subdirectory(vbf_exe)
if(${WITH_UNIT_TESTS})
    message(STATUS "configuring project with UNIT TESTS")
    add_subdirectory(unit_tests)
else()
    message(STATUS "configuring project without unit tests")
    message(STATUS "to configure with unit test, use CLI: -DWIHT_UNIT_TESTS=ON")
endif()

if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    message(STATUS "CMake configure type for project is DEBUG")
    set(CMAKE_CXX_FLAGS "-std=c++14 -g Wall -Werror -fno-elide-constructors")
    message(STATUS "C++ Compiler flags:  ${CMAKE_CXX_FLAGS}")
elseif(${CMAKE_BUILD_TYPE} STREQUAL "Release")
    message(STATUS "CMake configure type is RELEASE")
    set(CMAKE_CXX_FLAGS "-std=c++14 -o1 -Wall -Werror -fno-elide-constructors")
    message(STATUS "C++ Compiler flags:  ${CMAKE_CXX_FLAGS}")
endif()
    

message(STATUS "CMAKE_BUILD_TYPE is ${CMAKE_BUILD_TYPE}")
message(STATUS "compiling the ${PROJECT_NAME} with CXX ${COMPILER_FLAGS}")

#LINK_LIBRARIES(OpenGLSupport OpenGLWindow GL GLU glut GLEW X11 pthread BulletDynamics BulletCollision LinearMath Bullet3Common)

#target_link_libraries(vbf_test.out PRIVATE VBF_RigidBody VBF_StaticBody VBF_KinematicBody VBF_DynamicBody)
