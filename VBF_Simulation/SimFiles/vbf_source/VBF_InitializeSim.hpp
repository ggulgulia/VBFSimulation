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
            double m_collisionMargin{0.004};
            size_t m_num_instances{10};
            //std::vector<VBF::RigidBody*> m_rigid_bodies(120);
            VBF::KinematicMeshBody* m_vbf_part{nullptr};

            void initialize_data(){
                
                //lambda closure to return the value held in 
                //m_inputData map. The lambda expression
                //captures m_inputData member by reference
                //and key by forwarding reference
                auto value_of_key = [&] (auto&& key){
                    return m_inputData[key];
                };

                m_world->initialize_new_world();
                m_world->set_gravity(btVector3(0.0, value_of_key("gravity"), 0.0));
                m_timeStep = value_of_key("time_step");
                m_scalingFactor = value_of_key("scalingFactor");
                m_collisionMargin = value_of_key("collision_margin");
                m_num_instances = value_of_key("num_instances");
                const btVector3 meshOrigin = btVector3(value_of_key("kin_start_posX"), 
                                                 value_of_key("kin_start_posY"), 
                                                 value_of_key("kin_start_posZ"));

                /*VBF::KinematicMeshBody*/ m_vbf_part = new VBF::KinematicMeshBody(m_path_to_VBF_part, m_scalingFactor, meshOrigin);
                //m_rigid_bodies.push_back(vbf_part->get_vbf_rbody());
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


    };
}
#endif /* ifndef INITIALIZE_SIM_H */
