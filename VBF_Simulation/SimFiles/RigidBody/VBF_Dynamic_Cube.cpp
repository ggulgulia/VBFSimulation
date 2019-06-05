#include "VBF_Static_Cube.hpp"



//Static_Cube Class Definitions
VBF::Static_Cube::Static_Cube(double length, btVector3 origin, btTransform shapeTrans, btVector3 inertia, double mass, size_t index):
               RigidBody(std::string("Static_Cube"),
               (new btBoxShape(btVector3(length, length, length))),
               origin, shapeTrans, mass, inertia, index),
               m_length(length){
                        
                MotionState* moSt = RigidBody::get_motion_state();
                CollShape* shape = RigidBody::get_shape();
                double mass2 = 0.0;
                btVector3 inertia2(btVector3(0.0, 0.0, 0.0));
                btRbConstrInfo rbinfo(mass2, moSt, shape, inertia2);
                btRigidBody* rbody = new btRigidBody(rbinfo);
                RigidBody::set_rbody(rbody);
                //empty constructor body
               }

//destructor
VBF::Static_Cube::~Static_Cube(){};

std::string VBF::Static_Cube::get_name() const { return "Static_Cube"; }

