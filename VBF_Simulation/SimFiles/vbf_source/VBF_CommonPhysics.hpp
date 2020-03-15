
#ifndef COMMON_PHYSICS_H
#define COMMON_PHYSICS_H
#include <bullet/LinearMath/btVector3.h>
#include <OpenGL/GLDebugDrawer.h>
#include <VBF_World.hpp>
#include <VBF_RigidBody.hpp>
#include <VBF_Static_Cube.hpp>


/*!  Physics Object should have a VBF::World and the related objects (
 * Physical Bodies, reference ground) in it. 
 * It should have a bridge with the graphics to visualize and 
 * it should be optional to speed up the calculations  when needed.
 * For VBF Simulations, we would like to have a world, a ground 
 * referece and objects in it.
 * Ofcourse physics can be simulated without a ground but I don't 
 * think this is going to make my life easier as it is
 * the documentations are missing  
 */
  namespace VBF{  
    
    class CommonPhysics{
        private:
               VBF::World* m_VBF_world; /*!< Private member pointer to object VBF::World */
               VBF::StaticBody *m_ground; /*!< Reference ground surface (ground is always a static body) */
               std::vector<VBF::RigidBody*> m_VBF_rbody; /*!< Container of pointer to rigid bodies*/
               std::vector<CollShape*> m_shape; /*!< Container to pointers of collision shapes */
        public:
            
            /*! @brief Destructor
             *
             * @details This destructor releases memory held by the 
             * pointer members of the object, including the pointers
             * stored in the member containers and assigns each of the
             * member pointers to nullptr
             *
             * @warning The destructor has not been rigorously tested
             * and hence the corner cases are yet to be determined. 
             * Hence it is recommended not to call the destructor 
             * manually. Let the program call it at the end of main
             */
            virtual ~CommonPhysics();
            
            /*! @brief Default constructor
             *
             * @details Default constructor initializes the members 
             * m_VBF_World and m_ground with a default VBF::World 
             * object and a VBF::Static_Cube object respectively. 
             *
             * @param NONE
             *
             * @warning The default constructor has not been 
             * rigorously tested and hence the corner cases are yet 
             * to be determined. 
             */
            CommonPhysics();
            
            /*! @brief User constructor
             *
             * @details This constructor creates a VBF::CommonPhysics
             * object and appropriately initializes the members  with
             * the parameters passed to it. The body of the 
             * constructor passes the pointer stored in parameter 
             * vbf_rbody_vect to m_VBF_rbody. 
             *
             * @param vbf_world : pointer to VBF::World object
             * @param vbf_rbody_vect : std::vector containing pointers
             * to rigid bodies (that user may wish to simulate).
             * @param ground : pointer to VBF::StaticBody object.
             * @param 
             *
             * @warning The constructor doesn't check the validity of
             * the pointer arguments passed to it. Secondly this 
             * constructor has not been rigorously tested.
             */
            CommonPhysics(VBF::World* vbf_world, VBF::StaticBody* ground, std::vector<VBF::RigidBody*>& vbf_rbody_vect);
            
            /*! @brief Constructor taking only pointer to VBF::World
             * oobject.
             *
             * @details This constructor initializes only the member 
             * m_VBF_world member variable of VBF::World.
             *
             * @param vbf_world : pointer to VBF_World object.
             *
             * @warning This constructor doesn't check the validity of
             * the pointer argument passed to it. Testing needed.
             */
            CommonPhysics(VBF::World* vbf_world);
            
            /*! @brief Constructor initializing m_VBF_World and adding
             * a generic rigid body to the world.
             *
             * @details This constructor initialzes m_VBF_world member
             * variable and adds a single pointer to  VBF::RigidBody 
             * to the m_VBF_rbody container. This constructor provides
             * flexibility to create a rigid body simulation without
             * a ground where the object can perpetually fall under
             * the action of gravity, or float in a lonely universe, 
             * etc.
             *
             * @param vbf_world : pointer to VBF::World object.
             * @param vbf_rbody : pointer to VBF::Rigid body.
             *
             * @warning This constructor doesn't check the validity of
             * the pointer argument passed to it. Testing needed.
             */
            CommonPhysics(VBF::World* vbf_world, VBF::RigidBody* vbf_rbody_vct);
            
            /*! @brief Deleted copy constructor.
             */
            CommonPhysics(const CommonPhysics& comPhy)=delete;
            
            /*! @brief Method to initialize VBF::CommonPhysics object.
             *
             * @details Non-static public method that initializes the
             * this object. This is a recommended method to initialize
             * the physics for VBF simulation.
             *
             * @param NONE
             *
             * @warning This method doesn't check if the remaining 
             * pointers in the object have been initialized. TODO :
             * implement a layer of safety check.
             */
    	    void initPhysics();
            
            /*! @brief Steps the simulation in time. 
             *
             * @details This method steps the physical time by an 
             * amount specified in the parameter. 
             *
             * NOTE : Internally this method calls the stepSimulation
             * method of the member variable m_VBF::World (see docume
             * ntation for VBF::World).
             *
             * @param deltaT : time step 
             * @param resolution : internal substeps to compute the physics. 
             *                     Number of substesp = deltaTime/resolution
             *                     Default value of resolution = 1/60f
             *
             * @todo implement other overladed variants of 
             * stepSimulation defined in bullet and VBF::World
             */
    	    void step_simulation(double deltaTime, double resolution=0.0166667);
            
            /*! @brief Sets debug draw flags
             *
             * @details This method has been adopted directly from
             * one of the demo example  code of bullet physics 
             * library. The example code did not explain what is 
             * happening but I figured this is important for the 
             * graphics to show up.
             *
             * NOTE : I could not find a documentation of the 
             * debugDrawFlags. Specifically what integer value means
             * what is still unknown.
             * @param debugDrawFlag : integer value of debugDrawFalg
             *
             * @warning The method is not usefult if the VBF::World is
             * not initialized. Need proper exception handling for 
             * this method. 
             */
            void debugDraw(int debugDrawFlags);
            
            /*! @brief TODO
             *
             * @details TODO
             *
             * @param NONE
             *
             * @warning TODO
             */
    	    void syncPhysicsToGraphics();
            
            /*! @brief Returns the btWorld (bullet) object
             *
             * @details Non-static public member method that returns
             * the encapsulated VBF::World::m_world (of type bullet)
             * object. This could be useful if the user wants to 
             * change the value of gravity for example. 
             *
             * @warning The method doesn't check the validity of 
             * underlying pointer that it is returning. TODO
             */
            virtual btWorld* get_world() const;
            
            void init_physics(VBF::World* vbf_world, VBF::StaticBody* ground, std::vector<VBF::RigidBody*>& vbf_rbody_vect);
    };

}

#endif //COMMON_PHYSICS_H
