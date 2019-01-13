#ifndef IMPORT_STL_SETUP_H
#define IMPORT_STL_SETUP_H


#include <string>
#include <OpenGLWindow/GLInstanceGraphicsShape.h>
#include <bullet/btBulletDynamicsCommon.h>
#include <bullet/btBulletDynamicsCommon.h>
//#include <OpenGLWindow/GLInstancingRenderer.h>
#include "VBF_World.hpp"

typedef GLInstanceGraphicsShape VBF_Mesh;

namespace VBF{

    class ImportSTLSetup{
    
        private:
            VBF_Mesh*  m_mesh;
            std::string m_filename;
        public:
            ImportSTLSetup(const std::string &fileName, int width=640, int height=480);
            virtual ~ImportSTLSetup();
            virtual VBF_Mesh* get_mesh();
            virtual std::string get_file_name();
    };
}
#endif //IMPORT_STL_SETUP_H
