#ifndef VBF_CUBE_H
#define VBF_CUBE_H 

#include <bullet/btBulletDynamicsCommon.h>
#include <string>
#include "VBF_RigidBodies.hpp"

typedef btDefaultMotionState MotionState;
typedef btRigidBody::btRigidBodyConstructionInfo btRbConstrInfo;
typedef btCollisionShape CollShape;

namespace VBF{

    
    class Static_Cube : public RigidBody{

        private:
            double m_length;

        public:

            explicit Static_Cube(double length, btVector3 origin, size_t index);
            Static_Cube(const Static_Cube&) = delete;
            ~Static_Cube();
            virtual std::string get_name() const override final;

    };
}//end of name space

#endif /* ifndef VBF_CUBE_H */

