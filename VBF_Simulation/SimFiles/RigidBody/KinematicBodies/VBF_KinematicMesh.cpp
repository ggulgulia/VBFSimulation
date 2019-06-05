#include <VBF_KinematicMesh.hpp>
#include <../LoadMeshFromSTL.hpp>
#include <fstream>
#include <iostream>
#include <valarray> //for sin/cos functions


VBF::KinematicMeshBody::KinematicMeshBody(const std::string &fileName,
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
