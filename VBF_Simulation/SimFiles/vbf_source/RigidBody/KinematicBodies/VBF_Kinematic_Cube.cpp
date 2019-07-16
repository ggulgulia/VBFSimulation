#include <VBF_Kinematic_Cube.hpp>

VBF::Kinematic_Cube::Kinematic_Cube(): KinematicBody("Default Kinematic Cube", 
                          new btBoxShape(btVector3(10.0, 10.0, 10.0)),
                          btVector3(0.0,0.0, 0.0), 23), 
            m_length(10.0){
                            //empty constructor body
            }

//Kinematic_Cube Class Definitions
VBF::Kinematic_Cube::Kinematic_Cube(double length, btVector3 origin, size_t index):
                                    KinematicBody("Kinematic_Cube",
                                    new btBoxShape(btVector3(length, length, length)),
                                    origin, index),
                                    m_length(length){
                        
                //empty constructor body
               }

//destructor
VBF::Kinematic_Cube::~Kinematic_Cube(){}
double VBF::Kinematic_Cube::get_length()const noexcept {return m_length;}
std::string VBF::Kinematic_Cube::get_name() const noexcept { return "Kinematic_Cube"; }
