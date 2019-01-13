#include "ImportSTLSetup.hpp"
#include "VBF_World.hpp"
#include "VBF_GraphicsBridge.hpp"
#include <OpenGLWindow/SimpleOpenGL3App.h>

int main(int argc, char *argv[]){

    VBF::World* vbf_world = new VBF::World();
    vbf_world->initialize_new_world();
    std::string fileName("l_finger_tip.stl");
    VBF::Window* vbf_window = new VBF::Window(vbf_world, 800, 600, "Hello VBF World");
    //vbf_window->create_window();
    VBF::ImportSTLSetup* stl_body = new VBF::ImportSTLSetup(fileName);    

    return 0;
}

