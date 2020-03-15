#ifndef VBF_STATIC_CYLINDER_H
#define VBF_STATIC_CYLINDER_H 

/* @brief The interface creates a Static Cylinder rigid body
 *
 * @details The construction of a cylinder proceeds through a call to the creation of a
 * bullet primitive cylinder of type btCylinderShape whose constructor takes a 3d vector 
 * whose  parameters can be interpreted as 
 * btVector3(cylinder_radius, 0.5*cylinder_height, cylinder_radius)
*/

#include <VBF_StaticBody.hpp>

/*! typedefs for ugly bullet's datatypes
 *
 */
namespace VBF{
    
    class Static_Cylinder : public StaticBody{

        private:

            double m_radius; //!< Radius of cyinder
            double m_height; //!< Height of cylinder 

        public:
            Static_Cylinder(): StaticBody("Default Static Cylinder", 
                                new btCylinderShape(btVector3(0.50, 0.5*2.0, 0.50)),
                                btVector3(0.0,0.0, 0.0), 0.004, 33), 
                                m_radius(0.50), m_height(2.0) {
                            //empty constructor body
            }

            explicit Static_Cylinder(double radius, double height, btVector3 origin, 
                                    const double collMarg, size_t index);
            
            /*! @brief Preventing copy semantics for Static_Cylinder construction
             */
            Static_Cylinder(const Static_Cylinder&) = delete;


            /*! @brief Destructor
             */
            ~Static_Cylinder();

            /*! @brief Returns the radius of VBF::Static_Cylinder.
             *
             * @details Non-static, constant public member function that returns the value 
             * of private member m_radius of object VBF::Static_Cylinder. This method
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

#endif /* ifndef VBF_STATIC_CUBE_H */

