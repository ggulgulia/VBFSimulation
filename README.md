# About

This project is on the Vibratory Bowl Simulation to generate the optimum state matrix for the bolts and similar parts that will enable us to come up with an optimum mechanism and parameters involved in the entire process

# Current Status

Right now I'm very new to the project and am learning about what has been done and what's need to be done and hence I'll update this readme file as I work on this project

# Tasks needed to be defined

* How to build the project
* how to contribute the project
* directory structure of the project
* some information about the doxygen guide
* include some parallelization of the serial code (future goal)

## Building the Bullet Physics Engine

The Simulation makes use of Bullet Physics Engine. Version-3 of this engine is provided in the repository under the name bullet3-master.zip

Follow the steps below to build the Bullet Physics engine on a linux system:
* Unzip the file to a suitable location
* On the terminal type:
    * mkdir build
    * cd build
    * cmake .. -G "Unix Makefiles"
    * make
    * make install - this installs the pyhsics engine to your "usr/local/lib" and "usr/local/include" directories
    * on the terminal see if OpenGL library is located in "usr/local/lib" by issuing the command "locate lOpenGLSupport.a" or "locate lOpenGLSupport.so". If neither command points to the above directory then it has to be copied from the directory that one of the two commands yield.
    * To copy the library open a terminal at ""usr/local/lib" and do "sudo cp 'path/to/directory/where/locate lOpenGLSupport.a' points ." (dont forget the ".")
    
## Building ODE (DrawStuff) 
* download draw stuff from https://sourceforge.net/projects/opende/files/ and unpack it
* go to the /ode-0.11.1 directory and issue the following command
    * sh autogen.sh
    * ./configure 
    * make
    * sudo make install
    * if the draw stuff is not header files and libraries are not included in proper locations, do it manually
* by default this configures the ODE as a static library. Need to figure out how to build a shared library from this

Update 25/11/18: ODE-Draw stuff is incompatible with bullet and moreover bullet has its own inbuilt visualization framework based on OpenGL which needs some kind of bridging. Hence I'll discontinue using ODE draw stuff for the time being 

# What is Running (IMPORTANT, ALL the sub-headings below are related to this heading)
* VBF_Simulation/HelloWorld program
* VBF_Simulation/Demos3/BasicDemo/
* VBF_Simulation/Demos3/BasicDemoConsole/ (not helpful since there's no gui mode)
* VBF_Simulation/Demos3/BasicDemoCustomOpenGL2/ (looks like one of the videos that Cosima showed me)
* VBF_Simulation/Demos3/VehicleDemo/

* Upadate 25/11/18 : ../VBF_Simulation/SimFile/test.cpp is running with a blank OpenGL window. Need to bridge this window to the bullet physics simulation that's happening within the code

## Fixes Done to Library for above program to run
* all the fixes done were tested against the Demos mentioned above in bullet until the they ran.
* most of the fixes needed were to create the correct openGL, glut, GL, GLEW libraries and the respective header files in correct location. This is suppose to be done automatically by the CMake. 
* Check the above demos for the kind of structure we need in CMake file

* Update 25/11/18: All the demos use the codes Demos/btgui/ directory which is some sort of framework based around openGL and brideed using DebugDrawer class. Hence I created another library (ofcourse to avoid culttering of our soruce code directory with the code that will never be changed). This library is called libOpenGLWindow.a and the headers are placed in ../../usr/local/includes/ and library is placed in ../../usr/local/lib/
### Bullet Library


### OpenGL Library
* OpenGL associtated with bullet3 physics engine did not build when bullet itself was built. The OpenGL library : libOpenGLSupport.a had to be built from scratch and installed on the locations "usr/local/include/" and "usr/local/lib"
* Update 18th November: Some more modeifications to the OpenGL library. The DemoApplication.cxx and GlutDemoApplication.cxx have been packed as a part of libOpenGLSupport.a to avoid it's inclusion in all demo folders. These two files supposedly pack the example of how a visualization framework in bullet could be used, but I'm yet to figure out how. 


### Glut/GL/GLU Library
* Linkers to above library in CMake File shipped with bullet are missing in many places.
* as again relative paths to include had to be repaired in many files, I don't remember exactly which ones but it makes sense to pack the repaired library and push it to githb. In future it will be needed to make a good unit test and build system so that Cosima and others can use it easily.
* Updaate 18th November: For now one Demos3/BasicDemo/ program compiles. Look at the CMakelists.txt . Check the ../Demos3/BasicDemoCustomOpenGL2/ cmake file and order of the linker flags in the cmake file


# IMPORTANT LINKS
* https://www3.ntu.edu.sg/home/ehchua/programming/cpp/gcc_make.html
* https://cmake.org/documentation/
* http://www.network-theory.co.uk/docs/gccintro/
* https://www.ode-wiki.org/wiki/index.php?title=Manual:_Install_and_Use 
* https://stackoverflow.com and google.com --> my saviour at the (beginning, middle and) end of day
* https://studiofreya.com/game-maker/bullet-physics/debug-triangles-in-bullet-physics/ (mentions something about irrlicht which was used in older version of VBF_Simulations too)

