#include <VBF_Kinematic_Cylinder.hpp>


VBF::Kinematic_Cylinder::Kinematic_Cylinder(): KinematicBody("Default Kinematic Cylinder", 
                          new btCylinderShape(btVector3(0.5, 1.0, 0.5)),
                          btVector3(0.0,0.0, 0.0), 0.004, 23), 
            m_radius(0.5), m_height(2.0){
                            //empty constructor body
            }

//Kinematic_Cylinder Class Definitions
VBF::Kinematic_Cylinder::Kinematic_Cylinder(double radius, double height, btVector3 origin,
                                            const double collMarg, size_t index):
                                    KinematicBody("Kinematic_Cylinder",
                                    new btBoxShape(btVector3(radius, 0.5*height, radius)),
                                    origin, collMarg, index),
                                    m_radius(radius), m_height(height){
                        
                //empty constructor body
               }

//destructor
VBF::Kinematic_Cylinder::~Kinematic_Cylinder(){}
double VBF::Kinematic_Cylinder::get_cylinder_radius()const noexcept {return m_radius;}
double VBF::Kinematic_Cylinder::get_cylinder_height()const noexcept {return m_height;}
std::string VBF::Kinematic_Cylinder::get_name() const noexcept { return "Kinematic_Cylinder"; }
