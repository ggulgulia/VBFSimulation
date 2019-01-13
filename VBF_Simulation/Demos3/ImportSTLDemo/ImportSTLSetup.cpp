#include "ImportSTLSetup.hpp"
#include "LoadMeshFromSTL.hpp"
#include <vector>
//#include <OpenGLWindow/GLInstancingRenderer.h>
#include <OpenGLWindow/GLInstanceGraphicsShape.h>
#include <bullet/btBulletDynamicsCommon.h>
#include <OpenGLWindow/SimpleOpenGL3App.h>
#include "VBF_GraphicsBridge.hpp"



ImportSTLSetup::ImportSTLSetup(const std::string &fileName,
                              int width, 
                              int height):
                              m_filename(fileName)
{

}


ImportSTLSetup::~ImportSTLSetup()
{
    
}


void ImportSTLSetup::initPhysics()
{
    //this line is causing segmentation fault
    //the member m_dynamicsWorld doesn't have any method getDebugDrawer()
	//m_dynamicsWorld->getDebugDrawer()->setDebugMode(btIDebugDraw::DBG_DrawWireframe);

    std::fstream file;
	int prefixIndex=-1;
    int numPrefixes = 2;
	
	btVector3 shift(0,0,0);
	btVector3 scaling(10,10,10);
	GLInstanceGraphicsShape* gfxShape = LoadMeshFromSTL(m_filename);
	btTransform trans;
	trans.setIdentity();
	trans.setRotation(btQuaternion(btVector3(1,0,0),SIMD_HALF_PI));
	btVector3 position = trans.getOrigin();
	btQuaternion orn = trans.getRotation();
	btVector3 color(0,0,1);

	
}

int main(int argc, char *argv[]){

    VBF::World* vbf_world = new VBF::World();
    vbf_world->initialize_new_world();
    std::string fileName("l_finger_tip.stl");
    VBF::Window* vbf_window = new VBF::Window(vbf_world, 800, 600, "Hello VBF World");
    //vbf_window->create_window();

    ImportSTLSetup* stl_body = new ImportSTLSetup(fileName);    
    stl_body->initPhysics();

    return 0;
}

