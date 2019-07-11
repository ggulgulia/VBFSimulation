#include <VBF_Dynamic_Cylinder.hpp>



//Dynamic_Cylinder Class Definitions
VBF::Dynamic_Cylinder::Dynamic_Cylinder(double length, btVector3 origin, 
                                double mass, 
                                double linFriction, double rollingFriction, 
                                double restitution, double linDamping, 
                                double angularDamping, size_t index):
                                DynamicBody("Dynamic_Cylinder",
                                new btCylinderShape(btVector3(length, length, length)),
                                origin, mass, linFriction, rollingFriction, 
                                restitution, linDamping, angularDamping, index),
                                m_length(length){
                                    //empty constructor body
                                }

//destructor
VBF::Dynamic_Cylinder::~Dynamic_Cylinder(){};

std::string VBF::Dynamic_Cylinder::get_name() const noexcept { return "Dynamic_Cylinder"; }

