#ifndef KINEMATIC_MESH_BODY_H
#define KINEMATIC_MESH_BODY_H

#include <VBF_KinematicBody.hpp>

typedef GLInstanceGraphicsShape VBF_Mesh;

namespace VBF{

    class KinematicMeshBody{
    
        private:
            std::string m_filename;
            double m_scale;
            VBF_Mesh*  m_mesh;
            KinematicBody* m_VBF_kinematicBody;
        public:
            KinematicMeshBody(const std::string &fileName, double scale=0.1, btVector3 origin = btVector3(0.0, 0.0, 0.0),
                             size_t index=500);
            virtual ~KinematicMeshBody();
            KinematicBody* get_vbf_rbody() ;
            virtual VBF_Mesh* get_mesh() const noexcept;
            virtual std::string get_file_name() const noexcept;
            virtual btVector3 get_mesh_origin() const noexcept;
    };
}
#endif //KINEMATIC_MESH_BODY_H
