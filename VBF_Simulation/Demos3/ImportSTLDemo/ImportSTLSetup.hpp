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
            VBF_Mesh*  m_mesh;
            std::string m_filename;
            VBF::RigidBody* m_VBF_rbody;
            btVector3 m_origin;
        public:
            ImportSTLSetup(const std::string &fileName, int width=640, int height=480, btVector3 origin = btVector3(0.0, 0.0, 0.0));
            virtual ~ImportSTLSetup();
            virtual VBF_Mesh* get_mesh() const;
            virtual std::string get_file_name() const;
            virtual btVector3 get_mesh_origin() const;
            virtual VBF::RigidBody* get_vbf_rbody() const;
    };
}
#endif //IMPORT_STL_SETUP_H
