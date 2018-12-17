#include "VBF_Cube.hpp"



//Cube Class Definitions
VBF::Cube::Cube(double length, btVector3 origin, btVector3 inertia, double mass, size_t index):
               RigidBody(std::string("Cube"),
               (new btBoxShape(btVector3(length, length, length))),
               origin, mass, inertia, index),
               m_length(length){
                        
                //empty constructor body
               }

//copy constructor
VBF::Cube::Cube(const Cube& cube, btVector3 origin):                
               RigidBody(cube, origin),
               m_length(get_length()){ 
               
               //empty constructor body
               }

//destructor
VBF::Cube::~Cube(){};

std::string VBF::Cube::get_name(){ return "Cube"; }

