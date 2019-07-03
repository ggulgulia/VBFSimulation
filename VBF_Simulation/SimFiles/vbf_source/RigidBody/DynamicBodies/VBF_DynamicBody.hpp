#ifndef VBF_DYNAMIC_BODY_H
#define VBF_DYNAMIC_BODY_H 

#include <../VBF_RigidBody.hpp>

namespace VBF{

    class DynamicBody : public RigidBody{

        private:
            double m_mass;
            btVector3 m_inertia;
                            //when there are many rigid bodies

            //dynamic properties of the rigid body
            //they go in rbconstrinfo
            double m_frictionCoeff;
            double m_rollingFriction;
            double m_restitutionCoeff;
            double m_linearDamping;
            double m_angularDamping;
        public:

            //user constructor
            explicit DynamicBody(std::string name, CollShape* shape, 
                                 btVector3 origin, double mass, 
                                 double linFriction=0.5, double rollingFriction=0.5, 
                                 double restitution=0.2, double linDamping=0.0, 
                                 double angularDamping=0.0, size_t index=200);
            
            //preventing implicit copy Constructor
            DynamicBody(const RigidBody& vbf_rb) = delete;
            
            //destructor
            virtual ~DynamicBody();
            
            //helper functions
            virtual double get_mass()        const;
            virtual btVector3 get_inertia()  const;
            virtual void set_gravity(const btVector3 gravity= btVector3(0.0,-9.81, 0.0));
            virtual btVector3 get_position();
            virtual void set_linear_vel(const btVector3& pos, const btVector3& linVel);
            //virtual void set_angular_vel(const btVector3& axis, const btVector3& angVel);
    };
}//end of name space

#endif /* ifndef VBF_RIGID_BODIES_H */

