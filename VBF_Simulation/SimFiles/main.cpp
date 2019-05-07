#include "ImportSTLSetup.hpp"
#include "VBF_World.hpp"
#include "VBF_CommonPhysics.hpp"
#include "VBF_GraphicsBridge.hpp"
#include "VBF_Cube.hpp"
#include "VBF_Sphere.hpp"
#include "VBF_InitializeSim.hpp"

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

VBF::Cube* get_ground(){

    //create a ground
    double grLength = 45;
    btVector3 grOrigin = btVector3(0.0, -10.05-grLength*0.5, 0.0);
    btTransform shapeTrans;
    shapeTrans.setIdentity();
    btVector3 grInertia = btVector3(0.0, 0.0, 0.0);
    double grMass = 0.0; //ground is static object, doesn't interact
    size_t grIndex = 23;
    
    return new VBF::Cube(grLength, grOrigin, shapeTrans, grInertia, grMass, grIndex);
 
}

void get_cubes(std::vector<VBF::RigidBody*>& rigid_bodies_vector){

    //create more objects cube objects
    std::vector<VBF::RigidBody*> rigid_bodies;
    double cubeLen = 1.0;
    double cubeMass = 1.0; //  these are dynamic objects
    size_t cubeIndex = 12;
    btVector3 cubeInertia= btVector3(0.0, 0.0, 0.0);
    size_t array_size = 5;
    btTransform shapeTrans;
    shapeTrans.setIdentity();

    for(size_t k=0; k<array_size; ++k){
        for (size_t i = 0; i < array_size; ++i) {
           for (size_t j = 0; j < array_size; ++j) {
               
               btVector3 cubeOrigin = btVector3(2.0*i, 20+2.0*k, 2.0*j);
               cubeIndex += j + array_size*i + array_size*k;
               VBF::Cube *cube = new VBF::Cube(cubeLen, cubeOrigin, shapeTrans, cubeInertia, cubeMass, cubeIndex);
               rigid_bodies_vector.push_back(cube);
           } 
        }
    }
}

void get_spheres(std::vector<VBF::RigidBody*>& sphere_vector){
    
    double sphereRad = 1.0;
    double sphereMass = 1.0;
    size_t sphereIndex = 44;
    btVector3 sphereInertia = btVector3(0.0, 0.0, 0.0);
    btTransform shapeTrans;
    shapeTrans.setIdentity();
    size_t array_size = 5;
       for(size_t k=0; k<array_size; ++k){ 
           for (size_t i = 0; i < array_size; ++i) {
               for (size_t j = 0; j < array_size; ++j) {
                   
                   btVector3 sphereOrigin = btVector3(2.0*i, 20+2.0*k, 2.0*j);
                   sphereIndex += j + array_size*i + array_size*k;
                   VBF::Sphere *sph = new VBF::Sphere(sphereRad, sphereOrigin, shapeTrans, sphereInertia, sphereMass, sphereIndex);
                   sphere_vector.push_back(sph);
               } 
            }
        }

}

void get_sphere(std::vector<VBF::RigidBody*>& sphere_vector){
    
    double sphereRad = 1.0;
    size_t sphereIndex = 44;
    double scale{0.1};
    btVector3 meshAxis = btVector3(0.1*scale, -0.2*scale, 10.0*scale);
    btVector3 sphereInertia = btVector3(0.0, 0.0, 0.0);
    btTransform shapeTrans;
    btQuaternion qt;
    double pi{3.14159265358};
    qt.setEulerZYX(0,0,-0.5*pi);
    shapeTrans.setRotation(qt);

    VBF::Sphere *sph = new VBF::Sphere(sphereRad, meshAxis, shapeTrans, sphereInertia, 0.010, sphereIndex);
    sphere_vector.push_back(sph);

}

int main(int argc, char *argv[]){

    std::cout << "attempt to run hello world like program using modern c++ and with GUI debugDraw\n";

    //read input data from the input file
    std::string inputFileName("input.txt");    
    VBF::InitializeSim init(inputFileName);

    //create a placeholder for rigid boides
    std::vector<VBF::RigidBody*> rigid_bodies;

    //import the stl file
    double scale{0.1}, mass{0.00};
    std::string fileName("MeshFiles/StufeFein150x30x200.stl");
    std::string file2{"Zylinder1_7x1_0.stl"};
    btVector3 meshOrigin = btVector3(-77.9, 125.0, 10.0);
    VBF::ImportSTLSetup* stl_body = new VBF::ImportSTLSetup(fileName, scale, mass, meshOrigin);

    rigid_bodies.push_back(stl_body->get_vbf_rbody());
    //VBF::ImportSTLSetup* stl_body2 = new VBF::ImportSTLSetup(file2, 10*scale, 0.1);
    //rigid_bodies.push_back(stl_body2->get_vbf_rbody());

    //create world for vbf simulation
    VBF::World* vbf_world = new VBF::World();
    vbf_world->intialize_new_world();
    
    VBF::RigidBody *ground = get_ground();
    get_sphere(rigid_bodies); //this is just a reference body
    

    //CommonPhysics phy(vbf_world);
    VBF::CommonPhysics phy(vbf_world, ground, rigid_bodies);
    phy.initPhysics();
    
    //visualization bridge
    VBF::Window* vbf_window = new VBF::Window(vbf_world, 800, 600, "Hello VBF World");
    vbf_window->create_window();
    VBF_Vis vis_bridge;
    vis_bridge.setDynamicsWorld(vbf_world->get_world());
    vis_bridge.reshape(800, 600);
    vis_bridge.setShadows(true);
    gApp = &vis_bridge;

    btClock timer;
    unsigned long prevTime = timer.getTimeMicroseconds();
    btVector3 position;

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

         btVector3 position1 = get_rigid_body_position(stl_body->get_vbf_rbody());
         std::cout << position1[0] << " " << position1[1] << " " << position1[2] << "\n";

        }while(!vbf_window->requested_exit());
        
    vbf_window->close_window();
    //stl_body->~ImportSTLSetup();
    ground->~RigidBody();
    init.~InitializeSim();
    //delete window;
   
return 0;
}
