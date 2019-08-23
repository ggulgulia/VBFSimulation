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
typedef btDefaultMotionState MotionState; //!< typedef for bullet type btDefaultMotionstate
typedef btRigidBody::btRigidBodyConstructionInfo btRbConstrInfo; //!< typedef for bullet btRigidBody::btRigidBodyConstructorInfo
typedef btCollisionShape CollShape; //!< typefef for bullet btCollisionShape

namespace VBF{

    class RigidBody{

        private:
            std::string m_name; //!< Name of the VBF::RigidBody (eg. Sphere, Cube, etc).
            CollShape* m_shape; //!< Collision shape encapsulated in the VBF::RigidBody
            btVector3 m_origin; //!< Origin vector of the VBF::RigidBody
            double m_collisionMargin{0.004};
            size_t m_index;     //!< Index of VBF::RigidBody for book keeping purpose
            MotionState *m_motionState; //!< Motion state of VBF::RigidBody 
            btRigidBody *m_rbody; //!< Bullet btRigidBody encapsulated in the VBF::RigidBody 

        public:

            /*! Default explicit constructor.
             * NOTE: right now call to this constructor
             * creates hanging pointers, either resolve this
             * or don't permit call to empty constructor
             */
            explicit RigidBody();
            
            /*! @brief Explicit user constructor. 
             * @details The indices in RigidBodies are introduced for book keeping purposes
             * but at this point I've not figured out a sensible use for the member that stores index.
             * This consttructor is not meant to be called on its own but is called by one of the 
             * classes inheriting from RigidBody class
             *
             * @param name   Name of the rigid body
             * @param shape  Collision Shape (bullet type) that the rigid body encompasses
             * @param origin Origin of the rigid body
             * @param index  index of the rigid body for book keeping purpose
             *
             * @return NONE
             */
            explicit RigidBody(const std::string& name, CollShape* shape, 
                               btVector3 origin, const double collMarg, size_t index=0);
            

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
            
            /*! @brief Returns the motion state of rigid body
             *
             * @details Non-static, non-constant public member function. 
             * The method is guaranteed to not throw. This method takes in no arguments
             * @returns motion state of the RigidBody
             */
            MotionState* get_motion_state()noexcept;

            /*! @brief assigns the private member m_rbody an appropriate rigid body 
             *
             * @param valid pointer to btRigidBody
             * @return NONE
             */
            void set_rbody(btRigidBody* rbody);
            
            /*! @brief returns the bullet rigid body data structure encapsulated within VBF::RigidBody
             *  @details Non-Static constant member function returning the bullet rigid body. This method
             *  can be called by other constant methods or when only read-only access to the 
             *  rigid body is desired.
             *
             *  @param NONE
             *  @return VBF::RigidBody private member data : (bullet) btRigidbody (Non-modifiable)
             */
            virtual btRigidBody* get_rbody() const noexcept ;

            /*! @brief Same as constant member function but returns a modifiable btRigidbody encapsulated in VBF::RigidBody
             */

            void set_collision_margin(const double collMargin){
                m_collisionMargin = collMargin;
            }

            double get_collision_margin();

            virtual btRigidBody* get_rbody() noexcept;

            /*! @breif Non-static public member function returning the name of the VBF::RigidBody
             *
             * @param NONE
             * @return RigidBody private member data : m_name (Non-modifiable)
             */
            virtual std::string get_name() const noexcept;

            /*! @breif Returns the collision shape encapsulated within the VBF::RigidBody
             *
             * @details Non-static, constant public member function that returns the 
             * Collision Shape (a bullet type, check the typedef in this file) of the 
             * rigid body. This is needed for getting the origin while the simulation
             * is in progress. The shapes can be Cubes, Sphere or imported triangular 
             * mesh shapes
             *
             * @param NONE
             *
             * @returns CollShape (non-modifiable)
             */
            virtual CollShape* get_shape() const noexcept;

            /*! @brief Returns the collision shape encapsulated within VBF::RigidBody
             *
             * @details Non-static, non-constant public member function, same as constant version
             * but with the exception that manipulations (setting) through inbuilt bullet
             * physics functions are also permitted.
             * 
             * @param NONE
             *
             * @returns CollShape (modifiable)
             */
            virtual CollShape* get_shape()noexcept;

            /*! Non-static constant public member function that returns the 
             * origin of the rigid body
             * @param NONE
             * @returns origin
             */
            virtual btVector3 get_origin() const noexcept;

            /*! @brief Returns the index of the VBF::RigidBody
             * @details Non-static constant public member function that returns the index of the 
             * VBF::RigidBody
             *
             * @param NONE
             *
             * @returns index
             */
            virtual size_t get_index() const noexcept;

            /*! \brief returns the (vector) location of cog of the rigid body
             *
             * Non-static, non-constant public virtual function that returns the center of gravity of the rigid body.
             * This function internally makes use of the functionality provided by bullet
             * physics engine
             *
             * \returns private data member : m_rbody (btRigidBody) 
             */
            virtual btVector3 get_cog_position() const noexcept = 0;

            virtual const btMatrix3x3& get_rotation() const noexcept = 0;

    };

}//end of name space

#endif /* ifndef VBF_RIGID_BODY_H */

