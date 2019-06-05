#include <VBF_Dynamic_Sphere.hpp>



//Dynamic_Sphere Class Definitions
VBF::Dynamic_Sphere::Dynamic_Sphere(double radius, btVector3 origin, 
                                double mass, 
                                double linFriction, double rollingFriction, 
                                double restitution, double linDamping, 
                                double angularDamping, size_t index):
                                DynamicBody("Dynamic_Sphere",
                                new btSphereShape(radius),
                                origin, mass, linFriction, rollingFriction, 
                                restitution, linDamping, angularDamping, index),
                                m_radius(radius){
                                    //empty constructor body
                                }

//destructor
VBF::Dynamic_Sphere::~Dynamic_Sphere(){};

std::string VBF::Dynamic_Sphere::get_name() const { return "Dynamic_Sphere"; }

