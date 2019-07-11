#include <VBF_Kinematic_Cylinder.hpp>

VBF::Kinematic_Cylinder::Kinematic_Cylinder(): KinematicBody("Default Kinematic Cube", 
                          new btBoxShape(btVector3(10.0, 10.0, 10.0)),
                          btVector3(0.0,0.0, 0.0), 23), 
            m_length(10.0){
                            //empty constructor body
            }

//Kinematic_Cylinder Class Definitions
VBF::Kinematic_Cylinder::Kinematic_Cylinder(double length, btVector3 origin, size_t index):
                                    KinematicBody("Kinematic_Cylinder",
                                    new btBoxShape(btVector3(length, length, length)),
                                    origin, index),
                                    m_length(length){
                        
                //empty constructor body
               }

//destructor
VBF::Kinematic_Cylinder::~Kinematic_Cylinder(){};
double VBF::Kinematic_Cylinder::get_length()const noexcept {return m_length;}
std::string VBF::Kinematic_Cylinder::get_name() const noexcept { return "Kinematic_Cylinder"; }
