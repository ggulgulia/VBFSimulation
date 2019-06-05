#include <VBF_DynamicBody.hpp>


//user constructor
VBF::DynamicBody::DynamicBody(std::string name, CollShape* shape, 
                              btVector3 origin, double mass, 
                              double linFriction, double rollingFriction, 
                              double restitution, double linDamping, 
                              double angularDamping, size_t index):
    RigidBody(name, shape, origin, index),
    m_mass(mass), m_inertia(btVector3(0.0, 0.0, 0.0))
{
    MotionState* moSt = RigidBody::get_motion_state();
    shape->calculateLocalInertia(m_mass, m_inertia);
    btRbConstrInfo rbinfo(m_mass, moSt, shape, m_inertia);
    rbinfo.m_friction = linFriction;

    //this causes the loaded stl mesh to dissappear
    //rbinfo.m_rollingFriction = rollingFriction;  //bug here
    rbinfo.m_restitution = 0.0;
    rbinfo.m_linearDamping = linDamping;
    rbinfo.m_angularDamping = angularDamping;
    btRigidBody* rbody = new btRigidBody(rbinfo);
    rbody->setActivationState(DISABLE_DEACTIVATION);
    rbody->setGravity(btVector3(0.0, -9.80, 0.0));
    RigidBody::set_rbody(rbody);
}

//desturctor
VBF::DynamicBody::~DynamicBody(){
            }
            
//helper functions                
double VBF::DynamicBody::get_mass()        const { return m_mass;   }
btVector3 VBF::DynamicBody::get_inertia()  const { return m_inertia;}
void VBF::DynamicBody::set_gravity(const btVector3 gravity){ get_rbody()->setGravity(gravity);  }
btVector3 VBF::DynamicBody::get_position()  {return get_rbody()->getCenterOfMassPosition();}

void VBF::DynamicBody::set_linear_vel(const btVector3& pos, const btVector3& linVel){
    btRigidBody *rbody = this->get_rbody();
    rbody->setLinearVelocity(linVel);
}
