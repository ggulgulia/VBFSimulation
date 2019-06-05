#include "VBF_DynamicBody.hpp"

//default constructor
VBF::DynamicBody::DynamicBody():
                m_rbody(nullptr)
                {  }

//user constructor
VBF::DynamicBody::DynamicBody(std::string name, CollShape* shape, btVector3 origin,
                          btTransform shapeTransform, double mass, 
                          double linFriction, double rollingFriction, 
                          double restitution, double linDamping, 
                          double angularDamping, size_t index):
    RigidBody(name, shape, origin, shapeTransform, index),
    m_mass(mass), m_inertia(btVector3(0.0, 0.0, 0.0))
{
    m_shape->calculateLocalInertia(m_mass, m_inertia);
    btRbConstrInfo rbinfo(m_mass, get_motion_state(), m_shape, m_inertia);
    rbinfo.m_friction = linFriction;

    //this causes the loaded stl mesh to dissappear
    //rbinfo.m_rollingFriction = rollingFriction;  //bug here
    rbinfo.m_restitution = 0.0;
    rbinfo.m_linearDamping = linDamping;
    rbinfo.m_angularDamping = angularDamping;
    m_rbody = new btDynamicBody(rbinfo);
    m_rbody->setActivationState(DISABLE_DEACTIVATION);

}

//desturctor
VBF::DynamicBody::~DynamicBody(){
            delete m_rbody;
            m_rbody = nullptr;
            }
            
//helper functions                
double VBF::DynamicBody::get_mass()        const { return m_mass;   }
btVector3 VBF::DynamicBody::get_inertia()  const { return m_inertia;}
void VBF::DynamicBody::set_gravity(const btVector3 gravity){ m_rbody->setGravity(gravity);  }
btVector3 VBF::DynamicBody::get_position()  {return m_rbody->getCenterOfMassPosition();}

void VBF::DynamicBody::set_linear_vel(const btVector3& pos, const btVector3& linVel){
    btDynamicBody *rbody = this->get_rbody();
    rbody->setLinearVelocity(linVel);
}
