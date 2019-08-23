#include "VBF_Static_Ground.hpp"

//Static_Ground Class Definitions
VBF::Static_Ground::Static_Ground(btVector3& normal, double position, btVector3& origin,
                                const double collMarg, size_t index):
               StaticBody(std::string("Static_Ground"),
               new btStaticPlaneShape(normal, position),
               origin, collMarg, index),
               m_normal(normal),
               m_position(position){
                        
                //empty constructor body
               }

//destructor
VBF::Static_Ground::~Static_Ground(){}
btVector3 VBF::Static_Ground::get_normal()const noexcept {return m_normal;}
float VBF::Static_Ground::get_position()const noexcept {return m_position;}

std::string VBF::Static_Ground::get_name() const noexcept { return "Static_Ground"; }
