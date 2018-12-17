#include "helper.hpp"
#include "VBF_World.hpp"
#include "VBF_RigidBodies.hpp"
#include "VBF_CommonPhysics.hpp"
#include "VBF_GraphicsBridge.hpp"
#include "VBF_Cube.hpp"
#include "VBF_Sphere.hpp"

void releaseResources(std::vector<btCollisionShape*> &collShape, std::vector<btRigidBody*> &rbody,
                      std::vector<btDefaultMotionState*> &motionState){
    for(size_t i=0; i<collShape.size(); ++i){
        delete collShape[i];
        collShape[i] = nullptr;
    }
    for(size_t i=0; i<rbody.size(); ++i){
        delete rbody[i];
        rbody[i] = nullptr;
    }
    for(size_t i=0; i<motionState.size(); ++i){
        delete motionState[i];
        motionState[i] = nullptr;
    }

    std::cout << "Successfully freed the memory\n";
}

void get_ground(VBF::RigidBody*& ground){

    //create a ground
    double grLength = 50;
    btVector3 grOrigin = btVector3(0.0, -50.0, 0.0);
    btVector3 grInertia = btVector3(0.0, 0.0, 0.0);
    double grMass = 0.0; //ground is static object, doesn't interact
    size_t grIndex = 23;
    ground = new VBF::Cube(grLength, grOrigin, grInertia, grMass, grIndex);
 
}

void get_cubes(std::vector<VBF::RigidBody*>& rigid_bodies_vector){

    //create more objects cube objects
    std::vector<VBF::RigidBody*> rigid_bodies;
    double cubeLen = 1.0;
    double cubeMass = 1.0; //  these are dynamic objects
    size_t cubeIndex = 12;
    btVector3 cubeInertia= btVector3(0.0, 0.0, 0.0);
    size_t array_size = 5;

    for(size_t k=0; k<array_size; ++k){
        for (size_t i = 0; i < array_size; ++i) {
           for (size_t j = 0; j < array_size; ++j) {
               
               btVector3 cubeOrigin = btVector3(2.0*i, 20+2.0*k, 2.0*j);
               cubeIndex += j + array_size*i + array_size*k;
               VBF::Cube *cube = new VBF::Cube(cubeLen, cubeOrigin, cubeInertia, cubeMass, cubeIndex);
               rigid_bodies_vector.push_back(cube);
           } 
        }
    }
}


int main(int argc, char *argv[])
{

    std::cout << "attempt to run hello world like program using modern c++ and with GUI debugDraw\n";
    

    //create world for vbf simulation
    VBF::World* vbf_world = new VBF::World();
    vbf_world->intialize_new_world();

    //create OpenGL Window
    b3gDefaultOpenGLWindow* window = new b3gDefaultOpenGLWindow();
    b3gWindowConstructionInfo wci;
    wci.m_openglVersion = 2;
    wci.m_width = sWidth;
    wci.m_height = sHeight;
    window->createWindow(wci);
    window->setResizeCallback(MyResizeCallback);
    window->setMouseButtonCallback(MyMouseButtonCallback);
    window->setMouseMoveCallback(MyMouseMoveCallback);
    window->setKeyboardCallback(MyKeyboardCallback);
    window->setWindowTitle("iwb TUM");

    //create a placeholder for rigid boides
    std::vector<VBF::RigidBody*> rigid_bodies;
    VBF::RigidBody *ground;
    get_ground(ground);
    ground->get_shape();
    get_cubes(rigid_bodies);

    //CommonPhysics phy(vbf_world);
    VBF::CommonPhysics phy(vbf_world, ground, rigid_bodies);
    phy.initPhysics();
    
    //visualization bridge
    VBF_Vis vis_bridge;
    vis_bridge.setDynamicsWorld(phy.get_world());
    vis_bridge.reshape(sWidth, sHeight);
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
         window->startRendering();
         vis_bridge.renderme();
         phy.debugDraw(2);
         window->endRendering();
        }while(!window->requestedExit());
        
    window->closeWindow();
    delete window;
   
    return 0;
}
