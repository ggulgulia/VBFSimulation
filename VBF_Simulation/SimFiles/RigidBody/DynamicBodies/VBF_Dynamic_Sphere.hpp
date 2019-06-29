#ifndef DYNAMIC_SPHERE_H
#define DYNAMIC_SPHERE_H 

#include <VBF_DynamicBody.hpp>

typedef btDefaultMotionState MotionState;
typedef btRigidBody::btRigidBodyConstructionInfo btRbConstrInfo;
typedef btCollisionShape CollShape;

namespace VBF{

    
    class Dynamic_Sphere : public DynamicBody{

        private:
            double m_radius;

        public:
            
            //user constructor
            explicit Dynamic_Sphere(double radius, btVector3 origin, 
                                  double mass, 
                                  double linFriction=0.5, double rollingFriction=0.5, 
                                  double restitution=0.2, double linDamping=0.0, 
                                  double angularDamping=0.0, size_t index=221);

            //below two lines prevent expensive copy semantics
            Dynamic_Sphere(const Dynamic_Sphere&) = delete;
            Dynamic_Sphere& operator=(Dynamic_Sphere&) = delete;

            //Destructor
            ~Dynamic_Sphere();
            virtual std::string get_name() const noexcept override final;

    };
}//end of name space

#endif /* ifndef DYNAMIC_CUBE_H */

