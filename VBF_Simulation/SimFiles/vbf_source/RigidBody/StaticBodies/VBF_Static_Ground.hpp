#ifndef VBF_STATIC_GROUND_H
#define VBF_STATIC_GROUND_H 

/*! @brief Class file for VBF::StaticCube
 *
 * @details This class encapsulates the bullet's data structure for a Cube but ensures that
 * all the cube object generated through this calss object are static rigid body. This class
 * has only one private member that dictates the length of the cube
 *
 */
#include <VBF_StaticBody.hpp>
#include <bullet/BulletCollision/CollisionShapes/btStaticPlaneShape.h>

/*! typedefs for ugly bullet's datatypes
 *
 */
namespace VBF{
    
    class Static_Ground : public StaticBody{

        private:

            btVector3 m_normal;
            float m_position;

        public:
            Static_Ground(): StaticBody("Default Static Ground", 
                             new btStaticPlaneShape(btVector3(0.0, 1.0, 0.0), 0.0),
                             btVector3(0.0, 0.0, 0.0), 0.004, 24), 
                             m_normal(btVector3(0.0, 1.0, 0.0)),m_position(0.0){
                            //empty constructor body
            }

            explicit Static_Ground(btVector3& normal, double position, btVector3& origin, 
                                  const double collMarg, size_t index);
            
            /*! @brief Preventing copy semantics for Static_Ground construction
             */
            Static_Ground(const Static_Ground&) = delete;


            /*! @brief Destructor
             */
            ~Static_Ground();

            /*! Non-static, constant public member function returning
             * length of the cube
             *
             * @return private member variable m_length (non-modifiable)
             */
            btVector3 get_normal() const noexcept;
            float get_position() const noexcept;
            
            virtual std::string get_name() const noexcept override final;
    };
}//end of name space

#endif /* ifndef VBF_STATIC_GROUND_H */

