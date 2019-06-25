#ifndef VBF_STATIC_CUBE_H
#define VBF_STATIC_CUBE_H 

#include <bullet/btBulletDynamicsCommon.h>
#include <string>
#include "VBF_StaticBody.hpp"

typedef btDefaultMotionState MotionState;
typedef btRigidBody::btRigidBodyConstructionInfo btRbConstrInfo;
typedef btCollisionShape CollShape;

namespace VBF{
    
    class Static_Cube : public StaticBody{

        private:
            double m_length;

        public:
            Static_Cube(): StaticBody("Default Static Cube", 
                          new btBoxShape(btVector3(10.0, 10.0, 10.0)),
                          btVector3(0.0,0.0, 0.0), 23), 
            m_length(10.0){
                            //empty constructor body
            }

            explicit Static_Cube(double length, btVector3 origin, size_t index);
            Static_Cube(const Static_Cube&) = delete;
            ~Static_Cube();
            double get_length() const;
    };
}//end of name space

#endif /* ifndef VBF_STATIC_CUBE_H */

