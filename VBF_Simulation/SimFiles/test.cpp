#include <bullet/btBulletDynamicsCommon.h>
#include <iostream>
#include <vector>
#include <memory>
#include <OpenGL/GLDebugDrawer.h>


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

    //create the properties of the world
    btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
    btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);
    btBroadphaseInterface* interface = new btDbvtBroadphase();
    btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;
    
    // initialize the world with the above properties
    btDiscreteDynamicsWorld* world = new btDiscreteDynamicsWorld(dispatcher, interface, solver, collisionConfiguration);
    world->setGravity(btVector3(0.0, -9.81, 0));
    
    //initialize visualization framework
    GLDebugDrawer *debugDraw = new GLDebugDrawer;
    debugDraw->setDebugMode(1); //what does 1 mean and what are the other options?
    world->setDebugDrawer(debugDraw); 
    
   
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

        world->addRigidBody(rbody[i]);
    }

    //do some simulation
    for (size_t i = 0; i < 20; ++i) {
        world->stepSimulation(1.f/60.f, 10);

        //print positions of all objects
        for (int j = 0; j<world->getNumCollisionObjects(); ++j){

            btCollisionObject *obj = world->getCollisionObjectArray()[j];
            btRigidBody* bdy = btRigidBody::upcast(obj);
            
            if(bdy && bdy->getMotionState()){
                btTransform trans;
                bdy->getMotionState()->getWorldTransform(trans);
                std::cout << "world pos: " << trans.getOrigin().getX() <<"\nY: " << trans.getOrigin().getY() << "\nZ:" << trans.getOrigin().getZ() << "\n";
            }
        }
        
    }

    releaseResources(collisionShapes, rbody, myMotionstate);

    //releasing resources
    for (size_t i = 0; i < collisionShapes.size(); ++i) {


        
    }

    return 0;
}
