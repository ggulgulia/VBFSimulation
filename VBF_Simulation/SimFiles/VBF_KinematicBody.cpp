#include "VBF_KinematicBody.hpp"

//default constructor
VBF::KinematicBody::KinematicBody(): RigidBody()
                {  }

//user constructor
VBF::KinematicBody::KinematicBody(const std::string& name, CollShape* shape, 
                                 btVector3 origin, size_t index):
    RigidBody(name, shape, origin, index)
{
    //beautiful process in bullet to create a rigid body
    double mass{};   //default initialization to 0.0                            
    btVector3 inertia{btVector3(0.0, 0.0, 0.0)}; //kinematic body has no mass and hence no inerita
    btRbConstrInfo rbinfo(mass, get_motion_state(), get_shape(), inertia);
    btRigidBody* rbody = get_rbody();
    rbody =  new btRigidBody(rbinfo);
    rbody->setActivationState(DISABLE_DEACTIVATION);
    rbody->setCollisionFlags( rbody->getCollisionFlags()|btCollisionObject::CF_KINEMATIC_OBJECT);
    rbody->setGravity(btVector3(0.0, 0.0, 0.0));
    RigidBody::set_rbody(rbody);
}

//desturctor
VBF::KinematicBody::~KinematicBody(){
            //RigidBody::~RigidBody();
            }
            
//helper functions                
double VBF::KinematicBody::get_mass() const { return 0.0;}
btVector3 VBF::KinematicBody::get_inertia()  const { return btVector3(0.0, 0.0, 0.0);}
btVector3 VBF::KinematicBody::get_position()  {return get_rbody()->getCenterOfMassPosition();}
void VBF::KinematicBody::set_linear_vel(const btVector3& pos, const btVector3& linVel){
    btRigidBody *rbody = this->get_rbody();
    btTransform trans;
    rbody->getMotionState()->getWorldTransform(trans);
    trans.getOrigin() += linVel*0.166667; //dummy vibration, get deltaT as input
    rbody->getMotionState()->setWorldTransform(trans);
}
