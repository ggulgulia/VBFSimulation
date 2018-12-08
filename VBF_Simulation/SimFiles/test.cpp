#include "helper.hpp"
#include "vbf_world.hpp"

//overloading the priting operator
std::ostream operator<<(std::ostream &out, const btTransform &trans){
    std::cout << "\nX: " << trans.getOrigin().getX() << "\nY: " << trans.getOrigin().getY() <<"\nZ: " << trans.getOrigin().getZ() <<"\n";
}

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

   
    //create placeholder for shapes, some kind of array
    std::vector<btCollisionShape*> collisionShapes;
    
    //CREATE RIGID BODIES
    //1. create box
    btCollisionShape *box = new btBoxShape(btVector3(1.0, 1.0, 1.0));
    
    //2. create a sphere
    btCollisionShape *sphere = new btSphereShape(1.0); //sphere with radius 1.0
    
    //push the above bodies in the place holder array
    collisionShapes.push_back(box);     
    collisionShapes.push_back(sphere);

    
    std::vector<double> mass{0.0, 1.0};
    std::vector<btVector3> inertia;
    std::vector<btDefaultMotionState*> myMotionstate;
    std::vector<btTransform> shapeTransform(collisionShapes.size());
    std::vector<btVector3> origin;

    typedef btRigidBody::btRigidBodyConstructionInfo btRbConstrInfo; //gitting rid of ugly name
    std::vector<btRbConstrInfo> rbInfo; //above typedef used here
    
    std::vector<btRigidBody*> rbody; //'r' refers to rigid here

    //manually define the origins of the shapes
    origin.push_back(btVector3(0.0, -56.0, 0.0)); //for box
    origin.push_back(btVector3(2.0, 10.0, 0.0));  //for sphere

    for(size_t i=0; i<collisionShapes.size(); ++i){
        
        inertia.push_back(btVector3(0.0, 0.0, 0.0));
        if(mass[i] != 0.0)
            collisionShapes[i]->calculateLocalInertia(mass[i], inertia[i]);

        shapeTransform[i].setIdentity();
        shapeTransform[i].setOrigin(origin[i]);
        myMotionstate.push_back(new btDefaultMotionState(shapeTransform[i]));
        rbInfo.push_back(btRbConstrInfo(mass[i], myMotionstate[i], collisionShapes[i], inertia[i]));
        rbody.push_back(new btRigidBody(rbInfo[i]));

    }

    vbf_world->add_rigid_bodies_to_world(rbody);

    ////do some simulation
    for (size_t i = 0; i < 100000; ++i) {
        vbf_world->step_simulation(1.0/60.0, 10.0);
        vbf_world->print_updated_positions();
    }

    //releaseResources(collisionShapes, rbody, myMotionstate);

    return 0;
}
