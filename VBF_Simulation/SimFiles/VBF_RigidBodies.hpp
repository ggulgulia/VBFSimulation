#ifndef VBF_RIGID_BODIES_H
#define VBF_RIGID_BODIES_H 

#include <bullet/btBulletDynamicsCommon.h>
#include <string>

typedef btDefaultMotionState MotionState;
typedef btRigidBody::btRigidBodyConstructionInfo btRbConstrInfo;
typedef btCollisionShape CollShape;

namespace VBF{

    class RigidBody{

        private:
            std::string m_name;
            CollShape* m_shape;
            btVector3 m_origin;
            btTransform m_shapeTransform;
            double m_mass;
            btVector3 m_inertia;
            size_t m_index; //might be helpful for book keeping 
                            //when there are many rigid bodies
            btRigidBody *m_rbody;

            //dynamic properties of the rigid body
            //they go in rbconstrinfo
            double m_frictionCoeff;
            double m_rollingFriction;
            double m_restitutionCoeff;
            double m_linearDamping;
            double m_angularDamping;
        public:

            //default constructor
            //note right now call to this constructor
            //creates hanging pointers, either resolve this
            //or don't permit call to empty constructor
            explicit RigidBody();
            //user constructor
            explicit RigidBody(std::string name, CollShape* shape, btVector3 origin,
                               btTransform shapeTransform, double mass, btVector3 inertia, 
                               double linFriction=0.5, double rollingFriction=0.5, 
                               double restitution=0.2, double linDamping=0.0, 
                               double angularDamping=0.0, size_t index=0);
            
            //copy Constructor
            RigidBody(const RigidBody& vbf_rb);
            
            //constructor that simply creates a copy of RigidBody 
            //by transforming its position (and orientation)   
            RigidBody(const RigidBody& rbody, btVector3 origin);
            
            //destructor
            virtual ~RigidBody();
            
            //helper functions
            virtual btRigidBody* get_rbody() const;
            virtual btRigidBody* get_rbody();
            virtual std::string get_name()   const;
            virtual CollShape* get_shape()   const;
            virtual btVector3 get_origin()   const;
            virtual double get_mass()        const;
            virtual btVector3 get_inertia()  const;
            virtual size_t get_index()       const;
            virtual void set_gravity(const btVector3 gravity= btVector3(0.0,-9.81, 0.0));
            virtual btVector3 get_cog_position();

            virtual void set_linear_vel(const btVector3& pos, const btVector3& linVel);
            //virtual void set_angular_vel(const btVector3& axis, const btVector3& angVel);
    };
}//end of name space

#endif /* ifndef VBF_RIGID_BODIES_H */

