#include <VBF_Dynamic_Cube.hpp>



//Dynamic_Cube Class Definitions
VBF::Dynamic_Cube::Dynamic_Cube(double length, btVector3 origin, 
                                double mass, 
                                double linFriction, double rollingFriction, 
                                double restitution, double linDamping, 
                                double angularDamping, size_t index):
                                DynamicBody("Dynamic_Cube",
                                new btBoxShape(btVector3(length, length, length)),
                                origin, mass, linFriction, rollingFriction, 
                                restitution, linDamping, angularDamping, index),
                                m_length(length){
                                    //empty constructor body
                                }

//destructor
VBF::Dynamic_Cube::~Dynamic_Cube(){}

std::string VBF::Dynamic_Cube::get_name() const noexcept { return "Dynamic_Cube"; }

