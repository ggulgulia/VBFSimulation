#include "VBF_StaticBody.hpp"

//default constructor
VBF::StaticBody::StaticBody(){  }

//user constructor
VBF::StaticBody::StaticBody(const std::string& name, CollShape* shape, 
                            btVector3 origin, size_t index):
                            RigidBody(name,shape, origin, index)
{
    //beautiful process in bullet to create a rigid body
    double mass{};   //default initialization to 0.0                            
    btVector3 inertia{btVector3(0.0, 0.0, 0.0)}; //kinematic body has no mass and hence no inerita
    btRbConstrInfo rbinfo(mass, get_motion_state(), get_shape(), inertia);
    btRigidBody* rbody(new btRigidBody(rbinfo));
    rbody->setGravity(btVector3(0.0, 0.0, 0.0));
    set_rbody(rbody);
}

//desturctor
VBF::StaticBody::~StaticBody(){
            }
            
//helper functions                
//void VBF::StaticBody::setName(const std::string& name)override {m_name = name;}
double VBF::StaticBody::get_mass() const { return 0.0;}
btVector3 VBF::StaticBody::get_inertia()  const { return btVector3(0.0, 0.0, 0.0);}
btVector3 VBF::StaticBody::get_position()  {return get_rbody()->getCenterOfMassPosition();}
