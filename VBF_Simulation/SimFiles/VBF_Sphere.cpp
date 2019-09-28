#include "VBF_Sphere.hpp"


VBF::Sphere::Sphere(double radius, btVector3 origin, btVector3 inertia, double mass, size_t index):
                    RigidBody(std::string("Sphere"),
                    (new btSphereShape(radius)),
                    origin, mass, inertia, index),
                    m_radius(radius){
                        //empty constructor body
                    }
VBF::Sphere::Sphere(const Sphere& sphere, btVector3 origin):                
                    RigidBody(sphere, origin),
                     m_radius(get_radius()){ 
                    //empty constructor body
                    }
             
VBF::Sphere::~Sphere() {};
std::string VBF::Sphere::get_name(){ return "Sphere"; }
