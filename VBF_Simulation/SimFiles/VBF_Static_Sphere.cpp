#include "VBF_Static_Sphere.hpp"


VBF::Static_Sphere::Static_Sphere(double radius, btVector3 origin,size_t index):
                    StaticBody(std::string("Static_Sphere"),
                    (new btSphereShape(radius)),
                    origin, index),
                    m_radius(radius){
                        //empty constructor body
                    }
             
VBF::Static_Sphere::~Static_Sphere() {};
