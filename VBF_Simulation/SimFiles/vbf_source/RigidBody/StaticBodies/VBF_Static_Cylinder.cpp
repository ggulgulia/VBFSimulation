#include "VBF_Static_Cylinder.hpp"

//Static_Cylinder Class Definitions
VBF::Static_Cylinder::Static_Cylinder(double radius, double height, btVector3 origin,
                                    const double collMarg, size_t index):
               StaticBody(std::string("Static_Cylinder"),
               new btCylinderShape(btVector3(radius, 0.5*height, radius)),
               origin, collMarg, index),
               m_radius(radius), m_height(height){
                        
                //empty constructor body
               }

//destructor
VBF::Static_Cylinder::~Static_Cylinder(){}

double VBF::Static_Cylinder::get_cylinder_radius()const noexcept {return m_radius;}
double VBF::Static_Cylinder::get_cylinder_height()const noexcept {return m_height;}

std::string VBF::Static_Cylinder::get_name() const noexcept { return "Static_Cylinder"; }
