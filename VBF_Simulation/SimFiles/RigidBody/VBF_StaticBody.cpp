#include "VBF_StaticBody.hpp"



//StaticBody Class Definitions
VBF::StaticBody::StaticBody(const std::string& name, CollShape* shape, btVector3 origin, size_t index):
               RigidBody(name, shape, origin, index){
                        
                MotionState* moSt = RigidBody::get_motion_state();
                double mass = 0.0;
                btVector3 inertia(btVector3(0.0, 0.0, 0.0));
                btRbConstrInfo rbinfo(mass, moSt, shape, inertia);
                btRigidBody* rbody = new btRigidBody(rbinfo);
                RigidBody::set_rbody(rbody);
                //empty constructor body
               }

//destructor
VBF::StaticBody::~StaticBody(){};


