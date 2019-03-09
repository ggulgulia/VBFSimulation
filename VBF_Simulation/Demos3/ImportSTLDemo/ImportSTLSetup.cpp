#include "ImportSTLSetup.hpp"
#include "LoadMeshFromSTL.hpp"
#include "fstream"
#include <iostream>

VBF::ImportSTLSetup::ImportSTLSetup(const std::string &fileName,
                              int width, 
                              int height, btVector3 origin):
                              m_filename(fileName), 
                              m_origin(origin)
{
	btVector3 shift(0,0,0);
	btVector3 scaling(10,10,10);
    std::fstream file;

    try{

        std::cout << "Attempting to read mesh data from file: " << fileName << "\n";
        m_mesh = LoadMeshFromSTL(m_filename);
    }
    catch(const char* exception){
        std::cerr << "Error: " << exception << "\n";
        std::cerr << "Force exiting the program\n";
        exit(-1);
    }

	btTransform trans;
	trans.setIdentity();
	btVector3 color(0,0,1);

    btTriangleMesh* trimeshData = new btTriangleMesh();
	for (int i=0;i<m_mesh->m_numvertices;i++)
	{
		for (int j=0;j<3;j++)
			m_mesh->m_vertices->at(i).xyzw[j] += shift[j];
	}
    
    int shiftVert;
    double xs, ys, zs; //'s' refers to shift
    shiftVert = m_mesh->m_indices->at(0);
    xs = m_mesh->m_vertices->at(shiftVert).xyzw[0];
    ys = m_mesh->m_vertices->at(shiftVert).xyzw[1];
    zs = m_mesh->m_vertices->at(shiftVert).xyzw[2];
	for (int i=0;i<m_mesh->m_numIndices;i+=3)
	{
		int index0 = m_mesh->m_indices->at(i);
		int index1 = m_mesh->m_indices->at(i+1);
		int index2 = m_mesh->m_indices->at(i+2);
		
		btVector3 v0(m_mesh->m_vertices->at(index0).xyzw[0]-xs,
									m_mesh->m_vertices->at(index0).xyzw[1]-ys,
									m_mesh->m_vertices->at(index0).xyzw[2]-zs);
		btVector3 v1(m_mesh->m_vertices->at(index1).xyzw[0]-xs,
					 m_mesh->m_vertices->at(index1).xyzw[1]-ys,
					 m_mesh->m_vertices->at(index1).xyzw[2]-zs);
		btVector3 v2(m_mesh->m_vertices->at(index2).xyzw[0]-xs,
					 m_mesh->m_vertices->at(index2).xyzw[1]-ys,
					 m_mesh->m_vertices->at(index2).xyzw[2]-zs);
		
		trimeshData->addTriangle(v0,v1,v2);
	}
	btBvhTriangleMeshShape* shape = new btBvhTriangleMeshShape(trimeshData,true);//meshInterface);
    btVector3 xAxis(1,0,0);
    btQuaternion qt1(xAxis, -20);
    btTransform startTrans(qt1);
    //startTrans.setIdentity();
    
    //get the origin (should be 0,0,0);
    int indOrigin;
    double x0, y0, z0;
    indOrigin = m_mesh->m_indices->at(0);
    x0 = m_mesh->m_vertices->at(indOrigin).xyzw[0];
    y0 = m_mesh->m_vertices->at(indOrigin).xyzw[1];
    z0 = m_mesh->m_vertices->at(indOrigin).xyzw[2];
    //m_origin = btVector3(0.0, 0.0, 0.0);
    btVector3 meshInertia = btVector3(0.0, 0.0, 0.0);
    double meshMass(1);
    //btRigidBody* body = this->createRigidBody(0,startTrans,shape);
    m_VBF_rbody = new VBF::RigidBody(m_filename, shape, m_origin,
                                    startTrans, meshMass, meshInertia);
//m_VBF_rbody->getWorldTransform().setRotation(qt); 
}


VBF::ImportSTLSetup::~ImportSTLSetup(){
delete m_mesh;
   delete m_VBF_rbody;
   m_mesh = nullptr;
   m_VBF_rbody = nullptr; //don't delete the resources 
                          // as it might be referred to by
                          // some other object
}

VBF_Mesh* VBF::ImportSTLSetup::get_mesh() const {return m_mesh;}
std::string VBF::ImportSTLSetup::get_file_name() const {return m_filename;}
btVector3 VBF::ImportSTLSetup::get_mesh_origin()const {return m_origin;}
VBF::RigidBody* VBF::ImportSTLSetup::get_vbf_rbody() const {return m_VBF_rbody;}
