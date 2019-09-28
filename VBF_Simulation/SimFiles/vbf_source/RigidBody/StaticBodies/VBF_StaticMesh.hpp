#ifndef STATIC_MESH_BODY_H
#define STATIC_MESH_BODY_H

/*! 
 * \section intro_sec Introduction
 * The objective of this class is to import a triangular mesh data from a binary encoded
 * stl file and create a static rigid body for bullet physics
 */ 

#include <bullet/BulletCollision/Gimpact/btGImpactShape.h>
#include <bullet/BulletCollision/Gimpact/btGImpactCollisionAlgorithm.h>
#include <OpenGLWindow/GLInstanceGraphicsShape.h>
#include <VBF_StaticBody.hpp>

#include <../LoadMeshFromSTL.hpp>

namespace VBF{

    class StaticMeshBody {
    
        /*! \subsection private_members Private memebers of the class StaticMeshBody
         */

        private:
            std::string m_filename;  /*! path to binary stl file having mesh data*/
            double m_scale;          /*! scaling factor */
            VBF_MeshShape*  m_mesh;  /*! Graphic instance of mesh data */
            StaticBody* m_VBF_staticBody; /* VBF::StaticBody instance created from imported mesh */
        public:

            /*! \subsection public_members Public Members
             */

            /*! User constructor. The fileName is same as file path. The function may throw due to 
             * several reasons. Look at the helper file LoadSTLMesh.hpp
             */
            StaticMeshBody(const std::string &fileName, double scale=1.0,
                           btVector3 origin = btVector3(0.0, 0.0, 0.0), 
                           const double collMarg=0.004, size_t index=500);

            /*! Virtual Destructor does nothing at the moment
             */
            virtual ~StaticMeshBody();

            /*! non constant non static member function that returns the rigid body 
             * object from the StaticMeshBody class. This is particularly useful when the 
             * rigid bodies are to be added to the Physics World (VBF_World) where all rigid 
             * bodies interact (and sometimes not interact if they are static body for example)
             */
            StaticBody* get_vbf_rbody() ;

            /*! returns the graphics instance of the mesh. This function is 
             * guaranteed to not throw
             */
            virtual VBF_MeshShape* get_mesh() const noexcept;

            /*! returns path to file name of the binary encoded stl file
             * This function is guaranteed to not throw.
             */
            virtual std::string get_file_name() const noexcept;

            /*! non-static constant member function that returns the origin of the 
             * mesh file. Note the origin may not be the same as origin of the imported
             * mesh during its construction because the mesh may have interated with surrounding
             * objects and may have changed its position.
             * This function is guaranteed to not throw
             */
            virtual btVector3 get_mesh_origin() const noexcept;
    };
}
#endif //STATIC_MESH_BODY_H
