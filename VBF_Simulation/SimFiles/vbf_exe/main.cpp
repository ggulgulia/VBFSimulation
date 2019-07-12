
/*! \author Msc. Cosima Stocker, Msc. Gajendra Gulgulia
 * 
 * \date 01/07/2019
 * 
 * \bug The code has not been developed using Test Driven approach, hence the corner cases haven not yet been tested
 * as such there might be bugs that need to be identified, tested. The veracity of the bullet physics engine itself 
 * is not trustworthy because of missing documentation and release information on their website
 *
 * \copyright The work is a part of PhD thesis of Msc. Cosima Stocker and hence the code cannot be made public without
 * her permission.
 *
 * \mainpage Project Description
 *
 * \section intro_sec Introduction
 * 
 *  Purpose of this documentation is to clarify the usage of the code that has been developed for Vibratroy Bowl Feeder (VBF) Simulation
 *  which is a part of the PhD thesis of Msc. Cosima Stocker at the chair of IWB, Department of Mechanical Engineering, 
 *  Technical University of Munich
 * 
 * \section install_sec Background
 * Orienting devices for vibratory bowl feeders are still the most widely used system for the
 * automated sorting and feeding of small parts. The design process of these orienting devices has recently been 
 * supported by simulation methods. However, this merely shifts the well-known trial-and-error-based adaption of 
 * the orienting device’s geometry into virtualworld. Yet, this does not provide optimal design and, furthermore, 
 * requires strong involvement of the developer due to manual shape variation. This paper proposes an optimization 
 * algorithm for the automated simulation-based shape optimization of orienting devices for vibratory bowl feeders. 
 * First, general formalisms to state the multiobjective optimization problem for arbitrary types of orienting 
 * devices and feeding parts are provided. Then, the implementation of the algorithm is described based on 
 * Bullet Physics Engine and random search optimization technique. Finally, comparison of simulation results with 
 * experimental data point out good accuracy and, thus, great potential of the developed shape optimization 
 * software[Source: Automated Shape Optimization of Orienting Devices for Vibratory Bowl Feeders, hofman et.al.]
 * 
 * \subsection step1 Step 1: Opening the box
 *
 * etc...
 *
 */

//! relevant imports
#include <VBF_World.hpp>
#include <VBF_CommonPhysics.hpp>
#include <VBF_GraphicsBridge.hpp>
#include <test_rigidBody.hpp>


int main(int argc, char **argv){

    std::cout << "attempt to run hello world like program using modern c++ and with GUI debugDraw\n";

    if(argc !=2){
        std::cout << "Incorrect input arguments while running executable\n";
        std::cout << "Correct format to run the simulation:\n";
        std::cout << "<PATH TO EXECUTABLE> <PATH TO MESH FILES DIR>\n";
        std::cout  << "Aborting the program. Please run the simulation with correct format\n";
        return 0;
    }
    //! create a placeholder for rigid boides
    std::vector<VBF::RigidBody*> rigid_bodies;

    //! create a reference ground
    VBF::StaticBody *ground = get_ground();
    btVector3 groundOrigin = get_rigid_body_position(ground);
    std::cout << groundOrigin[0] << " " << groundOrigin[1] << " " << groundOrigin[2] << "\n";
    
    //! test different types (static, kinematic or dynamic speheres or cubes)
    
    //! test static sphere
    //get_cubes<VBF::Static_Sphere>(rigid_bodies);
    
    //! test import stl files of kinematic and dynamic types
    
    //! declare file names 
    
    //! fileName for kinematic rigid body
    //
    std::string meshPath{argv[1]};
    std::string file1Name{"StufeFein150x30x200.stl"};
    std::string file2Name{"Zylinder1_7x1_0.stl"};

    std::string file1Path(meshPath + file1Name);
    std::cout << file1Path << "\n";
    std::string file2Path(meshPath + file2Name);

    //! set scaling factor
    static const double scale{0.1};

    //! set origin for the imported part
    btVector3 meshOrigin{btVector3(0.0, 0.0, 00.0)} ;
    btVector3 partOrigin{btVector3(-2.0, 5.0, 0.0)};
    //! import kinematic part
    VBF::KinematicMeshBody* stl_body = new VBF::KinematicMeshBody(file1Path, scale, meshOrigin);

    //! initialize mass for dynamic body
    double mass2{0.20};
    //! import dynamic stl part
    VBF::DynamicMeshBody* stl_body2 = new VBF::DynamicMeshBody(file2Path, 10*scale, mass2, partOrigin);

    //! store the imported bodies in the rigid_bodies container
    rigid_bodies.push_back(stl_body->get_vbf_rbody());
    rigid_bodies.push_back(stl_body2->get_vbf_rbody());
    

    //add a cylinder like part to the simulation 
    static const double cylHeight{2.0}, cylRad{0.5};
    VBF::Dynamic_Cylinder* stl_body3 = new VBF::Dynamic_Cylinder(cylRad, cylHeight, partOrigin, mass2);
    rigid_bodies.push_back(stl_body3);

    ////test import static mesh
    //VBF::DynamicMeshBody* stl_body33 = new VBF::DynamicMeshBody(fileName, 0.5*scale, 1.00, btVector3(10.0, 0.0, 100.0));
    //rigid_bodies.push_back(stl_body33->get_vbf_rbody());

    ////test import kinematic cubes
    //VBF::Kinematic_Cube* kinCube = new VBF::Kinematic_Cube(1.0, btVector3(0.0, 6.0, 0.0), 10);
    //rigid_bodies.push_back(kinCube);

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
    
    static int numSteps{};
    do{
         unsigned long currTime = timer.getTimeMicroseconds();
         if(!vis_bridge.isIdle()){
             phy.step_simulation((currTime-prevTime)*0.001);
         }
         Vy = velFun(currTime*10, 1.0);
         btVector3 linVel{btVector3(0.0, Vy, 0.0)};
         stl_vbf_rbody->set_linear_vel(axis, linVel);

         prevTime = currTime;
         vbf_window->start_rendering();
         vis_bridge.renderme();
         phy.debugDraw(2);
         vbf_window->end_rendering();
         btVector3 position1 = get_rigid_body_position(stl_vbf_rbody);
        std::cout << "Time:" <<currTime <<" s, Vy:" <<  Vy <<  " x:" << position1[0] << " y:" << position1[1] << " z:" << position1[2] << "\n";
        
        ++numSteps;
        
        if(numSteps%100==0){
            std::cout << "******************************************************\n";
            std::cout << "number of parts in rigid body container " << rigid_bodies.size() << "\n";
            std::cout << "******************************************************\n";
            VBF::Dynamic_Cylinder* part = new VBF::Dynamic_Cylinder(cylRad, cylHeight, partOrigin, mass2);
            rigid_bodies.push_back(part);
            vbf_world->add_rigid_bodies_to_world(part->get_rbody());
            }
        }while(!vbf_window->requested_exit());
        
    vbf_window->close_window();
    //stl_body->~ImportSTLSetup();
    //delete window;
   
return 0;
}
