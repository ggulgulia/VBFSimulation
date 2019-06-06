#include <VBF_DynamicMesh.hpp>
#include <../LoadMeshFromSTL.hpp>
#include <fstream>
#include <iostream>
#include <valarray> //for sin/cos functions


VBF::DynamicMeshBody::DynamicMeshBody(const std::string &fileName,
                                      double scale,  double mass,
                                      btVector3 origin,
                                      double linFriction, double rollingFriction, 
                                      double restitution, double linDamping, 
                                      double angularDamping, size_t index):
                                      m_filename(fileName), m_scale(scale)
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

    m_VBF_DynamicBody = new VBF::DynamicBody(m_filename, shape, origin, mass, 
                              linFriction, rollingFriction, restitution, 
                              linDamping, angularDamping, index);
}


VBF::DynamicMeshBody::~DynamicMeshBody(){
   delete m_mesh;
   delete m_VBF_DynamicBody;
   m_mesh = nullptr;
   m_VBF_DynamicBody = nullptr; //don't delete the resources 
                          // as it might be referred to by
                          // some other object
}

VBF::DynamicBody* VBF::DynamicMeshBody::get_vbf_rbody() {return m_VBF_DynamicBody;}
VBF_Mesh* VBF::DynamicMeshBody::get_mesh() const noexcept {return m_mesh;}
std::string VBF::DynamicMeshBody::get_file_name() const noexcept {return m_filename;}
btVector3 VBF::DynamicMeshBody::get_mesh_origin()const noexcept {return m_VBF_DynamicBody->get_origin();}
