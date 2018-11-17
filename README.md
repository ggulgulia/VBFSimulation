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

# What is Running (IMPORTANT, ALL the sub-headings below are related to this heading)
* VBF_Simulation/HelloWorld program
* VBF_Simulation/Demos3/BasicDemo

## Fixes Done to Library for above program to run
* all the fixes done were tested against the Demo3 in bullet until the Demos in bullet-3-master/Deom3/ ran
* note the include paths of demos are completely shitty. The relative include paths of header files and libraries makes the life worse. This requires us to remember the relative paths of all inlude files in the bullet library. I loathe the programmer of this bullet library.
### Bullet Library


### OpenGL Library
* OpenGL associtated with bullet3 physics engine did not build when bullet itself was built. The OpenGL library : libOpenGLSupport.a had to be built from scratch and installed on the locations "usr/local/include/" and "usr/local/lib"

### Glut/GL/GLU Library
* Linkers to above library in CMake File shipped with bullet are missing in many places.
* as again relative paths to include had to be repaired in many files, I don't remember exactly which ones but it makes sense to pack the repaired library and push it to githb. In future it will be needed to make a good unit test and build system so that Cosima and others can use it easily.
* For now one Demos3/BasicDemo/ program compiles. Look at the CMakelists.txt


# IMPORTANT LINKS
* https://www3.ntu.edu.sg/home/ehchua/programming/cpp/gcc_make.html
* https://cmake.org/documentation/
* http://www.network-theory.co.uk/docs/gccintro/
* https://www.ode-wiki.org/wiki/index.php?title=Manual:_Install_and_Use 
* https://stackoverflow.com and google.com --> my saviour at the (beginning, middle and) end of day

