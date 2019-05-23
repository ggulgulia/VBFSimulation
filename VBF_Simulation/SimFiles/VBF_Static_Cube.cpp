#include "VBF_Static_Cube.hpp"

//default constructor
VBF::Static_Cube::Static_Cube(){
    m_length=50;
    size_t index=0;
    StaticBody("Default_Static_Cube", new btBoxShape(btVector3(m_length, m_length, m_length)), btVector3(0.0, 0.0, 0.0), index);
}

//Static_Cube Class Definitions
VBF::Static_Cube::Static_Cube(double length, btVector3 origin, size_t index):
               VBF::StaticBody(std::string("Static_Cube"),
               new btBoxShape(btVector3(length, length, length)),
               origin, index),
               m_length(length){
                        
                //empty constructor body
               }


//destructor
VBF::Static_Cube::~Static_Cube(){};

double VBF::Static_Cube::get_length()const{return m_length;}

