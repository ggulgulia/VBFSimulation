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

# IMPORTANT LINKS
* https://www3.ntu.edu.sg/home/ehchua/programming/cpp/gcc_make.html
* https://cmake.org/documentation/
* http://www.network-theory.co.uk/docs/gccintro/
* 

