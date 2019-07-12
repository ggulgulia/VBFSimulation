#ifndef VBF_WORLD_H
#define VBF_WORLD_H 

#include <bullet/LinearMath/btVector3.h>
#include <bullet/btBulletDynamicsCommon.h>
#include <bullet/LinearMath/btIDebugDraw.h>
#include <OpenGL/GLDebugDrawer.h>
#include <iostream>
#include <vector>
#include <memory>

/*! typedefs to remove long cumbersome names */
typedef btDiscreteDynamicsWorld btWorld; /*!< typedef for btDiscreteDynamicsWorld */
typedef btDefaultCollisionConfiguration btCollConfig; /*!< typedef for btCollisionConfig */
typedef btCollisionDispatcher btDispatcher_iwb; /*!< typedef for collision dispatcher */
typedef btBroadphaseInterface btInterface; /*!< typedef for btBroadPhaseInterface */
typedef btSequentialImpulseConstraintSolver btSolver; /*!< typedef for btSequentialImpulseConstraintSolver */
typedef btRigidBody::btRigidBodyConstructionInfo btRbConstrInfo; /*!< typedef for btRigidBody::RigidBodyConstrutorInfo */

namespace VBF{

    /*! @brief Physical domain where interactions take place
     *
     * @details VBF::World is an object predefined for VBF computations
     * and all related solvers and collision configurations are established 
     * in this class. For a VBF simulation, it is recommended to declare and 
     * initialize a VBF::World object before proceeding to set up physics and
     * creating 
     */
    class World {
        
        private:
            btWorld* m_world; /*!< member of type btWorld (bullet object) encapsulated within VBF::World */
            btCollConfig* m_collisionConfig; /*!< Collision configuraation encapsulated in VBF::World */
            btDispatcher_iwb* m_dispatcher;  /*!< Member of type btCollisionDispatcher (bullet object) encapsulated in VBF::World */
            btInterface* m_interface; /*!< Member of type btInterface (bullet object) encapsulated in VBF::World */
            btSolver* m_solver; /*!< Member of type btSolver (bullet object) encapsulated in VBF::World */
            bool m_is_initialized; /*!< Boolean member to verify if the VBF::World object is initialized */
            long double m_time;
    
            /*! @brief Advances the simulation in time.
             *
             * @details Non-static private member method that advances
             * the simulation in time determined by timeStep. This method is
             * called internally by the public member functions that are
             * overloaded by the same name
             *
             * source : https://stackoverflow.com/questions/12778229/what-does-step-mean-in-stepsimulation-and-what-do-its-parameters-mean-in-bulle
             * @param timeStep : Time (in seconds) by which the simulation is advanced
             * @param maxSubStep : Maximum number of substesp bullet is allowed to take each time 
             *                     Step simulation is called (keep it fixed to 1)
             * @param fixedTimeStep : Resolution of simulation. Decrease the value to inscrease the simulation 
             *                        resolution
             *
             * @returns 
             * @warning maxSubStep should be kept to 1.0 . (read the source)
             */
            void step_simulation(double deltaT1, double maxSubStep, double resolution){

            
                    m_world->stepSimulation(deltaT1, maxSubStep, resolution);
                    m_time += deltaT1;
            }
            /*! @berif Overloaded method of step_simulation
             *
             * @details TODO
             *
             * @param deltaT1 : TODO
             * @param deltaT2 : TODO
             * @param deltaT2 : TODO
             *
             * @warning TODO
             */
        public:
            /*! @brief Destructor
             *
             * @details Destructor to cleanup resources. Within the 
             * body of the destructor the memory is released and 
             * pointers are assigned to nullptr.
             *
             * @warning At the moment it is safe not to call the 
             * destructor manually since there has been no testing 
             * on this objet (using unit testing etc. )and hence the
             * corner cases for call to disctructor has not been 
             * ascertained
             */
            ~World();
            
            /*! @brief Default constructor
             *
             * @details The default constructor creates a VBF::World
             * object with all the underlying member pointers are 
             * currently assigned nullptr and the boolean member 
             * 'is_initialized' is set to false. 
             * 
             * It might be prudent to initialize some member variables
             * to correct pointers but this has to be properly tested.
             * For the purpose of VBF Simulations, it is recommended
             * to use this Constructor and call the member function
             * VBF::World::initialize_new_World() to initialize the 
             * member variables correctly. 
             */
            World();
    
            /*! @brief User defined constructor
             *
             * @details This constructor creates and initializes a new
             * VBF::World objet by approperiate pointers that have 
             * been passed to it. Within the constructor body, the 
             * variable is_initialzed to true. The gravity in the 
             * VBF::World is not set by a call to the constructor
             *
             * @param world : Pointer to btWorld.
             * @param collConfig : Pointer to btCollConfig.
             * @param dispatcher : Pointer to btDispatcher_iwb.
             * @param interface : Pointer to btInterface.
             * @param solver : Pointer to btSolver.
             *
             * @warning Currently this constructor doesn't check if
             * all the pointers passed are valid or not. Correct 
             * behavior should be to throw a bad pointer warning in
             * the case invalid pointers are passed.
             *
             * The user is advised to set the gravity (if needed)
             * in the VBF::World obeject created using this 
             * constructor by a call to the public method 
             * VBF::World::set_gravity()
             */
            explicit World(btWorld* world, 
                  btCollConfig* collConfig,
                  btDispatcher_iwb* dispatcher,
                  btInterface* interface,
                  btSolver* solver);
    
