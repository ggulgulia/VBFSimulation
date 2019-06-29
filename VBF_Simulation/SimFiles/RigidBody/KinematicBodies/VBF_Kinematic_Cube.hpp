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
            /*! @brief Deafault constructor
             *
             * @details This constructor creates a Kinematic Cube of  edge length 10.0 units
             * and the name of this cube is "Default Kinematic Cube"
             */
            Kinematic_Cube();
            explicit Kinematic_Cube(double length, btVector3 origin, size_t index);
            Kinematic_Cube(const Kinematic_Cube&) = delete;
            ~Kinematic_Cube();
            double get_length() const noexcept;
            virtual std::string get_name() const noexcept override final;
    };
}//end of name space

#endif /* ifndef VBF_KINEMATIC_CUBE_H */

