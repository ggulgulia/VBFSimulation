#ifndef VBF_SPHERE_H
#define VBF_SPHERE_H 

#include <bullet/btBulletDynamicsCommon.h>
#include <string>
#include "VBF_RigidBodies.hpp"

typedef btDefaultMotionState MotionState;
typedef btRigidBody::btRigidBodyConstructionInfo btRbConstrInfo;
typedef btCollisionShape CollShape;

namespace VBF{


    class Sphere: public RigidBody{
        
        private:
            double m_radius;

        public:

            explicit Sphere(double radius, btVector3 origin, btVector3 inertia, double mass, size_t index);         
            Sphere(const Sphere& sphere, btVector3 origin);             
            ~Sphere();

            virtual std::string get_name();
            double get_radius() const { return m_radius;}
    };

}//end of name space

#endif /* ifndef VBF_SPHERE_BODIES_H */

