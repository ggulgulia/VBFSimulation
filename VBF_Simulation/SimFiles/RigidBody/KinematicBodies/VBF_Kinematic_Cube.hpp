#ifndef VBF_KINEMATIC_CUBE_H
#define VBF_KINEMATIC_CUBE_H 

#include <VBF_KinematicBody.hpp>

typedef btDefaultMotionState MotionState;
typedef btRigidBody::btRigidBodyConstructionInfo btRbConstrInfo;
typedef btCollisionShape CollShape;

namespace VBF{
    
    class Kinematic_Cube : public KinematicBody{

        private:
            double m_length;

        public:
            Kinematic_Cube(): KinematicBody("Default Kinematic Cube", 
                          new btBoxShape(btVector3(10.0, 10.0, 10.0)),
                          btVector3(0.0,0.0, 0.0), 23), 
            m_length(10.0){
                            //empty constructor body
            }

            explicit Kinematic_Cube(double length, btVector3 origin, size_t index);
            Kinematic_Cube(const Kinematic_Cube&) = delete;
            ~Kinematic_Cube();
            double get_length() const;
    };
}//end of name space

#endif /* ifndef VBF_KINEMATIC_CUBE_H */

