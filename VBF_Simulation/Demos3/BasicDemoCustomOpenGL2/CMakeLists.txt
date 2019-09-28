cmake_minimum_required(VERSION 2.8)
project(libtest_project CXX)

#set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "-std=c++11 -g -Wall")
message("CMAKE_BUILD_TYPE is ${CMAKE_BUILD_TYPE}")

LINK_LIBRARIES(
    OpenGLSupport GL GLU glut GLEW X11 pthread BulletDynamics BulletCollision LinearMath 
)

IF (WIN32)
	ADD_EXECUTABLE(AppBasicDemoCustomOpenGL
		main.cpp 
		${BULLET_PHYSICS_SOURCE_DIR}/build3/bullet.rc
	)
ELSE()
    ADD_EXECUTABLE(AppBasicDemoCustomOpenGL
        BasicDemoPhysicsSetup.cpp
        ../btgui/OpenGLWindow/X11OpenGLWindow.cpp
	    main.cpp 

        )
	
ENDIF()




IF (INTERNAL_ADD_POSTFIX_EXECUTABLE_NAMES)
			SET_TARGET_PROPERTIES(AppHelloWorld PROPERTIES  DEBUG_POSTFIX "_Debug")
			SET_TARGET_PROPERTIES(AppHelloWorld PROPERTIES  MINSIZEREL_POSTFIX "_MinsizeRel")
			SET_TARGET_PROPERTIES(AppHelloWorld PROPERTIES  RELWITHDEBINFO_POSTFIX "_RelWithDebugInfo")
ENDIF(INTERNAL_ADD_POSTFIX_EXECUTABLE_NAMES)
