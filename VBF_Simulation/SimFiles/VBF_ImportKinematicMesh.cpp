#include "VBF_ImportKinematicMesh.hpp"
#include "VBF_KinematicBody.hpp"
#include "LoadMeshFromSTL.hpp"
#include "fstream"
#include <iostream>
#include <bullet/BulletCollision/Gimpact/btGImpactShape.h>
#include <bullet/BulletCollision/Gimpact/btGImpactCollisionAlgorithm.h>
#include <valarray> //for sin/cos functions


//forward declaration of function
btGImpactMeshShape* triMeshToCollisionShape(const VBF_Mesh*const mesh);

VBF::KinematicMeshBody::KinematicMeshBody(const std::string &fileName,
                                    double scale, btVector3 origin,
                                    int width, int height, size_t index):
                                    m_filename(fileName), 
                                    m_scale(scale)
{
    std::fstream file;

    try{

        std::cout << "Attempting to read mesh data from file: " << fileName << "\n";
        m_mesh = LoadMeshFromSTL(m_filename, scale);
    }
    catch(const char* exception){
        std::cerr << "Error: " << exception << "\n";
        std::cerr << "Force exiting the program\n";
        exit(-1);
    }

	btGImpactMeshShape* shape = triMeshToCollisionShape(m_mesh);
    origin[0] *= scale; 
    origin[1] *= scale; 
    origin[2] *= scale;
    double colMargin{0.005};
    shape->setMargin(colMargin);
    shape->updateBound();
     m_VBF_kinematicBody = new KinematicBody(m_filename, shape, origin, index);
}


VBF::KinematicMeshBody::~KinematicMeshBody(){
   delete m_mesh;
   delete m_VBF_kinematicBody;
   m_mesh = nullptr;
   m_VBF_kinematicBody = nullptr; //don't delete the resources 
                          // as it might be referred to by
                          // some other object
}

VBF::KinematicBody* VBF::KinematicMeshBody::get_vbf_rbody() {return m_VBF_kinematicBody;}
VBF_Mesh* VBF::KinematicMeshBody::get_mesh() const noexcept {return m_mesh;}
std::string VBF::KinematicMeshBody::get_file_name() const noexcept {return m_filename;}
btVector3 VBF::KinematicMeshBody::get_mesh_origin()const noexcept {return m_VBF_kinematicBody->get_origin();}


//internal routine to convert tri mesh data to a sensible bullet rigid body
btGImpactMeshShape* triMeshToCollisionShape(const VBF_Mesh*const mesh){

    btTriangleMesh* trimeshData = new btTriangleMesh();
	double xV0{0.0}, yV0{0.0}, zV0{0.0};
    double xV1{0.0}, yV1{0.0}, zV1{0.0};
    double xV2{0.0}, yV2{0.0}, zV2{0.0};
    b3AlignedObjectArray<int>* meshIndices = mesh->m_indices;
    b3AlignedObjectArray<GLInstanceVertex>* meshVertices = mesh->m_vertices;

    //set the origin of the body as the 
    //coordinate of the first element
    int numVertices = mesh->m_numvertices;
	for (int ind0 = meshIndices->at(0), ind1 = meshIndices->at(1), ind2=meshIndices->at(2); ind2<numVertices; ind0+=3, ind1+=3, ind2+=3){

        xV0 = meshVertices->at(ind0).xyzw[0];
        yV0 = meshVertices->at(ind0).xyzw[1];
        zV0 = meshVertices->at(ind0).xyzw[2];

        xV1 = meshVertices->at(ind1).xyzw[0];
        yV1 = meshVertices->at(ind1).xyzw[1];
        zV1 = meshVertices->at(ind1).xyzw[2];

        xV2 = meshVertices->at(ind2).xyzw[0];
        yV2 = meshVertices->at(ind2).xyzw[1];
        zV2 = meshVertices->at(ind2).xyzw[2];

        btVector3 v0(xV0, yV0, zV0);
        btVector3 v1(xV1, yV1, zV1);
        btVector3 v2(xV2, yV2, zV2);
		
		trimeshData->addTriangle(v0,v1,v2);
	}
    return new btGImpactMeshShape(trimeshData);
}

