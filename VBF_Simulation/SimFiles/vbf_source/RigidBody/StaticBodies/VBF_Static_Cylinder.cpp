#include "VBF_Static_Cylinder.hpp"

//Static_Cylinder Class Definitions
VBF::Static_Cylinder::Static_Cylinder(double length, btVector3 origin, size_t index):
               StaticBody(std::string("Static_Cylinder"),
               new btCylinderShape(btVector3(length, length, length)),
               origin, index),
               m_length(length){
                        
                //empty constructor body
               }

//destructor
VBF::Static_Cylinder::~Static_Cylinder(){};
double VBF::Static_Cylinder::get_length()const{return m_length;}

std::string VBF::Static_Cylinder::get_name() const noexcept { return "Static_Cylinder"; }
