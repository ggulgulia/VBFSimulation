#include "VBF_RigidBodies.hpp"
#include <cmath> //for sin/cos and math functions

//default constructor
VBF::RigidBody::RigidBody():
                m_shape(nullptr),
                m_motionState(nullptr),
                m_rbody(nullptr)
{
    m_origin = btVector3(0.0, 0.0, 0.0);
    m_index = 0;
    btTransform shapeTrans;
    shapeTrans.setOrigin(m_origin);
    m_motionState = new MotionState(shapeTrans);
}


//user constructor
VBF::RigidBody::RigidBody(const std::string& name, CollShape* shape, btVector3 origin, size_t index):
m_name(name), m_shape(shape), m_origin(origin), 
    m_index(index){
        btTransform shapeTrans;
        shapeTrans.setOrigin(m_origin);
        m_motionState = new MotionState(shapeTrans);
    }

            
//constructor that simply creates a copy of RigidBody 
//by transforming its position (and orientation)   
//desturctor
VBF::RigidBody::~RigidBody(){
            delete m_shape;
            m_shape = nullptr;
            }
            
//helper functions                
void VBF::RigidBody::setName(const std::string& name){m_name = name;}
void VBF::RigidBody::applyShape(CollShape *const shape){m_shape = shape;}
void VBF::RigidBody::set_rbody(btRigidBody* rbody){m_rbody = rbody;}
std::string VBF::RigidBody::get_name() const { return "incorrect name"; }
CollShape* VBF::RigidBody::get_shape() const { return m_shape;  } 
CollShape* VBF::RigidBody::get_shape() { return m_shape;  } 
btVector3 VBF::RigidBody::get_origin()  const { return m_origin; }
btRigidBody* VBF::RigidBody::get_rbody() const { return m_rbody;  }
btRigidBody* VBF::RigidBody::get_rbody() { return m_rbody;}
MotionState* VBF::RigidBody::get_motion_state() const{return m_motionState;}
MotionState* VBF::RigidBody::get_motion_state() {return m_motionState;}
size_t VBF::RigidBody::get_index()       const { return m_index;  }
