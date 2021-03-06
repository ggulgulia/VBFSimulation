/*! @file ImportSTLSetup.hpp */

#ifndef IMPORT_STL_SETUP_H
#define IMPORT_STL_SETUP_H

/*! This class assists in importing the an STL file having triangular mesh data. 
 * The Mesh filename and file path refer to the same data and is for the book keeping
 * purpose. 
 *
 * Note: Bullet is able to read only the stl files that are binary encoded. If ASCII encoded files
 * are given, the could be easily converted to binary files using an opensource tool (gmesh for 
 * example)
 */

#include <string>
#include <OpenGLWindow/GLInstanceGraphicsShape.h>
#include <bullet/btBulletDynamicsCommon.h>
#include <VBF_World.hpp>
#include <VBF_RigidBodies.hpp>

typedef GLInstanceGraphicsShape VBF_Mesh;

namespace VBF{

    /*! @class ImportSTLSetup
     * @brief Helper file to import STL trimesh data to VBF Simulation environments
     * @bug Two imported mesh penetrate rather than colliding with each other
     * @date 2019
     * @details This class assists in importing the an STL file having triangular mesh data. 
     * The Mesh filename and file path refer to the same data and is for the book keeping
     * purpose. 
     *
     * @note: Bullet is able to read only the stl files that are binary encoded. If ASCII encoded files
     * are given, the could be easily converted to binary files using an opensource tool (gmesh for 
     * example)
     */
    class ImportSTLSetup{
    
        private:            /*! Private memebers of Class ImportSTLSetup */
            std::string m_filename; /*! file path (also saved as file name)*/ 
            double m_scale;         /*! scaling factor for imported part*/
            double m_mass;         /*! mass of imported part. For static and Kinematic rigid bodies, they are 
                                       set to zero by default*/
            bool m_isKinematic;         /*! */
            VBF_Mesh*  m_mesh;         /*! Object that stores the mesh data for creating graphics instance.
                                           Need to find out the corresponding logic in bullet physics engine! */
            VBF::RigidBody* m_VBF_rbody; /*! Rigid body instance created from imported stl part */
            btVector3 m_origin;         /*! Origin of imported part*/
        public:

            /*! @brief Default constructor */
            ImportSTLSetup() = default;

            /*! user constructor for importing the part */
            ImportSTLSetup(const std::string &fileName, double scale=1.0, double mass=0.1, bool isKinematic=false, btVector3 origin = btVector3(0.0, 0.0, 0.0), int width=640, int height=480);

            /*! Destructor */
            virtual ~ImportSTLSetup();


            /*! @brief returns pointer to VBF_Mesh object */
            virtual VBF_Mesh* get_mesh() const noexcept;

            /*! @brief returns name of stl file from which the trimesh 
             * data is read 
             */
            virtual std::string get_file_name() const noexcept;

            /*! @breif returns the origin of the trimesh as specified 
             * during its import
             */
            virtual btVector3 get_mesh_origin() const noexcept;

            /*! @brief returns the pointer to the VBF::RigidBody
             * encapsulated in the trimesh data
             */
            virtual VBF::RigidBody* get_vbf_rbody() const noexcept;
    };
}
#endif //IMPORT_STL_SETUP_H
