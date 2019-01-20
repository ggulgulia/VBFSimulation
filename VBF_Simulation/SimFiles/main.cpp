//#include "helper.hpp"
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

VBF::Cube* get_ground(){

    //create a ground
    double grLength = 50;
    btVector3 grOrigin = btVector3(0.0, -50.0, 0.0);
    btVector3 grInertia = btVector3(0.0, 0.0, 0.0);
    double grMass = 0.0; //ground is static object, doesn't interact
    size_t grIndex = 23;
    
    return new VBF::Cube(grLength, grOrigin, grInertia, grMass, grIndex);
 
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

void get_spheres(std::vector<VBF::RigidBody*>& sphere_vector){
    
    double sphereRad = 1.0;
    double sphereMass = 1.0;
    size_t sphereIndex = 44;
    btVector3 sphereInertia = btVector3(0.0, 0.0, 0.0);
    size_t array_size = 5;
       for(size_t k=0; k<array_size; ++k){ 
           for (size_t i = 0; i < array_size; ++i) {
               for (size_t j = 0; j < array_size; ++j) {
                   
                   btVector3 sphereOrigin = btVector3(2.0*i, 20+2.0*k, 2.0*j);
                   sphereIndex += j + array_size*i + array_size*k;
                   VBF::Sphere *sph = new VBF::Sphere(sphereRad, sphereOrigin, sphereInertia, sphereMass, sphereIndex);
                   sphere_vector.push_back(sph);
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

    //create a placeholder for rigid boides
    std::vector<VBF::RigidBody*> rigid_bodies;
    VBF::RigidBody *ground = get_ground();

    //get_cubes(rigid_bodies);
    get_spheres(rigid_bodies);

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
    //delete window;
   
return 0;
}
