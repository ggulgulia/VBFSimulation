#include "VBF_RigidBodies.hpp"

//default constructor
VBF::RigidBody::RigidBody():
                m_shape(nullptr),
                m_rbody(nullptr)
                {  }

//user constructor
VBF::RigidBody::RigidBody(std::string name, CollShape* shape, btVector3 origin, double mass, btVector3 inertia, size_t index):
m_name(name), m_shape(shape), m_origin(origin), 
m_mass(mass), m_inertia(inertia), m_index(index)
{
    //beautiful process in bullet to create a rigid body
    if(m_mass >0.0){
        m_shape->calculateLocalInertia(m_mass, m_inertia);
    }
    btTransform shapeTransform;
    MotionState *motionState;
    shapeTransform.setIdentity();
    shapeTransform.setOrigin(m_origin);
    motionState = new MotionState(shapeTransform);
    
    btRbConstrInfo rbinfo(m_mass, motionState, m_shape, m_inertia);
    m_rbody = new btRigidBody(rbinfo);
}

//copy Constructor
VBF::RigidBody::RigidBody(const RigidBody& vbf_rb):
                m_name(vbf_rb.get_name()),
                m_shape(vbf_rb.get_shape()),
                m_origin(vbf_rb.get_origin()), 
                m_mass(vbf_rb.get_mass()),
                m_inertia(vbf_rb.get_inertia()), 
                m_index(vbf_rb.get_index()+1),
                m_rbody(vbf_rb.get_rbody())
                { //empty copy constructor body
                 }
            
//constructor that simply creates a copy of RigidBody 
//by transforming its position (and orientation)   
VBF::RigidBody::RigidBody(const RigidBody& rbody, btVector3 origin):
                RigidBody(rbody) //call the copy constructor
                {
                    m_origin = origin; //
                    btTransform shapeTransform;
                    shapeTransform.setIdentity();
                    shapeTransform.setOrigin(m_origin);
                    MotionState *motionState = new MotionState(shapeTransform);
                    btRbConstrInfo rbinfo(m_mass, motionState, m_shape, m_inertia);
                    m_rbody = new btRigidBody(rbinfo);
                }
//desturctor
VBF::RigidBody::~RigidBody(){
            delete m_shape;
            delete m_rbody;
            m_shape = nullptr;
            m_rbody = nullptr;
            }
            
//helper functions                
btRigidBody* VBF::RigidBody::get_rbody() const { return m_rbody; }
std::string VBF::RigidBody::get_name()   const { return "incorrect name"; }
CollShape* VBF::RigidBody::get_shape()   const { return m_shape;  } 
btVector3 VBF::RigidBody::get_origin()   const { return m_origin; }
double VBF::RigidBody::get_mass()        const { return m_mass;   }
btVector3 VBF::RigidBody::get_inertia()  const { return m_inertia;}
size_t VBF::RigidBody::get_index()       const { return m_index;  }
