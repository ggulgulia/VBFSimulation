#include <VBF_Static_Sphere.hpp>


VBF::Static_Sphere::Static_Sphere(): StaticBody("Default Static Sphere", 
                          new btSphereShape(10.0),
                          btVector3(0.0,0.0, 0.0), 33), 
            m_radius(10.0){
                            //empty constructor body
            }
VBF::Static_Sphere::Static_Sphere(double radius, btVector3 origin, size_t index):
                    StaticBody("Static_Sphere",
                    new btSphereShape(radius),
                    origin, index),
                    m_radius(radius){
                        //empty constructor body
                    }
             
VBF::Static_Sphere::~Static_Sphere() {};
std::string VBF::Static_Sphere::get_name() const noexcept { return "Static_Sphere"; }
double VBF::Static_Sphere::get_radius() const { return m_radius;}
