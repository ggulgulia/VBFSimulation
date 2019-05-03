#include "ImportSTLSetup.hpp"
#include "LoadMeshFromSTL.hpp"
#include "fstream"
#include <iostream>
#include <bullet/BulletCollision/Gimpact/btGImpactShape.h>
#include <bullet/BulletCollision/Gimpact/btGImpactCollisionAlgorithm.h>


VBF::ImportSTLSetup::ImportSTLSetup(const std::string &fileName,
                                    double scale, double mass,
                                    int width, 
                                    int height, btVector3 origin):
                                    m_filename(fileName), 
                                    m_scale(scale),
                                    m_mass(mass),
                                    m_origin(origin)
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

	btTransform trans;
	trans.setIdentity();
	btVector3 color(0,0,1);

    btTriangleMesh* trimeshData = new btTriangleMesh();
    int shiftVert;
    double xs(0.0), ys(0.0), zs(0.0); //'s' refers to shift
	double xV0{0.0}, yV0{0.0}, zV0{0.0};
    double xV1{0.0}, yV1{0.0}, zV1{0.0};
    double xV2{0.0}, yV2{0.0}, zV2{0.0};
    b3AlignedObjectArray<int>* meshIndices = m_mesh->m_indices;
    b3AlignedObjectArray<GLInstanceVertex>* meshVertices = m_mesh->m_vertices;
    shiftVert = meshIndices->at(0);
    xs = meshVertices->at(shiftVert).xyzw[0];
    ys = meshVertices->at(shiftVert).xyzw[1];
    zs = meshVertices->at(shiftVert).xyzw[2];

    xs = 0.0; ys = 0; zs = 0.0;
    //set the origin of the body as the 
    //coordinate of the first element
    m_origin[0] = 0.01-xs;
    m_origin[1] = -0.02-ys;
    m_origin[2] = 0.0-zs;
    int numVertices = m_mesh->m_numvertices;
	for (int ind0 = meshIndices->at(0), ind1 = meshIndices->at(1), ind2=meshIndices->at(2); ind2<numVertices; ind0+=3, ind1+=3, ind2+=3){

        xV0 = meshVertices->at(ind0).xyzw[0]-xs;
        yV0 = meshVertices->at(ind0).xyzw[1]-ys;
        zV0 = meshVertices->at(ind0).xyzw[2]-zs;

        xV1 = meshVertices->at(ind1).xyzw[0]-xs;
        yV1 = meshVertices->at(ind1).xyzw[1]-ys;
        zV1 = meshVertices->at(ind1).xyzw[2]-zs;

        xV2 = meshVertices->at(ind2).xyzw[0]-xs;
        yV2 = meshVertices->at(ind2).xyzw[1]-ys;
        zV2 = meshVertices->at(ind2).xyzw[2]-zs;

        btVector3 v0(xV0, yV0, zV0);
        btVector3 v1(xV1, yV1, zV1);
        btVector3 v2(xV2, yV2, zV2);
		
		trimeshData->addTriangle(v0,v1,v2);
	}


    //btConvexTriangleMeshShape *shape = new btConvexTriangleMeshShape(trimeshData);
	btGImpactMeshShape* shape = new btGImpactMeshShape(trimeshData);//meshInterface);
    m_origin[0] = -7.79; m_origin[1] = 12.5; m_origin[2] = 1.0;
    shape->updateBound();
    btTransform startTrans;
    startTrans.setIdentity();
    btQuaternion qt;
    qt.setEulerZYX(0,0,-1.57);
    startTrans.setRotation(qt);
    //btVector3 zAxis(0.0,0,1.0);
    //btQuaternion qt1(zAxis, -90);
    //btTransform startTrans(qt1);
    btVector3 meshInertia = btVector3(0.0, 0.0, 0.0);
    shape->calculateLocalInertia(m_mass, meshInertia);
    m_VBF_rbody = new VBF::RigidBody(m_filename, shape, m_origin,
                                    startTrans, m_mass, meshInertia);
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

VBF_Mesh* VBF::ImportSTLSetup::get_mesh() const noexcept {return m_mesh;}
std::string VBF::ImportSTLSetup::get_file_name() const noexcept {return m_filename;}
btVector3 VBF::ImportSTLSetup::get_mesh_origin()const noexcept {return m_origin;}
VBF::RigidBody* VBF::ImportSTLSetup::get_vbf_rbody() const noexcept {return m_VBF_rbody;}
