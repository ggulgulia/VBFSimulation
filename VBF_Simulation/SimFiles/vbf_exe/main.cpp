
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
#include <VBF_CommonPhysics.hpp>
#include <VBF_GraphicsBridge.hpp>
#include <test_rigidBody.hpp>
#include <VBF_InitializeSim.hpp>
//#include <VBF_ReadInputData.hpp>


int main(int argc, char **argv){

    try{
    std::cout << "attempt to run hello world like program using modern c++ and with GUI debugDraw\n";

    //if(argc !=3){
    //    std::cout << "Incorrect input arguments while running executable\n";
    //    std::cout << "Correct format to run the simulation:\n";
    //    std::cout << "<PATH TO EXECUTABLE> <PATH TO VBF MESH FILE> <PATH TO INPUT FILE>\n";
    //    std::cout  << "Aborting the program. Please run the simulation with correct format\n";
    //    return 0;
    //}
    //! create a placeholder for rigid boides
    std::vector<VBF::RigidBody*> rigid_bodies;

    //! declare file names 
    
    //! fileName for kinematic rigid body
    //std::string meshPath{argv[1]};
    //std::string inputFile{argv[2]};
    //VBF::ReadInputData init(inputFile);
    //std::cout << "Printing inputs " << init;
    //std::cout << "Value of deltaT " << init["deltaT"] << "\n";


    //std::string vbf_file_path(meshPath + file1Name);
    std::string vbf_file_path{"../MeshFiles/StufeFein150x30x200.stl"};
    std::string inputFile{"../InputFile.txt"};
    std::cout << vbf_file_path << "\n";
    std::string file2Path("../MeshFiles/Zylinder1_7x1_0.stl");

    VBF::ReadInputData inputData(inputFile);
    std::cout << inputData << "\n";

    VBF::InitializeSim initSim(inputFile, vbf_file_path);
    
    
    //! import kinematic part
    VBF::KinematicMeshBody* stl_body = initSim.get_vbf_part();

    //add a cylinder like part to the simulation 
    VBF::Dynamic_Cylinder* stl_body3 = initSim.get_dyn_part(); 
    rigid_bodies.push_back(stl_body3);

    
    VBF::CommonPhysics& phy = initSim.get_VBF_physics();
    VBF::World* vbf_world = initSim.get_VBF_world(); 
    VBF::Window* vbf_window = new VBF::Window(vbf_world, 800, 600, "Hello VBF World");
    vbf_window->create_window();
    VBF_Vis vis_bridge;
    vis_bridge.setDynamicsWorld(vbf_world->get_world());
    vis_bridge.reshape(800, 600);
    vis_bridge.setShadows(true);
    gApp = &vis_bridge; 


    
    double Vy{}; //!< Variable to store instantenous vibration 

    /*! Vibration function 
     */
    auto velFun = [] (double time, double amplitude)->double{double pi{3.14159};
                                                            return amplitude*sin(4*pi*time);};
    //btVector3 axis{btVector3(7.397719, 0.25, 13.203666)};



    btClock timer;
    unsigned long prevTime = timer.getTimeMicroseconds();
    VBF::KinematicBody* stl_vbf_rbody = stl_body->get_vbf_rbody();
    
    static int numSteps{};
    size_t no_movement_steps{200}; //200 seconds without vibration

    //this loops starts the simulation but the VBF part is not
    //vibrated for some time (defined by no_movement_steps)
    for(size_t i=0; i<no_movement_steps; ++i){

         unsigned long currTime = timer.getTimeMicroseconds();
         if(!vis_bridge.isIdle()){
             phy.step_simulation((currTime-prevTime)*0.001);
         }
         prevTime = currTime;
         vbf_window->start_rendering();
         vis_bridge.renderme();
         phy.debugDraw(2);
         vbf_window->end_rendering();
         btVector3 position1 = get_rigid_body_position(stl_vbf_rbody);
        std::cout << "Time:" <<currTime <<" s, Vy:" <<  Vy <<  " x:" << position1[0] << " y:" << position1[1] << " z:" << position1[2] << "\n";
        
        ++numSteps;
    }
    
    //in this loop the vibration of the VBF part begins
    do{
         unsigned long currTime = timer.getTimeMicroseconds();
         if(!vis_bridge.isIdle()){
             phy.step_simulation(0.01, 0.02);
         }
         Vy = velFun(currTime*10, 0.20);
         btVector3 linVel{btVector3(0.0, Vy, 0.0)};
         stl_vbf_rbody->set_linear_vel(linVel);

         prevTime = currTime;
         vbf_window->start_rendering();
         vis_bridge.renderme();
         phy.debugDraw(2);
         vbf_window->end_rendering();
         btVector3 position1 = get_rigid_body_position(stl_vbf_rbody);
        std::cout << "Time:" <<currTime <<" s, Vy:" <<  Vy <<  " x:" << position1[0] << " y:" << position1[1] << " z:" << position1[2] << "\n";
        
        ++numSteps;
        
        //if(numSteps%500==0){
        //    std::cout << "******************************************************\n";
        //    std::cout << "number of parts in rigid body container " << rigid_bodies.size() << "\n";
        //    std::cout << "******************************************************\n";
        //    VBF::Dynamic_Cylinder* part = new VBF::Dynamic_Cylinder(cylRad, cylHeight, partOrigin, mass2);
        //    rigid_bodies.push_back(part);
        //    vbf_world->add_rigid_bodies_to_world(part->get_rbody());
        //    }
        }while(!vbf_window->requested_exit());
      
    vbf_window->close_window();
    //stl_body->~ImportSTLSetup();
    //delete window;
    }
    
    
    catch(const std::runtime_error& e){
        std::cerr << "RUNTIME ERROR: " << e.what() << "\n";
        std::cerr << "Force aborting program\n";
        exit(-1);
    }
    /*! Catch statement with elipsis `...` catches any exception
    / that might not have been accounted for
    */
    catch(...){
        std::cerr << "ERROR : CAUGHT AN EXCEPTION OF UNDETERMINED TYPE\n"
                  << "FORCE EXITING THE PROGRAM\n";

        return -1;
    }
   
return 0;
}
