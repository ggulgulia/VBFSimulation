#ifndef DYNAMIC_MESH_BODY_H
#define DYNAMIC_MESH_BODY_H

#include <VBF_DynamicBody.hpp>

typedef GLInstanceGraphicsShape VBF_Mesh;

namespace VBF{

    class DynamicMeshBody{
    
        private:
            std::string m_filename;
            double m_scale;
            VBF_Mesh*  m_mesh;
            DynamicBody* m_VBF_DynamicBody;
        public:
            DynamicMeshBody(const std::string &fileName, 
                            double scale=0.1, double mass=0.0, 
                            btVector3 origin = btVector3(0.0, 0.0, 0.0),
                            double linFriction=0.5, double rollingFriction=0.5, 
                            double restitution=0.2, double linDamping=0.0, 
                            double angularDamping=0.0, size_t index=601);
            virtual ~DynamicMeshBody();
            DynamicBody* get_vbf_rbody() ;
            virtual VBF_Mesh* get_mesh() const noexcept;
            virtual std::string get_file_name() const noexcept;
            virtual btVector3 get_mesh_origin() const noexcept;
    };
}
#endif //DYNAMIC_MESH_BODY_H
