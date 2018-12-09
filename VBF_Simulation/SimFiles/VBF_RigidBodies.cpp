#include "VBF_RigidBodies.hpp"

//default constructor
VBF::RigidBody::RigidBody(){  }

//user constructor
VBF::RigidBody::RigidBody(std::string name, VBF_Shape* shape, btVector3 origin, double mass, btVector3 inertia, size_t index):
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

btRigidBody* VBF::RigidBody::get_rbody() const { return m_rbody; }
std::string VBF::RigidBody::get_name() const { return "incorrect name"; }
/*************************************************************************************************/
/************************** END OF DEFINITIONS FOR Class VBF::RigidBody **************************/
/*************************************************************************************************/



//Cube Class Definitions
VBF::Cube::Cube(double length, btVector3 origin, btVector3 inertia, double mass, size_t index)
                   :m_length(length), RigidBody(std::string("Cube"),
                   (new btBoxShape(btVector3(length, length, length))),
                   origin, mass, inertia, index)
{
    //empty constructor body
}

VBF::Cube::~Cube(){};

std::string VBF::Cube::get_name(){ return "Cube"; }
/*************************************************************************************************/
/***************************** END OF DEFINITIONS FOR Class VBF::Cube ****************************/
/*************************************************************************************************/



//Sphere Class Definitions
VBF::Sphere::Sphere(double radius, btVector3 origin, btVector3 inertia, double mass, size_t index)
                :m_radius(radius), RigidBody(std::string("Sphere"),
                (new btSphereShape(radius)),
                origin, mass, inertia, index)
{
    //empty constructor body
}

VBF::Sphere::~Sphere() {};
std::string VBF::Sphere::get_name(){ return "Sphere"; }
/*************************************************************************************************/
/**************************** END OF DEFINITIONS FOR Class VBF::Sphere ***************************/
/*************************************************************************************************/
