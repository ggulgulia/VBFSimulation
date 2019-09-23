#ifndef INITIALIZE_SIM_H
#define INITIALIZE_SIM_H

#include <VBF_ReadInputData.hpp>
#include <VBF_World.hpp>
#include <VBF_CommonPhysics.hpp>
#include <VBF_GraphicsBridge.hpp>
#include <test_rigidBody.hpp>
namespace VBF{

    class InitializeSim{
        
        private:
            ReadInputData m_inputData;
            std::string m_path_to_VBF_part;
            World* m_world = new World();
            double m_timeStep{0.0025};
            double m_scalingFactor{1.0};
            size_t m_num_instances{10};
            std::vector<VBF::RigidBody*> m_rigid_bodies;
            VBF::KinematicMeshBody* m_vbf_part{nullptr};
            VBF::Dynamic_Cylinder* m_dyn_part{nullptr};
            VBF::StaticBody *m_ground{nullptr};
            VBF::CommonPhysics m_vbf_phy;
            btVector3 m_mesh_origin;
            btVector3 m_part_origin;

            double get_numeric_input_parameter(const std::string& key){
                return m_inputData.get_numeric_value(key);
            }
            
            std::string get_string_input_parameter(const std::string& key){
                return m_inputData.get_string_value(key);
            }

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

             InitializeSim() = default;
            ~InitializeSim() = default;

            InitializeSim(const std::string& inputFileName,
                         const std::string& path_to_VBF_part):
            m_inputData(inputFileName),
            m_path_to_VBF_part(path_to_VBF_part)
            {
                initialize_data();
    
                //storage for rigid bodies
                //std::vector<VBF::RigidBody*> rigid_bodies;

                ////! create a reference ground
                //btVector3 meshOrigin{btVector3(0.0, 0.0, 00.0)} ;
                //VBF::KinematicMeshBody* stl_body = new VBF::KinematicMeshBody(m_path_to_VBF_part, m_scalingFactor, meshOrigin);
                //rigid_bodies.push_back(stl_body->get_vbf_rbody());
            }


    const double get_collisionMargin(){
        return get_numeric_input_parameter("collision_margin");
    }

    const double get_scalingFactor(){
        return get_numeric_input_parameter("scaling_factor");
    }

    const btVector3 get_vbf_mesh_origin(){
        return m_mesh_origin;
    }

    const btVector3 get_dyn_part_origin(){
        return m_part_origin;
    }

    CommonPhysics& get_VBF_physics(){
        return m_vbf_phy;
    }
    World* get_VBF_world(){
        return m_world;
    }

    KinematicMeshBody* get_vbf_part(){
        return m_vbf_part;
    }

    VBF::Dynamic_Cylinder* get_dyn_part(){
        return m_dyn_part;
    }
    };

}
#endif /* ifndef INITIALIZE_SIM_H */
