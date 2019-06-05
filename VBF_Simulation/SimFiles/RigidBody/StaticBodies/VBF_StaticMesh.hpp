#ifndef STATIC_MESH_BODY_H
#define STATIC_MESH_BODY_H

#include <bullet/BulletCollision/Gimpact/btGImpactShape.h>
#include <bullet/BulletCollision/Gimpact/btGImpactCollisionAlgorithm.h>
#include <OpenGLWindow/GLInstanceGraphicsShape.h>
#include <VBF_StaticBody.hpp>

#include <../LoadMeshFromSTL.hpp>

namespace VBF{

    class StaticMeshBody{
    
        private:
            std::string m_filename;
            double m_scale;
            VBF_MeshShape*  m_mesh;
            StaticBody* m_VBF_staticBody;
        public:
            StaticMeshBody(const std::string &fileName, double scale=0.1, btVector3 origin = btVector3(0.0, 0.0, 0.0),
                             size_t index=500);
            virtual ~StaticMeshBody();
            StaticBody* get_vbf_rbody() ;
            virtual VBF_MeshShape* get_mesh() const noexcept;
            virtual std::string get_file_name() const noexcept;
            virtual btVector3 get_mesh_origin() const noexcept;
    };
}
#endif //STATIC_MESH_BODY_H
