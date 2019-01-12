#ifndef IMPORT_STL_SETUP_H
#define IMPORT_STL_SETUP_H


#include "GraphicsApp.hpp"
#include <string>
#include <fstream>
#include "VBF_World.hpp"

class ImportSTLSetup
{
    private:
	    GraphicsApp* m_app;
        std::string m_filename;
    public:
        ImportSTLSetup(const std::string &fileName, int width=640, int height=480);
        ImportSTLSetup(GraphicsApp* app);
        virtual ~ImportSTLSetup();
        
	    virtual void initPhysics();
};

#endif //IMPORT_OBJ_SETUP_H
