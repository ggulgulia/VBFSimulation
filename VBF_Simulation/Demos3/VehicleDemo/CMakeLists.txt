# This is basically the overall name of the project in Visual Studio this is the name of the Solution File


# For every executable you have with a main method you should have an add_executable line below.
# For every add executable line you should list every .cpp and .h file you have associated with that executable.  



# You shouldn't have to modify anything below this line 
########################################################
cmake_minimum_required(VERSION 2.8)
project(libtest_project CXX)

set(CMAKE_CXX_FLAGS "-std=c++11 -g")
message("CMAKE_BUILD_TYPE is ${CMAKE_BUILD_TYPE}")

LINK_LIBRARIES(
 OpenGLSupport GL GLU glut  BulletDynamics BulletCollision LinearMath    ${GLUT_glut_LIBRARY} ${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY}
)

ADD_EXECUTABLE(AppVehicleDemo
	heightfield128x128.cpp
	VehicleDemo.cpp
	main.cpp
)

IF (INTERNAL_ADD_POSTFIX_EXECUTABLE_NAMES)
			SET_TARGET_PROPERTIES(AppVehicleDemo PROPERTIES  DEBUG_POSTFIX "_Debug")
			SET_TARGET_PROPERTIES(AppVehicleDemo PROPERTIES  MINSIZEREL_POSTFIX "_MinsizeRel")
			SET_TARGET_PROPERTIES(AppVehicleDemo PROPERTIES  RELWITHDEBINFO_POSTFIX "_RelWithDebugInfo")
ENDIF(INTERNAL_ADD_POSTFIX_EXECUTABLE_NAMES)
