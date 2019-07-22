#ifndef VBF_KINEMATIC_CYLINDER_H
#define VBF_KINEMATIC_CYLINDER_H 

#include <VBF_KinematicBody.hpp>


/* @brief The interface creates a Kinematic Cylinder rigid body
 *
 * @details The construction of a cylinder proceeds through a call to the creation of a
 * bullet primitive cylinder of type btCylinderShape whose constructor takes a 3d vector 
 * whose  parameters can be interpreted as 
 * btVector3(cylinder_radius, 0.5*cylinder_height, cylinder_radius)
*/

namespace VBF{
    
    class Kinematic_Cylinder : public KinematicBody{

        private:
            double m_radius; //!< Radius of cyinder
            double m_height; //!< Height of cylinder 

        public:
            /*! @brief Deafault constructor
             *
             * @details This constructor creates a Kinematic Cube of  radius 0.5 and height 2.0
             * and the name of this cube is "Default Kinematic Cylinder"
             */
            Kinematic_Cylinder();

            /*! @brief User consructor 
             *
             * @details The user constructor creates kinematic cube of specified length
             * at the location specified by the origin. The constructor is explicit meaning
             * initialization by assinment is not possible.
             *
             * @param length : edge length of VBF::Kinematic_Cylinder
             * @param origin : vector specifying the location of center of mass of cube 
             * @param index : index of kinematic cube for book keeping purpose 
             */
            explicit Kinematic_Cylinder(double radius, double height, 
                                        btVector3 origin, size_t index);

            /*! @brief Deleted copy constructor to prevent copy semantics.
             */
            Kinematic_Cylinder(const Kinematic_Cylinder&) = delete;

            /*! @brief Destructor
             */
            ~Kinematic_Cylinder();

            /*! @brief Returns the radius of VBF::Kinematic_Cylinder.
             *
             * @details Non-static, constant public member function that returns the value 
             * of private member m_radius of object VBF::Kinematic_Cylinder. This method
             * is guaranteed to not thorw. 
             */
            double get_cylinder_radius() const noexcept;

            /*! @brief Returns the height of VBF::Kinematic_Cylinder.
             *
             * @details Non-static, constant public member function that returns the value 
             * of private member m_height of object VBF::Kinematic_Cylinder. This method
             * is guaranteed to not thorw. 
             */
            double get_cylinder_height() const noexcept;
            virtual std::string get_name() const noexcept override final;
    };
}//end of name space

#endif /* ifndef VBF_KINEMATIC_CUBE_H */

