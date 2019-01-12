#include "ImportSTLSetup.hpp"
#include "LoadMeshFromSTL.hpp"
#include <vector>
//#include <OpenGLWindow/GLInstancingRenderer.h>
#include <OpenGLWindow/GLInstanceGraphicsShape.h>
#include <bullet/btBulletDynamicsCommon.h>
#include <OpenGLWindow/SimpleOpenGL3App.h>



ImportSTLSetup::ImportSTLSetup(const std::string &fileName,
                              int width, 
                              int height):
                              m_filename(fileName)
                              //m_app(new GraphicsApp(fileName.c_str(),width, height))
{

}


ImportSTLSetup::ImportSTLSetup(GraphicsApp* app)
:m_app(app)
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
	for (int i=0;i<numPrefixes;i++)
	{
		//f = fopen(relativeFileName,"r");
        file.open(m_filename);
		if (file.is_open())
		{
			//fclose(f);
            file.close();
			prefixIndex = i;
			break;
		}
	}
	
	
	if (prefixIndex<0)
		return;
	
	btVector3 shift(0,0,0);
	btVector3 scaling(10,10,10);
	GLInstanceGraphicsShape* gfxShape = LoadMeshFromSTL(m_filename.c_str());
	btTransform trans;
	trans.setIdentity();
	trans.setRotation(btQuaternion(btVector3(1,0,0),SIMD_HALF_PI));
	btVector3 position = trans.getOrigin();
	btQuaternion orn = trans.getRotation();
	btVector3 color(0,0,1);
	int shapeId = m_app->get_renderer_interface()->registerShape(&gfxShape->m_vertices->at(0).xyzw[0], gfxShape->m_numvertices, &gfxShape->m_indices->at(0), gfxShape->m_numIndices);
	m_app->get_renderer_interface()->registerGraphicsInstance(shapeId,position,orn,color,scaling);

	
}

int main(int argc, char *argv[]){

    VBF::World* vbf_world = new VBF::World();
    vbf_world->initialize_new_world();
    std::string fileName("l_finger_tip.stl");
    ImportSTLSetup* stl_body = new ImportSTLSetup(fileName);    
    stl_body->initPhysics();

    return 0;
}

