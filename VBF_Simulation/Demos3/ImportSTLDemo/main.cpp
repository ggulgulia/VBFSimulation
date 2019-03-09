#include "ImportSTLSetup.hpp"
#include "VBF_World.hpp"
#include "VBF_GraphicsBridge.hpp"
#include "VBF_Cube.hpp"
#include "VBF_CommonPhysics.hpp"

VBF::Cube* get_ground(){

        //create a ground
        double grLength = 400; 
        btVector3 grOrigin = btVector3(0.0, -400.0, 0.0);
        btVector3 grInertia = btVector3(0.0, 0.0, 0.0);
        btTransform shapeTrans;
        shapeTrans.setIdentity();
        double grMass = 0.0; //ground is static object, doesn't interact
        size_t grIndex = 23; 
        return new VBF::Cube(grLength, grOrigin, shapeTrans, grInertia, grMass, grIndex);
}


int main(int argc, char *argv[]){
    
    //create a world for vbf simulation
    VBF::World* vbf_world = new VBF::World();
    vbf_world->initialize_new_world();
    
    //create a ground reference
    VBF::RigidBody *ground = get_ground(); 

     //import the stl file    
    //std::string fileName("l_finger_tip.stl");
    std::string fileName("StufeFein150x30x100.stl");
    VBF::ImportSTLSetup* stl_body = new VBF::ImportSTLSetup(fileName); 
    
     //create physics
    VBF::CommonPhysics phy(vbf_world, ground, stl_body->get_vbf_rbody());
    phy.initPhysics();
    
    //vis bridge
    VBF::Window* vbf_window = new VBF::Window(vbf_world, 800, 600, "Hello VBF World");
    vbf_window->create_window();VBF_Vis vis_bridge;
    vis_bridge.setDynamicsWorld(vbf_world->get_world());
    vis_bridge.reshape(800, 600);
    vis_bridge.setShadows(true);
    gApp = &vis_bridge;

    //run simulations
    btClock timer;
    size_t prevTime = timer.getTimeMicroseconds();

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
    phy.~CommonPhysics();
    stl_body->~ImportSTLSetup();
    ground->~RigidBody();


    return 0;
}

