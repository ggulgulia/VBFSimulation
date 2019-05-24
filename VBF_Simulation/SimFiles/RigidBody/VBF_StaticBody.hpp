#ifndef VBF_STATIC_BODY_H
#define VBF_STATIC_BODY_H 

#include "VBF_RigidBody.hpp"

typedef btDefaultMotionState MotionState;
typedef btRigidBody::btRigidBodyConstructionInfo btRbConstrInfo;
typedef btCollisionShape CollShape;

namespace VBF{

    
    class StaticBody : public RigidBody{


        public:

            explicit StaticBody(const std::string& name, CollShape* shape, btVector3 origin, size_t index);
            StaticBody(const StaticBody&) = delete;
            ~StaticBody();
            virtual double get_mass(){return 0.0;}

    };
}//end of name space

#endif /* ifndef VBF_STATIC_BODY_H */
