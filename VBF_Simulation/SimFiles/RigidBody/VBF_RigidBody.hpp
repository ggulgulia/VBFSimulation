#ifndef VBF_RIGID_BODY_H
#define VBF_RIGID_BODY_H 

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
            size_t m_index; //might be helpful for book keeping 
                            //when there are many rigid bodies
            MotionState *m_motionState;
            btRigidBody *m_rbody;

        public:

            //default constructor
            //note right now call to this constructor
            //creates hanging pointers, either resolve this
            //or don't permit call to empty constructor
            explicit RigidBody();
            //user constructor
            explicit RigidBody(const std::string& name, CollShape* shape, 
                               btVector3 origin, size_t index=0);
            
            //copy Constructor
            RigidBody(const RigidBody& vbf_rb)= delete;
            
            //destructor
            virtual ~RigidBody();
            
            //helper functions
            MotionState* get_motion_state(){return m_motionState;}
            void set_rbody(btRigidBody* rbody){m_rbody = rbody;}
            virtual btRigidBody* get_rbody() const;
            virtual btRigidBody* get_rbody();
            virtual std::string get_name()   const;
            virtual CollShape* get_shape()   const;
            virtual CollShape* get_shape();
            virtual btVector3 get_origin()   const;
            virtual size_t get_index()       const;
            virtual btVector3 get_cog_position();

    };
}//end of name space

#endif /* ifndef VBF_RIGID_BODY_H */
