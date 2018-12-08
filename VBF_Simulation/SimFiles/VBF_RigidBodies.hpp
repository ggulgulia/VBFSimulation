#ifndef VBF_RIGID_BODIES_H
#define VBF_RIGID_BODIES_H 

#include <bullet/btBulletDynamicsCommon.h>
#include <string>

typedef btDefaultMotionState MotionState;
typedef btRigidBody::btRigidBodyConstructionInfo btRbConstrInfo;
typedef btCollisionShape VBF_Shape;

namespace VBF{


    class RigidBody{

        private:
            std::string m_name;
            VBF_Shape* m_shape;
            btVector3 m_origin;
            double m_mass;
            btVector3 m_inertia;
            size_t m_index; //might be helpful for book keeping 
                            //when there are many rigid bodies
        protected:
            btRigidBody *m_rbody;

        public:

            //default constructor
            explicit RigidBody();

            //user constructor
            explicit RigidBody(std::string name, VBF_Shape* shape, btVector3 origin,
                               double mass, btVector3 inertia, size_t index);

            btRigidBody* get_rbody();
            virtual std::string get_name();
    };
    class Cube : public RigidBody{

        private:
            double m_length;

        public:

            explicit Cube(double length, btVector3 origin, btVector3 inertia, double mass, size_t index);

            ~Cube();
            virtual std::string get_name();
    };

    class Sphere: public RigidBody{
        
        private:
            double m_radius;

        public:

            explicit Sphere(double radius, btVector3 origin, btVector3 inertia, double mass, size_t index);
            ~Sphere();

            virtual std::string get_name();
    };

}//end of name space

#endif /* ifndef VBF_RIGID_BODIES_H */

