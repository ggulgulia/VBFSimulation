#include <VBF_Dynamic_Cylinder.hpp>



//Dynamic_Cylinder Class Definitions
VBF::Dynamic_Cylinder::Dynamic_Cylinder(double radius, double height, btVector3 origin, 
                                       const double collMarg, double mass, double linFriction, 
                                       double rollingFriction, 
                                       double restitution, double linDamping, 
                                       double angularDamping, size_t index):
                                       DynamicBody("Dynamic_Cylinder",
                                       new btCylinderShape(btVector3(radius, 0.5*height , radius)),
                                       origin, collMarg, mass, linFriction, rollingFriction, 
                                       restitution, linDamping, angularDamping, index),
                                       m_radius(radius), m_height(height){
                                           //empty constructor body
                                       }

//destructor
VBF::Dynamic_Cylinder::~Dynamic_Cylinder(){}

double VBF::Dynamic_Cylinder::get_cylinder_radius()const noexcept {return m_radius;}
double VBF::Dynamic_Cylinder::get_cylinder_height()const noexcept {return m_height;}
std::string VBF::Dynamic_Cylinder::get_name() const noexcept { return "Dynamic_Cylinder"; }

