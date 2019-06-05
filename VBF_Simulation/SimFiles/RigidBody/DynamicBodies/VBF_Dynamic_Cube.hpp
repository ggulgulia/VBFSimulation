#ifndef DYNAMIC_CUBE_H
#define DYNAMIC_CUBE_H 

#include <VBF_DynamicBody.hpp>

typedef btDefaultMotionState MotionState;
typedef btRigidBody::btRigidBodyConstructionInfo btRbConstrInfo;
typedef btCollisionShape CollShape;

namespace VBF{

    
    class Dynamic_Cube : public DynamicBody{

        private:
            double m_length;

        public:
            
            //user constructor
            explicit Dynamic_Cube(double length, btVector3 origin, 
                                  double mass, 
                                  double linFriction=0.5, double rollingFriction=0.5, 
                                  double restitution=0.2, double linDamping=0.0, 
                                  double angularDamping=0.0, size_t index=221);

            //below two lines prevent expensive copy semantics
            Dynamic_Cube(const Dynamic_Cube&) = delete;
            Dynamic_Cube& operator=(Dynamic_Cube&) = delete;

            //Destructor
            ~Dynamic_Cube();
            virtual std::string get_name() const override final;

    };
}//end of name space

#endif /* ifndef DYNAMIC_CUBE_H */

