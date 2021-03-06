#include <VBF_KinematicBody.hpp>



//KinematicBody Class Definitions
VBF::KinematicBody::KinematicBody(const std::string& name, CollShape* shape, btVector3 origin,
                                  const double collMarg, size_t index):
               RigidBody(name, shape, origin, collMarg, index){
                        
                MotionState* moSt = RigidBody::get_motion_state();
                double mass = 0.0;
                btVector3 inertia(btVector3(0.0, 0.0, 0.0));
                btRbConstrInfo rbinfo(mass, moSt, shape, inertia);
                btRigidBody* rbody = new btRigidBody(rbinfo);
                rbody->setActivationState(DISABLE_DEACTIVATION);
                rbody->setCollisionFlags( rbody->getCollisionFlags()|btCollisionObject::CF_KINEMATIC_OBJECT);
                rbody->setGravity(btVector3(0.0, 0.0, 0.0));
                RigidBody::set_rbody(rbody);
               }

//destructor
VBF::KinematicBody::~KinematicBody(){}

double VBF::KinematicBody::get_mass() const { return 0.0;}
btVector3 VBF::KinematicBody::get_inertia()  const { return btVector3(0.0, 0.0, 0.0);}
btVector3 VBF::KinematicBody::get_position()  {return get_rbody()->getCenterOfMassPosition();}
//void VBF::KinematicBody::set_linear_vel(const btVector3& pos, const btVector3& linVel){
void VBF::KinematicBody::set_linear_vel(const btVector3& linVel){
    btRigidBody *rbody = this->get_rbody();
    btTransform trans;
    rbody->getMotionState()->getWorldTransform(trans);
    trans.getOrigin() += linVel*0.166667; //dummy vibration, get deltaT as input
    rbody->getMotionState()->setWorldTransform(trans);
}

btVector3 VBF::KinematicBody::get_cog_position()const noexcept {return this->get_rbody()->getCenterOfMassPosition();}
const btMatrix3x3& VBF::KinematicBody::get_rotation() const noexcept {
    btTransform* trans = new btTransform();
    this->get_rbody()->getMotionState()->getWorldTransform(*trans);
    return trans->getBasis();}

