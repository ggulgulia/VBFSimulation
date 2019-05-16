#ifndef IMPORT_STL_SETUP_H
#define IMPORT_STL_SETUP_H


#include <string>
#include <OpenGLWindow/GLInstanceGraphicsShape.h>
#include <bullet/btBulletDynamicsCommon.h>
#include "VBF_World.hpp"
#include "VBF_RigidBodies.hpp"

typedef GLInstanceGraphicsShape VBF_Mesh;

namespace VBF{

    class ImportSTLSetup{
    
        private:
            std::string m_filename;
            double m_scale;
            double m_mass;
            bool m_isKinematic;
            VBF_Mesh*  m_mesh;
            VBF::RigidBody* m_VBF_rbody;
            btVector3 m_origin;
        public:
            ImportSTLSetup(const std::string &fileName, double scale=0.1, double mass=0.1, bool isKinematic=false, btVector3 origin = btVector3(0.0, 0.0, 0.0),
                           int width=640, int height=480);
            virtual ~ImportSTLSetup();
            virtual VBF_Mesh* get_mesh() const noexcept;
            virtual std::string get_file_name() const noexcept;
            virtual btVector3 get_mesh_origin() const noexcept;
            virtual VBF::RigidBody* get_vbf_rbody() const noexcept;
    };
}
#endif //IMPORT_STL_SETUP_H
