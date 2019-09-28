#ifndef VBF_WORLD_H
#define VBF_WORLD_H 

#include <bullet/LinearMath/btVector3.h>
#include <bullet/btBulletDynamicsCommon.h>
#include <bullet/LinearMath/btIDebugDraw.h>
#include <OpenGL/GLDebugDrawer.h>
#include <iostream>
#include <vector>
#include <memory>

typedef btDiscreteDynamicsWorld btWorld;
typedef btDefaultCollisionConfiguration btCollConfig;
typedef btCollisionDispatcher btDispatcher_iwb;
typedef btBroadphaseInterface btInterface;
typedef btSequentialImpulseConstraintSolver btSolver;
typedef btRigidBody::btRigidBodyConstructionInfo btRbConstrInfo;

namespace VBF{

    class World {
        
        private:
            btWorld*         m_world;
            btCollConfig*    m_collisionConfig;
            btDispatcher_iwb*    m_dispatcher;
            btInterface*     m_interface;
            btSolver*        m_solver;
            bool m_is_initialized;
    
        public:
            virtual ~World();
            
            //default constructor
            World();
    
            //user defined constructor
            explicit World(btWorld* world, 
                  btCollConfig* collConfig,
                  btDispatcher_iwb* dispatcher,
                  btInterface* interface,
                  btSolver* solver);
    
            //remove copy constructor
            World(const World& world) = delete;
    
            //a new world is shaped on the implicit *this object
            //assumption that the world is empty
            //if not all its existing properties will be lost
            void intialize_new_world();
        
            bool is_initialized() const;
            
            //setters
            void set_world(btWorld *world);
            void set_collisionConfig(btCollConfig *collConfig);
            void set_dispatcher(btDispatcher_iwb *dispatcher);
            void set_interface(btInterface *interface);
            void set_solver(btSolver *solver);
            void set_debug_drawer(GLDebugDrawer* debugDraw);
            void set_debug_drawer(GLDebugDrawer& debugDraw); //overloaded function
            void add_rigid_bodies_to_world(btRigidBody* rbody);
    
            //getters
            btWorld*          get_world() const;
            btCollConfig*     get_collisionConfig() const;
            btDispatcher_iwb* get_dispatcher() const;
            btInterface*      get_broadphaseInterface() const;
            btSolver*         get_solver() const;
            btIDebugDraw*     get_debug_drawer() const;
    
            void step_simulation(double deltaT1, double deltaT2) const;
            void step_simulation(double deltaT1) const;
            void print_updated_positions() const;
    };

}
//getting rid of ugly type names

#endif //VBF_WORLD_H
