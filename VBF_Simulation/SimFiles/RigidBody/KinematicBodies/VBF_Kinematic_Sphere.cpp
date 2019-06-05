#include <VBF_Kinematic_Sphere.hpp>


VBF::Kinematic_Sphere::Kinematic_Sphere(double radius, btVector3 origin, size_t index):
                    KinematicBody("Kinematic_Sphere",
                    new btSphereShape(radius),
                    origin, index),
                    m_radius(radius){
                        //empty constructor body
                    }
             
VBF::Kinematic_Sphere::~Kinematic_Sphere() {};
std::string VBF::Kinematic_Sphere::get_name() const { return "Kinematic_Sphere"; }
