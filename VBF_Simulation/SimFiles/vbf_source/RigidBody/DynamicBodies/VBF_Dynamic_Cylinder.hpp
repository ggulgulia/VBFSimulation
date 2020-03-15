#ifndef DYNAMIC_CYLINDER_H
#define DYNAMIC_CYLINDER_H 

#include <VBF_DynamicBody.hpp>


/* @brief The interface creates a Dynamic Cylinder rigid body
 *
 * @details The construction of a cylinder proceeds through a call to the creation of a
 * bullet primitive cylinder of type btCylinderShape whose constructor takes a 3d vector 
 * whose  parameters can be interpreted as 
 * btVector3(cylinder_radius, 0.5*cylinder_height, cylinder_radius)
*/

namespace VBF{

    
    class Dynamic_Cylinder : public DynamicBody{

        private:
            double m_radius; //!< Radius of cylinder
            double m_height; //!< Height of cylinder

        public:
            
            //user constructor
            explicit Dynamic_Cylinder(double radius, double height,
                                      btVector3 origin, const double collMarg, double mass, 
                                      double linFriction=0.2, double rollingFriction=0.5, 
                                      double restitution=0.01, double linDamping=0.0, 
                                      double angularDamping=0.0, size_t index=221);

            //below two lines prevent expensive copy semantics
            Dynamic_Cylinder(const Dynamic_Cylinder&) = delete;
            Dynamic_Cylinder& operator=(Dynamic_Cylinder&) = delete;

            //Destructor
            ~Dynamic_Cylinder();

            /*! @brief Returns the radius of VBF::Static_Cylinder.
             *
             * @details Non-static, constant public member function that returns the value 
             * of private member m_radius of object VBF::Static_Cylinder. This method
             * is guaranteed to not thorw. 
             */
            double get_cylinder_radius() const noexcept;

            /*! @brief Returns the height of VBF::Static_Cylinder.
             *
             * @details Non-static, constant public member function that returns the value 
             * of private member m_height of object VBF::Static_Cylinder. This method
             * is guaranteed to not thorw. 
             */
            
            double get_cylinder_height() const noexcept;

            virtual std::string get_name() const noexcept override final;

    };
}//end of name space

#endif /* ifndef DYNAMIC_CUBE_H */

