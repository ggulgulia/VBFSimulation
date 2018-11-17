# HelloWorld is a minimal sample creating, stepping and deleting a Bullet dynamics world
cmake_minimum_required(VERSION 2.8)
project(libtest_project CXX)

#set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Werror")
message("CMAKE_BUILD_TYPE is ${CMAKE_BUILD_TYPE}")
INCLUDE_DIRECTORIES(
${BULLET_PHYSICS_SOURCE_DIR}/src 
)

LINK_LIBRARIES(
    GL GLU glut OpenGLSupport BulletDynamics BulletCollision LinearMath 
)

IF (WIN32)
	ADD_EXECUTABLE(AppBasicDemo
		main.cpp 
		BasicDemo.cpp
        Win32DemoApplication.cpp
		BasicDemo.h
		${BULLET_PHYSICS_SOURCE_DIR}/build3/bullet.rc
	)
ELSE()
    ADD_EXECUTABLE(AppBasicDemo
	    main.cpp 
		BasicDemo.cpp
        DemoApplication.h
        DemoApplication.cpp
        GlutDemoApplication.cpp
        GlutDemoApplication.h
		BasicDemo.h

        )
	
ENDIF()




IF (INTERNAL_ADD_POSTFIX_EXECUTABLE_NAMES)
			SET_TARGET_PROPERTIES(AppHelloWorld PROPERTIES  DEBUG_POSTFIX "_Debug")
			SET_TARGET_PROPERTIES(AppHelloWorld PROPERTIES  MINSIZEREL_POSTFIX "_MinsizeRel")
			SET_TARGET_PROPERTIES(AppHelloWorld PROPERTIES  RELWITHDEBINFO_POSTFIX "_RelWithDebugInfo")
ENDIF(INTERNAL_ADD_POSTFIX_EXECUTABLE_NAMES)
