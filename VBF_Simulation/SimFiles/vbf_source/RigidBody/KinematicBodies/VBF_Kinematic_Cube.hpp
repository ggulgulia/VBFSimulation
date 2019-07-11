#ifndef VBF_KINEMATIC_CUBE_H
#define VBF_KINEMATIC_CUBE_H 

#include <VBF_KinematicBody.hpp>

namespace VBF{
    
    class Kinematic_Cube : public KinematicBody{

        private:
            double m_length; //!< edeg length of cube

        public:
            /*! @brief Deafault constructor
             *
             * @details This constructor creates a Kinematic Cube of  edge length 10.0 units
             * and the name of this cube is "Default Kinematic Cube"
             */
            Kinematic_Cube();

            /*! @brief User consructor 
             *
             * @details The user constructor creates kinematic cube of specified length
             * at the location specified by the origin. The constructor is explicit meaning
             * initialization by assinment is not possible.
             *
             * @param length : edge length of VBF::Kinematic_Cube
             * @param origin : vector specifying the location of center of mass of cube 
             * @param index : index of kinematic cube for book keeping purpose 
             */
            explicit Kinematic_Cube(double length, btVector3 origin, size_t index);

            /*! @brief Deleted copy constructor to prevent copy semantics.
             */
            Kinematic_Cube(const Kinematic_Cube&) = delete;

            /*! @brief Destructor
             */
            ~Kinematic_Cube();

            /*! @brief Returns the edge length of VBF::Kinematic_Cube.
             *
             * @details Non-static, constant public member function that returns the value 
             * of private member m_length of object VBF::Kinematic_Cube. This method
             * is guaranteed to not thorw. 
             */
            double get_length() const noexcept;
            virtual std::string get_name() const noexcept override final;
    };
}//end of name space

#endif /* ifndef VBF_KINEMATIC_CUBE_H */

