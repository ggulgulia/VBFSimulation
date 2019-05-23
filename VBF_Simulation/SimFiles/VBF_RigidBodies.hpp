#ifndef VBF_RIGID_BODIES_H
#define VBF_RIGID_BODIES_H 

#include <bullet/btBulletDynamicsCommon.h>
#include <string>
#include <cmath>

typedef btDefaultMotionState MotionState;
typedef btRigidBody::btRigidBodyConstructionInfo btRbConstrInfo;
typedef btCollisionShape CollShape;

namespace VBF{

    class RigidBody{

        private:
            std::string m_name;
            CollShape* m_shape;
            btVector3 m_origin;
            MotionState* m_motionState;
            size_t m_index;
            btRigidBody* m_rbody;
        public:

            explicit RigidBody();
            //user constructor
            explicit RigidBody(const std::string& name, CollShape* shape, 
                               btVector3 origin = btVector3(0.0,0.0, 0.0) , size_t index=0);
            
            //preventing implicit copy Constructor
            RigidBody(const RigidBody& vbf_rb) = delete;
            
            //destructor
            virtual ~RigidBody();
            
            //helper functions
            virtual void setName(const std::string& name);
            virtual void applyShape(CollShape *const shape);
            void set_rbody(btRigidBody* rbody);
            std::string get_name()   const;
            CollShape* get_shape()   const;
            CollShape* get_shape();
            btVector3 get_origin()   const;
            btRigidBody* get_rbody() const;
            btRigidBody* get_rbody();
            MotionState* get_motion_state() const;
            MotionState* get_motion_state();
            size_t get_index()       const;
            virtual btVector3 get_position() = 0;
            virtual double get_mass() const = 0;
            virtual btVector3 get_inertia() const = 0;
    };
}//end of name space

#endif /* ifndef VBF_RIGID_BODIES_H */

