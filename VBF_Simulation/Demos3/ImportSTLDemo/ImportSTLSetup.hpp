#ifndef IMPORT_STL_SETUP_H
#define IMPORT_STL_SETUP_H


#include "CommonRigidBodySetup.h"
#include "GraphicsApp.hpp"
#include <string>
#include <fstream>


class ImportSTLSetup : public CommonRigidBodySetup
{
    private:
	    GraphicsApp* m_app;
        std::string m_filename;
    public:
        ImportSTLSetup(std::string fileName, int width=640, int height=480);
        ImportSTLSetup(GraphicsApp* app);
        virtual ~ImportSTLSetup();
        
	    virtual void initPhysics(GraphicsPhysicsBridge& gfxBridge);
};

#endif //IMPORT_OBJ_SETUP_H
