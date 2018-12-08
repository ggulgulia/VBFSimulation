#include "helper.hpp"
#include "VBF_World.hpp"
#include "VBF_RigidBodies.hpp"

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

    //initialize visualization framework
    GLDebugDrawer *debugDraw = new GLDebugDrawer;
    debugDraw->setDebugMode(1); //what does 1 mean and what are the other options?
    vbf_world->set_debug_drawer(debugDraw); 

    std::vector<VBF::RigidBody*> rigid_bodies;
   
    VBF::Cube *cube = new VBF::Cube(1.0, btVector3(0.0, -56.0, 0.0), 
               btVector3(0.0, 0.0, 0.0),
               0.221, 23);
               
    VBF::Sphere *sphere = new VBF::Sphere(0.5, btVector3(0.0, 10.0, 0.0), 
                                          btVector3(0.0, 0.0, 0.0), 1.618, 28);

    rigid_bodies.push_back(sphere);
    rigid_bodies.push_back(cube);

    for(size_t i=0; i < rigid_bodies.size(); ++i){
        vbf_world->add_rigid_bodies_to_world(rigid_bodies[i]->get_rbody());
    }

    for(size_t i=0; i<100000; ++i){
        vbf_world->step_simulation(1.0/60.0, 10.0);
        vbf_world->print_updated_positions();
    }

    return 0;
}
