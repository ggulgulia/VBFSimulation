#include "ImportSTLSetup.hpp"
#include "LoadMeshFromSTL.hpp"
#include "fstream"
#include <iostream>

VBF::ImportSTLSetup::ImportSTLSetup(const std::string &fileName,
                              int width, 
                              int height, btVector3 origin,
                              double scaling_factor):
                              m_filename(fileName), 
                              m_origin(origin),
                              m_scale(scaling_factor)
{
    std::fstream file;

    try{

        std::cout << "Attempting to read mesh data from file: " << fileName << "\n";
        m_mesh = LoadMeshFromSTL(m_filename, scaling_factor);
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
    int shiftVert;
    double xs(0.0), ys(0.0), zs(0.0); //'s' refers to shift
    shiftVert = m_mesh->m_indices->at(0);
    xs = m_mesh->m_vertices->at(shiftVert).xyzw[0];
    ys = m_mesh->m_vertices->at(shiftVert).xyzw[1];
    zs = m_mesh->m_vertices->at(shiftVert).xyzw[2];


    b3AlignedObjectArray<int>* meshIndices = m_mesh->m_indices;
    int numVertices = m_mesh->m_numvertices;
	for (int ind0 = meshIndices->at(0), ind1 = meshIndices->at(1), ind2=meshIndices->at(2); ind2<numVertices; ind0+=3, ind1+=3, ind2+=3){
		
		btVector3 v0(m_mesh->m_vertices->at(ind0).xyzw[0]-xs,
					 m_mesh->m_vertices->at(ind0).xyzw[1]-ys,
					 m_mesh->m_vertices->at(ind0).xyzw[2]-zs);
		btVector3 v1(m_mesh->m_vertices->at(ind1).xyzw[0]-xs,
					 m_mesh->m_vertices->at(ind1).xyzw[1]-ys,
					 m_mesh->m_vertices->at(ind1).xyzw[2]-zs);
		btVector3 v2(m_mesh->m_vertices->at(ind2).xyzw[0]-xs,
					 m_mesh->m_vertices->at(ind2).xyzw[1]-ys,
					 m_mesh->m_vertices->at(ind2).xyzw[2]-zs);
		
		trimeshData->addTriangle(v0,v1,v2);
	}

	btBvhTriangleMeshShape* shape = new btBvhTriangleMeshShape(trimeshData,true);//meshInterface);
    btVector3 xAxis(-1,0.25,0.2);
    btQuaternion qt1(xAxis, -30);
    btTransform startTrans(qt1);
    btVector3 meshInertia = btVector3(0.0, 0.0, 0.0);
    double meshMass(1);
    //btRigidBody* body = this->createRigidBody(0,startTrans,shape);
    m_VBF_rbody = new VBF::RigidBody(m_filename, shape, m_origin,
                                    startTrans, meshMass, meshInertia);
    m_VBF_rbody->set_gravity();
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
