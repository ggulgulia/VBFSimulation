#ifndef VBF_STATIC_CUBE_H
#define VBF_STATIC_CUBE_H 

/*! @brief Class file for VBF::StaticCube
 *
 * @details This class encapsulates the bullet's data structure for a Cube but ensures that
 * all the cube object generated through this calss object are static rigid body. This class
 * has only one private member that dictates the length of the cube
 *
 */
#include <VBF_StaticBody.hpp>

/*! typedefs for ugly bullet's datatypes
 *
 */
namespace VBF{
    
    class Static_Cube : public StaticBody{

        private:

            double m_length;

        public:
            Static_Cube(): StaticBody("Default Static Cube", 
                          new btBoxShape(btVector3(10.0, 10.0, 10.0)),
                          btVector3(0.0,0.0, 0.0), 23), 
            m_length(10.0){
                            //empty constructor body
            }

            explicit Static_Cube(double length, btVector3 origin, size_t index);
            
            /*! @brief Preventing copy semantics for Static_Cube construction
             */
            Static_Cube(const Static_Cube&) = delete;


            /*! @brief Destructor
             */
            ~Static_Cube();

            /*! Non-static, constant public member function returning
             * length of the cube
             *
             * @return private member variable m_length (non-modifiable)
             */
            double get_length() const;
            
            virtual std::string get_name() const noexcept override final;
    };
}//end of name space

#endif /* ifndef VBF_STATIC_CUBE_H */

