#include <VBF_Kinematic_Cube.hpp>

//Kinematic_Cube Class Definitions
VBF::Kinematic_Cube::Kinematic_Cube(double length, btVector3 origin, size_t index):
               KinematicBody("Kinematic_Cube",
               new btBoxShape(btVector3(length, length, length)),
               origin, index),
               m_length(length){
                        
                //empty constructor body
               }

//destructor
VBF::Kinematic_Cube::~Kinematic_Cube(){};
double VBF::Kinematic_Cube::get_length()const{return m_length;}

