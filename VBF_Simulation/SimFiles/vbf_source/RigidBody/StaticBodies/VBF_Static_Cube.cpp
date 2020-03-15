#include "VBF_Static_Cube.hpp"

//Static_Cube Class Definitions
VBF::Static_Cube::Static_Cube(double length, btVector3 origin, 
                              const double collMarg, size_t index):
               StaticBody(std::string("Static_Cube"),
               new btBoxShape(btVector3(length, length, length)),
               origin, collMarg, index),
               m_length(length){
                        
                //empty constructor body
               }

//destructor
VBF::Static_Cube::~Static_Cube(){}
double VBF::Static_Cube::get_length()const{return m_length;}

std::string VBF::Static_Cube::get_name() const noexcept { return "Static_Cube"; }
