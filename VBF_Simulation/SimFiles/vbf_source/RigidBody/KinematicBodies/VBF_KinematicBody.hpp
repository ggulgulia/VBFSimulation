#ifndef VBF_KINEMATIC_BODY_H
#define VBF_KINEMATIC_BODY_H 

#include <../VBF_RigidBody.hpp>

namespace VBF{

    
    class KinematicBody : public RigidBody{


        public:

            explicit KinematicBody(const std::string& name, CollShape* shape, btVector3 origin, size_t index);
            KinematicBody(const KinematicBody&) = delete;
            ~KinematicBody();
            
            
            //helper functions
            virtual btVector3 get_position();
            virtual double get_mass() const; 
            virtual btVector3 get_inertia() const;
            virtual void set_linear_vel(const btVector3& linVel);
            virtual btVector3 get_cog_position() const noexcept;
            virtual const btMatrix3x3& get_rotation() const noexcept;

    };
}//end of name space

#endif /* ifndef VBF_KINEMATIC_BODY_H */

