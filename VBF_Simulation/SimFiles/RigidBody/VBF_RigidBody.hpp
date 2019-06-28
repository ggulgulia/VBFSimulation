#ifndef VBF_RIGID_BODY_H
#define VBF_RIGID_BODY_H 

/*! /section intro Introduction This is the parent class for Rigid Body and all different types of 
 * rigid bodies are derived from this class. The objective of this class is to provide a uniform and logical
 * interface for all other classes that are derived from this class. From programming point of view an inheritance
 * chain based on this class obviates the need to use the untidy if-else or switch-case statements
 * that add to a lot of confusion and crates a blob/god class(antipattern)
 *
 * This class and all derived classes from this class don't permit any copy semantics
 */ 

#include <bullet/btBulletDynamicsCommon.h>
#include <string>
#include <bullet/BulletCollision/Gimpact/btGImpactShape.h>
#include <bullet/BulletCollision/Gimpact/btGImpactCollisionAlgorithm.h>
#include <OpenGLWindow/GLInstanceGraphicsShape.h>

/*! Creating typedefs for the ugly type names defined in Bullet Physics
 */
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

            /*! Default explicit constructor.
             * NOTE: right now call to this constructor
             * creates hanging pointers, either resolve this
             * or don't permit call to empty constructor
             */
            explicit RigidBody();
            
            /*! Explicit user constructor. The indices in RigidBodies are introduced for book keeping purposes
             * but at this point I've not figured out a sesible use for the member that stores index
             */
            explicit RigidBody(const std::string& name, CollShape* shape, 
                               btVector3 origin, size_t index=0);
            
            /*! Dreventing copy semantics
             */

            /*! Deleted copy constructor
             */
            RigidBody(const RigidBody& vbf_rb)= delete;

            /*! Deleted copy assignment operator
             */
            RigidBody& operator=(RigidBody&) = delete;
            
            /*!Destructor
             */
            virtual ~RigidBody();
            
            //helper functions
            MotionState* get_motion_state(){return m_motionState;}
            void set_rbody(btRigidBody* rbody){m_rbody = rbody;}
            virtual btRigidBody* get_rbody() const;
            virtual btRigidBody* get_rbody();
            virtual std::string get_name()   const;
            /*! Non-static, constant public member function that returns the 
             * Collision Shape (a bullet type, check the typedef in this file) of the 
             * rigid body. This is needed for getting the origin while the simulation
             * is in progress
             */
            virtual CollShape* get_shape()   const;

            /*! Non-static, non-constant public member function, same as constant version
             * but with the exception that manipulations (setting) through inbuilt bullet
             * physics functions are also permitted
             */
            virtual CollShape* get_shape();

            /*! Non-static constant public member function that returns the 
             * origin of the rigid body
             */
            virtual btVector3 get_origin()   const;

            /*! Non-static constant public member function that returns the index of the 
             * rigid body
             */
            virtual size_t get_index()       const;

            /*! Virtual function that returns the center of gravity of the rigid body.
             * This function internally makes use of the functionality provided by bullet
             * physics engine
             */
            virtual btVector3 get_cog_position();

    };
}//end of name space

#endif /* ifndef VBF_RIGID_BODY_H */

