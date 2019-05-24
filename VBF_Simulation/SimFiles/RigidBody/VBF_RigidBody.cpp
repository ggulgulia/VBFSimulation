#include "VBF_RigidBody.hpp"
#include <cmath> //for sin/cos and math functions

//default constructor
VBF::RigidBody::RigidBody():
                m_shape(nullptr),
                m_rbody(nullptr)
                {  }

//user constructor
VBF::RigidBody::RigidBody(const std::string& name, CollShape* shape, btVector3 origin,
                           size_t index):
m_name(name), m_shape(shape), m_origin(origin), m_index(index)
{
    //beautiful process in bullet to create a rigid body
    btTransform trans;
    trans.setIdentity();
    trans.setOrigin(m_origin);
    m_motionState = new MotionState(trans);
    
}

            
//constructor that simply creates a copy of RigidBody 
//by transforming its position (and orientation)   
//desturctor
VBF::RigidBody::~RigidBody(){
            delete m_shape;
            delete m_rbody;
            m_shape = nullptr;
            m_rbody = nullptr;
            }
            
//helper functions                
btRigidBody* VBF::RigidBody::get_rbody() const { return m_rbody; }
btRigidBody* VBF::RigidBody::get_rbody() { return m_rbody; }
std::string VBF::RigidBody::get_name()   const { return "incorrect name"; }
CollShape* VBF::RigidBody::get_shape()   const { return m_shape;  } 
CollShape* VBF::RigidBody::get_shape() { return m_shape;  } 
btVector3 VBF::RigidBody::get_origin()   const { return m_origin; }
size_t VBF::RigidBody::get_index()       const { return m_index;  }
btVector3 VBF::RigidBody::get_cog_position()  {return m_rbody->getCenterOfMassPosition();}
