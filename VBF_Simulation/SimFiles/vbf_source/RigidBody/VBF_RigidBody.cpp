#include <VBF_RigidBody.hpp>
#include <cmath> //for sin/cos and math functions

//default constructor
VBF::RigidBody::RigidBody():
                m_shape(nullptr),
                m_rbody(nullptr)
                {  }

//user constructor
VBF::RigidBody::RigidBody(const std::string& name, CollShape* shape, btVector3 origin,
                          const double collMarg, size_t index):
m_name(name), m_shape(shape), m_origin(origin), 
m_collisionMargin(collMarg), m_index(index)
{
    //beautiful process in bullet to create a rigid body
    m_shape->setMargin(m_collisionMargin);
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
MotionState* VBF::RigidBody::get_motion_state() noexcept {return m_motionState;}

void VBF::RigidBody::set_rbody(btRigidBody* rbody){
    if(rbody == nullptr){
        throw "Bad pointer. Please check the pointer to rigid body\n";
    }
    else
        m_rbody = rbody;
}
btRigidBody* VBF::RigidBody::get_rbody() const noexcept { return m_rbody; }
btRigidBody* VBF::RigidBody::get_rbody()noexcept { return m_rbody; }
double VBF::RigidBody::get_collision_margin(){
    return m_collisionMargin;
}

std::string VBF::RigidBody::get_name() const noexcept { return "incorrect name"; }
CollShape* VBF::RigidBody::get_shape() const noexcept { return m_shape;  } 
CollShape* VBF::RigidBody::get_shape() noexcept { return m_shape;  } 
btVector3 VBF::RigidBody::get_origin()   const noexcept { return m_origin; }
size_t VBF::RigidBody::get_index()       const noexcept { return m_index;  }

