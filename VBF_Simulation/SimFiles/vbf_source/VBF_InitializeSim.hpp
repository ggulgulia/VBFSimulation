/*! @file VBF_InitializeSim.hpp */

#ifndef INITIALIZE_SIM_H
#define INITIALIZE_SIM_H

#include <VBF_ReadInputData.hpp>
#include <VBF_World.hpp>
#include <VBF_CommonPhysics.hpp>
#include <VBF_GraphicsBridge.hpp>
#include <test_rigidBody.hpp>
namespace VBF{

    /*! @class InitializeSim
     * @brief initializes the simulation based on the 
     * parameteters and data defined in the input file
     * @date 2019
     */
    class InitializeSim{
        
        private:
            /*! @brief member containing the input data
             * @details the input data is parsed by the class object `ReadInputData`
             * and the member variable `m_inputData` is placeholder for all data 
             * (string and numeric including the names of the parameters) 
             * read from the input file
             */
            ReadInputData m_inputData;

            /*! @brief relative path (relative to executable file) of the
             * stl geometry of vibratory bowl feeder
             */
            std::string m_path_to_VBF_part;

            /*! @brief physics simulation world of type `VBF::World`
             */
            World* m_world = new World();

            /*! @brief simulation time step */
            double m_timeStep{0.0025};

            /*! @brief scaling factor for physical 
             * parts (doesn't apply to time scaling)
             */
            double m_scalingFactor{1.0};

            /*! @brief number of instances of the 
             * small parts moving through the vibrating
             * bowl to be simulated
             */
            size_t m_num_instances{10};

            /*! @brief containers of the pointer to
             * small parts moving through the vibrating
             * bowl
             */
            std::vector<VBF::RigidBody*> m_rigid_bodies;

            /*! @brief place holder (pointer) to kinematic vibratory
             * bolw feeder stl part
             */
            VBF::KinematicMeshBody* m_vbf_part{nullptr};

            /*! @brief placeholder (pointer) to dynamic 
             * small parts moving throw the 
             * vibratory bowl feeder
             */
            VBF::Dynamic_Cylinder* m_dyn_part{nullptr};

            /*! @brief placeholder (pointer) to the datum ground
             */
            VBF::StaticBody *m_ground{nullptr};

            /*! @brief physics object having the 
             * pyhsics settings
             */
            VBF::CommonPhysics m_vbf_phy;

            /*! @brief origin of vibratory bowl feeder stl part
             */
            btVector3 m_mesh_origin;

            /*! @brief initial origin of the small mechanical parts
             * moving through the vbf part
             */
            btVector3 m_part_origin;


            /*! @brief function to manage numeric parameter from the 
             * object `m_inputData`
             *
             * @details Since `m_inputData` holds data of types
             * numeric and string parametres, to initialize the simulation
             * object , this method access the numeric data from `m_inputData`
             *
             * @param key of type `std::string`
             * @output numeric parameter of type `double` represented by key
             * @warning user is responsible for ensuring that the
             * parameter exists
             */
            double get_numeric_input_parameter(const std::string& key){
                return m_inputData.get_numeric_value(key);
            }
            

            /*! @brief function to manage string parameter from the 
             * object `m_inputData`
             *
             * @details Since `m_inputData` holds data of types
             * numeric and string parametres, to initialize the simulation
             * object , this method access the string data from `m_inputData`
             *
             * @param key of type `std::string`
             * @output string parameter `std::string`represented by key
             * @warning user is responsible for ensuring that the
             * parameter exists
             */
            std::string get_string_input_parameter(const std::string& key){
                return m_inputData.get_string_value(key);
            }

