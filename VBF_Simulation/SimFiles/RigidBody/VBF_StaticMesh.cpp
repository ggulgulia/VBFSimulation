#include <VBF_StaticMesh.hpp>
#include <LoadMeshFromSTL.hpp>
#include <fstream>
#include <iostream>
#include <valarray> //for sin/cos functions


VBF::StaticMeshBody::StaticMeshBody(const std::string &fileName,
                                    double scale, btVector3 origin, size_t index):
                                    m_filename(fileName), m_scale(scale)
{
    std::fstream file;

    try{

        std::cout << "Attempting to read mesh data from file: " << fileName << "\n";
        m_mesh = LoadMeshFromSTL(m_filename, scale);
    }
    catch(const char* exception){
        std::cerr << "Error: " << exception << "\n";
        std::cerr << "Exception during construction of static mesh rigid body\n";
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
     m_VBF_staticBody = new StaticBody(m_filename, shape, origin, index);
}


VBF::StaticMeshBody::~StaticMeshBody(){
   delete m_mesh;
   delete m_VBF_staticBody;
   m_mesh = nullptr;
   m_VBF_staticBody = nullptr; //don't delete the resources 
                          // as it might be referred to by
                          // some other object
}

VBF::StaticBody* VBF::StaticMeshBody::get_vbf_rbody() {return m_VBF_staticBody;}
VBF_MeshShape* VBF::StaticMeshBody::get_mesh() const noexcept {return m_mesh;}
std::string VBF::StaticMeshBody::get_file_name() const noexcept {return m_filename;}
btVector3 VBF::StaticMeshBody::get_mesh_origin()const noexcept {return m_VBF_staticBody->get_origin();}
