#ifndef VBF_STATIC_SPHERE_H
#define VBF_STATIC_SPHERE_H 

#include <VBF_StaticBody.hpp>

typedef btDefaultMotionState MotionState;
typedef btRigidBody::btRigidBodyConstructionInfo btRbConstrInfo;
typedef btCollisionShape CollShape;

namespace VBF{


    class Static_Sphere: public StaticBody{
        
        private:
            double m_radius;

        public:

            explicit Static_Sphere(double radius, btVector3 origin, size_t index);         
            ~Static_Sphere();

            virtual std::string get_name() const override final;
            double get_radius() const { return m_radius;}
    };

}//end of name space

#endif /* ifndef VBF_SPHERE_BODIES_H */

