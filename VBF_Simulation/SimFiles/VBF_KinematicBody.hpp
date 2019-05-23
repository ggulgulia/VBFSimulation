#ifndef VBF_KINEMATIC_BODY_H
#define VBF_KINEMATIC_BODY_H 

#include "VBF_RigidBodies.hpp"

namespace VBF{

    class KinematicBody : public RigidBody{

        public:

            //default constructor
            //note right now call to this constructor
            //creates hanging pointers, either resolve this
            //or don't permit call to empty constructor
            explicit KinematicBody();
            //user constructor
            explicit KinematicBody(const std::string& name, CollShape* shape, btVector3 origin,
                               size_t index=0);
            
            //prevent implicit copy Constructor
            KinematicBody(const KinematicBody& vbf_rb) = delete;
            
            //destructor
            virtual ~KinematicBody();
            
            //helper functions
            virtual btVector3 get_position();
            virtual double get_mass() const; 
            virtual btVector3 get_inertia() const;
            virtual void set_linear_vel(const btVector3& pos, const btVector3& linVel);
            //virtual void set_angular_vel(const btVector3& axis, const btVector3& angVel);
    };
}//end of name space

#endif /* ifndef VBF_KINEMATIC_BODY_H */