            /*! @brief Preventing copy semantics by deleting
             * copy constructor
             */
            World(const World& world) = delete;
    
            void intialize_new_world();

            /*! @brief Initializes a VBF::World object suitable for
             * VBF::Simulation
             *
             * @details Public member function useful for initializing
             * a VBF::World object created using the default 
             * constructor. This method is a safe and recommended way
             * to initialize a VBF::World to be used in VBF simulation
             * . 
             * @param None
             * @returns void
             */
            bool is_initialized() const;
            
            /*! @brief Public method to set member variable m_world.
             *
             *  @param world : pointer to btWorld object.
             * @warning The method doesn't check for the validiy
             * of input parameter.
             */
            void set_world(btWorld *world);

            /*! @brief Public method to initialize gravity in 
             * VBF::World object.
             *
             * @param : gravity : btVector3 with gravity vector. 
             * Default value of the vector is such that the gravity
             * is initialized to 9.80 along -ve y-axis. 
             * @warning The method doesn't check for the validiy
             * of input parameter.
             */
            void set_gravity(btVector3 gravity=btVector3(0.0, -9.80, 0.0));
            /*! @brief Public method to set the collision
             * configuration.
             *
             * @param collConfig : pointer to btCollConfig object.
             * @warning The method doesn't check for the validiy
             * of input parameter.
             */
            void set_collisionConfig(btCollConfig *collConfig);

            /*! @brief Public method to set collision dispatcher.
             * @warning The method doesn't check for the validiy
             * of input parameter.
             */
            void set_dispatcher(btDispatcher_iwb *dispatcher);

            /*! @brief Public method to set interface
             * @warning The method doesn't check for the validiy
             * of input parameter.
             */
            void set_interface(btInterface *interface);
            /*! @brief Public method to set the bullet physics solver.
             * @warning The method doesn't check for the validiy
             * of input parameter.
             */
            void set_solver(btSolver *solver);

            /*! @brief Public method to set the debug drawer.
             *
             * @details This method is useful for getting the 
             * visualization framework which can be quite useful
             * to see if the simulation is proceeding as expected,
             * and of course to make the simulation look not boring.
             *
             * @param Pointer to GLDebugDrawer object. 
             *
             * @warning The method doesn't check for the validiy
             * of input parameter.
             */
            void set_debug_drawer(GLDebugDrawer* debugDraw);

            /*! @brief Same as the public member set_debug_drawer
             *
             * @details This is an overload of the public method 
             * described previously but taaking a reference instead 
             * of pointer to GLDebigDrawer object.
             *
             * @param Reference to GLDebugDrawer object.
             */
            void set_debug_drawer(GLDebugDrawer& debugDraw); //overloaded function
            /*!@brief adds btRigidBody to VBF::World.
             *
             * @details After creating the world and rigid bodies 
             * separately, it makes sense that the rigid bodies are
             * introduced to the world which defines the environment 
             * for their interactions (gravity, friction, reference
             * ground etc.), and this is excatly the objective of this
             * method. 
             *
             * @param Pointer to btRididBody.
             *
             * @warning The method doesn't check for the validiy
             * of input parameter.
             */
            void add_rigid_bodies_to_world(btRigidBody* rbody);
    
            /*! @brief Returns access to member m_world
             *
             * @details Non-static public member method returning the 
             * pointer to the btWorld (bullet object) encapsulated in
             * VBF::World.
             *
             * @warning The method currently doesn't check the 
             * validity of pointer that it tries to return.
             */
            btWorld*          get_world() const;

            /*! @brief Returns access to member m_collConfig.
             *
             * @details Non-static public member method returning read
             * only access to btCollConfig (bullet object) 
             * encapsulated in VBF::World. 
             *
             * @warning The method currently doesn't check the 
             * validity of pointer that it tries to return.
             */
            btCollConfig*     get_collisionConfig() const;

            /*! @brief Returns access to member m_dispatcher.
             *
             * @details Non-static public member method that returns
             * read-only access pointer to btCollisionDispatcher 
             * (bullet object).
             *
             * @warning The method currently doesn't check the 
             * validity of pointer that it tries to return.
             */
            btDispatcher_iwb* get_dispatcher() const;

            /*! @brief  Returns access to member m_interface.
             *
             * @details Non-static public member function that returns
             * read only access to poitner btInterface (bullet object)
             * encapsulated within VBF::World.
             *
             * @warning The method currently doesn't check the 
             * validity of pointer that it tries to return.
             */
            btInterface*      get_broadphaseInterface() const;

            /*! @brief Returns read only access to pointer m_solver.
             *
             * @details Returns access to member m_solver
             *
             * @warning The method currently doesn't check the 
             * validity of pointer that it tries to return.
             */
            btSolver*         get_solver() const;

            /*! 
             *
             * @warning The method currently doesn't check the 
             * validity of pointer that it tries to return.
             */
            btIDebugDraw*     get_debug_drawer() const;

            long double get_curr_time() noexcept;
    

            void step_simulation(double deltaT1) noexcept;

            /*! @berif Overloaded method of step_simulation
             *
             * @details TODO
             *
             * @param deltaT1 : TODO
             *
             * @warning TODO
             */
            
            void step_simulation(double deltaT1, double deltaT2);
            void print_updated_positions() const;
    };

}

#endif //VBF_WORLD_H
