#ifndef VBF_KINEMATIC_CYLINDER_H
#define VBF_KINEMATIC_CYLINDER_H 

#include <VBF_KinematicBody.hpp>

namespace VBF{
    
    class Kinematic_Cylinder : public KinematicBody{

        private:
            double m_length; //!< edeg length of cube

        public:
            /*! @brief Deafault constructor
             *
             * @details This constructor creates a Kinematic Cube of  edge length 10.0 units
             * and the name of this cube is "Default Kinematic Cube"
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
            explicit Kinematic_Cylinder(double length, btVector3 origin, size_t index);

            /*! @brief Deleted copy constructor to prevent copy semantics.
             */
            Kinematic_Cylinder(const Kinematic_Cylinder&) = delete;

            /*! @brief Destructor
             */
            ~Kinematic_Cylinder();

            /*! @brief Returns the edge length of VBF::Kinematic_Cylinder.
             *
             * @details Non-static, constant public member function that returns the value 
             * of private member m_length of object VBF::Kinematic_Cylinder. This method
             * is guaranteed to not thorw. 
             */
            double get_length() const noexcept;
            virtual std::string get_name() const noexcept override final;
    };
}//end of name space

#endif /* ifndef VBF_KINEMATIC_CUBE_H */

