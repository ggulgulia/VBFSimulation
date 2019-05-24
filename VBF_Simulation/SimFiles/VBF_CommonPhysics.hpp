
#ifndef COMMON_PHYSICS_H
#define COMMON_PHYSICS_H
#include <bullet/LinearMath/btVector3.h>
#include <OpenGL/GLDebugDrawer.h>
//#include "CommonParameterInterface.h"
#include "VBF_World.hpp"
#include <VBF_RigidBody.hpp>


// a Physics Object should have a VBF::World and the related objects (Physical Bodies) in it
// it should have a bridge with the graphics to visualize and 
//it should be optional to speed up the calculations  when needed

//FOR VBF Simulations, we would like to have a world, a ground referece and objects in it
//ofcourse physics can be simulated without a ground but I don't think this is going to 
//make my life easier as it is, the documentations are missing 
namespace VBF{  
    
    class CommonPhysics{
        private:
               VBF::World* m_VBF_world;
               VBF::RigidBody *m_ground;
               std::vector<VBF::RigidBody*> m_VBF_rbody;
               std::vector<CollShape*> m_shape;
               //bool m_is_visualization_on;
        public:
            
            virtual ~CommonPhysics();
            CommonPhysics();
            CommonPhysics(VBF::World* vbf_world, VBF::RigidBody * ground, std::vector<VBF::RigidBody*>& vbf_rbody_vect);
            CommonPhysics(VBF::World* vbf_world);
            CommonPhysics(VBF::World* vbf_world, VBF::RigidBody* vbf_rbody);
            CommonPhysics(const CommonPhysics& comPhy)=delete;
    	    virtual void initPhysics();
    	    virtual void stepSimulation(double deltaTime);
            virtual void debugDraw(int debugDrawFlags);
    	    virtual void syncPhysicsToGraphics();
            virtual btWorld* get_world() const;
    };

}

#endif //COMMON_PHYSICS_H
