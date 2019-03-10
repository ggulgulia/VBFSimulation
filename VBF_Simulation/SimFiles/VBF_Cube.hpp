#ifndef VBF_CUBE_H
#define VBF_CUBE_H 

#include <bullet/btBulletDynamicsCommon.h>
#include <string>
#include "VBF_RigidBodies.hpp"

typedef btDefaultMotionState MotionState;
typedef btRigidBody::btRigidBodyConstructionInfo btRbConstrInfo;
typedef btCollisionShape CollShape;

namespace VBF{

    
    class Cube : public RigidBody{

        private:
            double m_length;

        public:

            explicit Cube(double length, btVector3 origin, btTransform shapeTrans, btVector3 inertia, double mass, size_t index);
            
            Cube(const Cube& cube, btVector3 origin);

            ~Cube();
            virtual std::string get_name() const override final;
            double get_length() const { return m_length;}
    };


}//end of name space

#endif /* ifndef VBF_CUBE_H */

