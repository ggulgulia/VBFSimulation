#include "VBF_World.hpp"
#include "VBF_CommonPhysics.hpp"
#include "VBF_GraphicsBridge.hpp"
#include <VBF_Static_Cube.hpp>
#include <VBF_Kinematic_Cube.hpp>

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

VBF::Static_Cube* get_ground(){

    //create a ground
    double grLength = 50;
    btVector3 grOrigin = btVector3(0.0, -4-grLength, 0.0);
    size_t grIndex = 23;
    
    return new VBF::Static_Cube(grLength, grOrigin, grIndex);
 
}

//void get_cubes(std::vector<VBF::RigidBody*>& rigid_bodies_vector){
//
//    //create more objects cube objects
//    std::vector<VBF::RigidBody*> rigid_bodies;
//    double cubeLen = 1.0;
//    double cubeMass = 1.0; //  these are dynamic objects
//    size_t cubeIndex = 12;
//    btVector3 cubeInertia= btVector3(0.0, 0.0, 0.0);
//    size_t array_size = 5;
//    btTransform shapeTrans;
//    shapeTrans.setIdentity();
//
//    for(size_t k=0; k<array_size; ++k){
//        for (size_t i = 0; i < array_size; ++i) {
//           for (size_t j = 0; j < array_size; ++j) {
//               
//               btVector3 cubeOrigin = btVector3(2.0*i, 20+2.0*k, 2.0*j);
//               cubeIndex += j + array_size*i + array_size*k;
//               VBF::Kinematic_Cube *cube = new VBF::Kinematic_Cube(cubeLen, cubeOrigin,  cubeIndex);
//               rigid_bodies_vector.push_back(cube);
//           } 
//        }
//    }
//}
//
//void get_spheres(std::vector<VBF::RigidBody*>& sphere_vector){
//    
//    double sphereRad = 1.0;
//    double sphereMass = 1.0;
//    size_t sphereIndex = 44;
//    btVector3 sphereInertia = btVector3(0.0, 0.0, 0.0);
//    btTransform shapeTrans;
//    shapeTrans.setIdentity();
//    size_t array_size = 5;
//       for(size_t k=0; k<array_size; ++k){ 
//           for (size_t i = 0; i < array_size; ++i) {
//               for (size_t j = 0; j < array_size; ++j) {
//                   
//                   btVector3 sphereOrigin = btVector3(2.0*i, 20+2.0*k, 2.0*j);
//                   sphereIndex += j + array_size*i + array_size*k;
//                   VBF::Sphere *sph = new VBF::Sphere(sphereRad, sphereOrigin, shapeTrans, sphereInertia, sphereMass, sphereIndex);
//                   sphere_vector.push_back(sph);
//               } 
//            }
//        }
//
//}
//
//
////this method adds a reference sphere at the axis of  the vbf component for visual check and 
////debuggging 
//void get_sphere(std::vector<VBF::RigidBody*>& sphere_vector, btVector3 &meshAxis, const double scale){
//    
//    double sphereRad = 1.0;
//    size_t sphereIndex = 44;
//    meshAxis[0] *= scale; meshAxis[1] *= scale; meshAxis[2] *= scale;
//    btVector3 sphereInertia = btVector3(0.0, 0.0, 0.0);
//    btTransform shapeTrans;
//    shapeTrans.setIdentity();
//    VBF::Sphere *sph = new VBF::Sphere(sphereRad, meshAxis, shapeTrans, sphereInertia, 0.0, sphereIndex);
//    sphere_vector.push_back(sph);
//
//}

int main(int argc, char *argv[]){

    std::cout << "attempt to run hello world like program using modern c++ and with GUI debugDraw\n";

    //create a placeholder for rigid boides
    std::vector<VBF::RigidBody*> rigid_bodies;

    VBF::StaticBody *ground = get_ground();
    btVector3 groundOrigin = get_rigid_body_position(ground);
    std::cout << groundOrigin[0] << " " << groundOrigin[1] << " " << groundOrigin[2] << "\n";
    //import the stl file
    VBF::Kinematic_Cube* kinCube = new VBF::Kinematic_Cube(4.0, btVector3(0.0, 10.0, 0.0), 10);
    //create world for vbf simulation
    VBF::World* vbf_world = new VBF::World();
    vbf_world->intialize_new_world();
    
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

    double Vy{};
    auto velFun = [] (double time, double amplitude)->double{double pi{3.14159};
                                                            return amplitude*sin(4*pi*time);};
    btVector3 axis{btVector3(7.397719, 0.25, 13.203666)};



    btClock timer;
    unsigned long prevTime = timer.getTimeMicroseconds();


    do{
         unsigned long currTime = timer.getTimeMicroseconds();
         if(!vis_bridge.isIdle()){
             phy.stepSimulation((currTime - prevTime)/1000.);
         }
         Vy = velFun(currTime, 2);
         btVector3 linVel{btVector3(0.0, Vy, 0.0)};
         kinCube->set_linear_vel(axis, linVel);

         prevTime = currTime;
         vbf_window->start_rendering();
         vis_bridge.renderme();
         phy.debugDraw(2);
         vbf_window->end_rendering();
         btVector3 position1 = get_rigid_body_position(kinCube);
        std::cout << "Time:" <<currTime <<" s, Vy:" <<  Vy <<  " x:" << position1[0] << " y:" << position1[1] << " z:" << position1[2] << "\n";


        }while(!vbf_window->requested_exit());
        
    vbf_window->close_window();
    //stl_body->~ImportSTLSetup();
    //delete window;
   
return 0;
}
