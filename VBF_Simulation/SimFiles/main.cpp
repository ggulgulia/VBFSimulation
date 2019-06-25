#include "VBF_World.hpp"
#include "VBF_CommonPhysics.hpp"
#include "VBF_GraphicsBridge.hpp"
#include "test_rigidBody.hpp"

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
    
    //test different types (static, kinematic or dynamic speheres or cubes)
    get_cubes<VBF::Static_Sphere>(rigid_bodies);
    //import the stl file
    std::string fileName("MeshFiles/StufeFein150x30x200.stl");
    std::string file2{"MeshFiles/Zylinder1_7x1_0.stl"};
    double scale{0.1};
    btVector3 meshOrigin{btVector3(0.0, 0.0, 00.0)} ;
    VBF::KinematicMeshBody* stl_body = new VBF::KinematicMeshBody(fileName, scale, meshOrigin);
    rigid_bodies.push_back(stl_body->get_vbf_rbody());
    VBF::KinematicMeshBody* stl_body2 = new VBF::KinematicMeshBody(file2, 10*scale, meshOrigin);
    rigid_bodies.push_back(stl_body2->get_vbf_rbody());

    //test import static mesh
    VBF::DynamicMeshBody* stl_body33 = new VBF::DynamicMeshBody(fileName, 0.5*scale, 1.00, btVector3(10.0, 0.0, 100.0));
    rigid_bodies.push_back(stl_body33->get_vbf_rbody());

    //test import kinematic cubes
    VBF::Kinematic_Cube* kinCube = new VBF::Kinematic_Cube(1.0, btVector3(0.0, 6.0, 0.0), 10);
    rigid_bodies.push_back(kinCube);

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
    VBF::KinematicBody* stl_vbf_rbody = stl_body->get_vbf_rbody();

    do{
         unsigned long currTime = timer.getTimeMicroseconds();
         if(!vis_bridge.isIdle()){
             phy.stepSimulation((currTime - prevTime)/1000.);
         }
         Vy = velFun(currTime, 2);
         btVector3 linVel{btVector3(0.0, Vy, 0.0)};
         stl_vbf_rbody->set_linear_vel(axis, linVel);

         prevTime = currTime;
         vbf_window->start_rendering();
         vis_bridge.renderme();
         phy.debugDraw(2);
         vbf_window->end_rendering();
         btVector3 position1 = get_rigid_body_position(stl_vbf_rbody);
        std::cout << "Time:" <<currTime <<" s, Vy:" <<  Vy <<  " x:" << position1[0] << " y:" << position1[1] << " z:" << position1[2] << "\n";


        }while(!vbf_window->requested_exit());
        
    vbf_window->close_window();
    //stl_body->~ImportSTLSetup();
    //delete window;
   
return 0;
}
