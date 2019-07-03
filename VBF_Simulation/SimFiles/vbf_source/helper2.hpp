
#include <ImportSTLSetup.hpp>
#include <VBF_World.hpp>
#include <VBF_CommonPhysics.hpp>
#include <VBF_GraphicsBridge.hpp> 
#include <VBF_Cube.hpp>
#include <VBF_Sphere.hpp> 
#include <VBF_InitializeSim.hpp>

//returns the rigid body position based on motion state
void get_rigid_body_position(const VBF::RigidBody *const vbf_rigid_body, btVector3& position){
    btTransform trans;
    vbf_rigid_body->get_rbody()->getMotionState()->getWorldTransform(trans);
    position[0] = trans.getOrigin().getX();
    position[1] = trans.getOrigin().getY();
    position[2] = trans.getOrigin().getZ();
}


//returns the rigid body position based not on motion state

const btVector3 get_rigid_body_position(const VBF::RigidBody *const vbf_rigid_body) noexcept{

    btVector3 pos = vbf_rigid_body->get_rbody()->getWorldTransform().getOrigin();
    return pos;
}

void run_simulation_loop(VBF::World *const vbf_world, VBF::CommonPhysics& phy, DemoApplication* gApp){

    VBF::Window* vbf_window = new VBF::Window(vbf_world, 800, 600, "Hello VBF World");
    vbf_window->create_window();
    VBF_Vis vis_bridge;
    vis_bridge.setDynamicsWorld(vbf_world->get_world());
    vis_bridge.reshape(800, 600);
    vis_bridge.setShadows(true);
    gApp = &vis_bridge;

    btClock timer;
    unsigned long prevTime = timer.getTimeMicroseconds();
    
    do{ 
        unsigned long currTime = timer.getTimeMicroseconds();
        if(!vis_bridge.isIdle()){
                         phy.stepSimulation((currTime - prevTime)/1000.);
                                  
           }   
        prevTime = currTime;
        vbf_window->start_rendering();
        vis_bridge.renderme();
        phy.debugDraw(2);
        vbf_window->end_rendering();
    
      }while(!vbf_window->requested_exit());
    vbf_window->close_window();

}
