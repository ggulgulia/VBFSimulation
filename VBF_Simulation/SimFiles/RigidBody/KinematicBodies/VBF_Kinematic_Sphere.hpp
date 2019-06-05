#ifndef VBF_KINEMATIC_SPHERE_H
#define VBF_KINEMATIC_SPHERE_H 

#include <VBF_KinematicBody.hpp>

typedef btDefaultMotionState MotionState;
typedef btRigidBody::btRigidBodyConstructionInfo btRbConstrInfo;
typedef btCollisionShape CollShape;

namespace VBF{


    class Kinematic_Sphere: public KinematicBody{
        
        private:
            double m_radius;

        public:

            explicit Kinematic_Sphere(double radius, btVector3 origin, size_t index);         
            ~Kinematic_Sphere();

            //preventing copy semantics
            Kinematic_Sphere(const Kinematic_Sphere&) = delete;
            Kinematic_Sphere& operator=(Kinematic_Sphere&) = delete;

            virtual std::string get_name() const override final;
            double get_radius() const { return m_radius;}
    };

}//end of name space

#endif /* ifndef VBF_SPHERE_BODIES_H */

