#include "ImportSTLSetup.hpp"
#include "LoadMeshFromSTL.hpp"

VBF::ImportSTLSetup::ImportSTLSetup(const std::string &fileName,
                              int width, 
                              int height):
                              m_filename(fileName)
{
	btVector3 shift(0,0,0);
	btVector3 scaling(10,10,10);
	m_mesh = LoadMeshFromSTL(m_filename);
	btTransform trans;
	trans.setIdentity();
	trans.setRotation(btQuaternion(btVector3(1,0,0),SIMD_HALF_PI));
	btVector3 position = trans.getOrigin();
	btQuaternion orn = trans.getRotation();
	btVector3 color(0,0,1);

}

VBF::ImportSTLSetup::~ImportSTLSetup(){
   delete m_mesh;
   m_mesh = nullptr;
}

VBF_Mesh* VBF::ImportSTLSetup::get_mesh() {return m_mesh;}
std::string VBF::ImportSTLSetup::get_file_name(){return m_filename;}