            /*! @brief private method called by the constructor
             * to initialize member variables as per the conditions
             * specified in the input file. This method is 
             * called in the body of the constructor after the 
             * input file has been read.
             *
             * @note since the compiler initilizes the member variables 
             * in the order of declaration, even before the constructor
             * is entered, it is better to have default values for each member
             * variables when they are declared. This is more important 
             * for the current case since the values are initialized at run time
             * after the parameters have been read from the input file
             * in the body of the constructor, even after the object of 
             * type `InitializeSim` is completed
             */
            void initialize_data(){
                
                //lambda closure to return the numeric value held in 
                //m_inputData map.
                auto value_of_key = [&](auto&& key)->double {
                    return m_inputData.get_numeric_value(key);
                };
                
                
                m_world->initialize_new_world();
                m_world->set_gravity(btVector3(0.0, value_of_key("gravity"), 0.0));
                m_timeStep = value_of_key("time_step");
                m_scalingFactor = value_of_key("scaling_factor");
                const double collMarg = value_of_key("collision_margin");
                m_num_instances = value_of_key("num_instances");
                m_mesh_origin = btVector3(value_of_key("kin_start_posX"), 
                                                 value_of_key("kin_start_posY"), 
                                                 value_of_key("kin_start_posZ"));
                m_part_origin = btVector3(value_of_key("dyn_start_posX"),
                                                         value_of_key("dyn_start_posY"),
                                                         value_of_key("dyn_start_posZ"));
                const double cylRad = value_of_key("cylinder_radius");
                const double cylHeight = value_of_key("cylinder_height");
                const double dyn_mass = value_of_key("dyn_mass");

                m_vbf_part = new VBF::KinematicMeshBody(m_path_to_VBF_part, m_scalingFactor,
                                                        m_mesh_origin, collMarg);
                
                m_dyn_part = new VBF::Dynamic_Cylinder(cylRad, cylHeight, m_part_origin, 
                                                       collMarg, dyn_mass);

                m_ground = get_ground(collMarg);
                m_rigid_bodies.push_back(m_vbf_part->get_vbf_rbody());
                m_rigid_bodies.push_back(m_dyn_part);

                m_vbf_phy.init_physics(m_world, m_ground, m_rigid_bodies);
            }

        public:

            /*! @brief Compiler defined default constructor
             */
             InitializeSim() = default;

             /*! @brief compiler defined default destructr
              */
            ~InitializeSim() = default;

            /*! @brief constructor 
             * @param inputFileName, path_to_VBF_part
             * @details initializes the data members m_inputData
             * and m_path_to_VBF_part
             * and within the constructor body calls the 
             * private method `initialize_data()`
             *
             * @warning the constructor throws if
             * initialize_data() fails
             */
            InitializeSim(const std::string& inputFileName,
                         const std::string& path_to_VBF_part):
            m_inputData(inputFileName),
            m_path_to_VBF_part(path_to_VBF_part)
            {
                try{
                initialize_data();
                }
                catch(const std::exception& e){
                    std::cerr << e.what() << "\n";
                    abort();
                }
            }


        /*! @brief public method that returns collision margin
         * of physical bodies
         */
        const double get_collisionMargin(){
            return get_numeric_input_parameter("collision_margin");
        }
    
        /*! @brief public method that returns scaling factor
         * for physical bodies
         */
        const double get_scalingFactor(){
            return get_numeric_input_parameter("scaling_factor");
        }
    
        /*! @brief public method that returns origin of vbf part
         * as specified in the input file
         *
         */
        const btVector3 get_vbf_mesh_origin(){
            return m_mesh_origin;
        }
    
        /*! @brief public method that returns origin 
         * of dynamic small parts as in the input file
         * for physical bodies
         * 
         * @note this method should not be used for 
         * finding the origin of the dynamic parts
         * during simulation
         */
        const btVector3 get_dyn_part_origin(){
            return m_part_origin;
        }
    
        /*! @brief public method that returns scaling factor
         * for physical bodies
         */
        CommonPhysics& get_VBF_physics(){
            return m_vbf_phy;
        }

        /*! @brief returns a pointer to `VBF::World` 
         * object held in the simulation
         */
        World* get_VBF_world(){
            return m_world;
        }
    
        /*! @brief public method that returns a pointer 
         * to the vibrating bowl feeder part
         */
        KinematicMeshBody* get_vbf_part(){
            return m_vbf_part;
        }
    
        /*! @brief public method that returns a pointer
         * to the small parts moving over
         * the vibratory bowl feeder
         */
        VBF::Dynamic_Cylinder* get_dyn_part(){
            return m_dyn_part;
        }
    };

}
#endif /* ifndef INITIALIZE_SIM_H */
