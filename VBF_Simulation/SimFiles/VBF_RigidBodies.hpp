#ifndef VBF_RIGID_BODIES_H
#define VBF_RIGID_BODIES_H 

#include <bullet/btBulletDynamicsCommon.h>

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
                               double mass, btVector3 inertia, size_t index):
                m_name(name), m_shape(shape), m_origin(origin), m_mass(mass),
                m_inertia(inertia), m_index(index)
                {
                    m_shape->calculateLocalInertia(m_mass, m_inertia);
                    btTransform shapeTransform;
                    MotionState *motionState;
                    shapeTransform.setIdentity();
                    shapeTransform.setOrigin(m_origin);
                    motionState = new MotionState(shapeTransform);
                    
                    btRbConstrInfo rbinfo(m_mass, motionState, m_shape, m_inertia);
                    m_rbody = new btRigidBody(rbinfo);
                }

            btRigidBody* get_rbody(){ return m_rbody; }
    };

    class Cube : public RigidBody{

        private:
            double m_length;

        public:

            explicit Cube(double length, btVector3 origin, btVector3 inertia, double mass, size_t index)
                :m_length(length), RigidBody(std::string("Cube"),
                                            (new btBoxShape(btVector3(length, length, length))),
                                            origin, mass, inertia, index)
                {
                    //empty constructor body
                }
    };

    class Sphere: public RigidBody{
        
        private:
            double m_radius;

        public:

            explicit Sphere(double radius, btVector3 origin, btVector3 inertia, double mass, size_t index)
                :m_radius(radius), RigidBody(std::string("Sphere"),
                                            (new btSphereShape(radius)),
                                            origin, mass, inertia, index)
                {
                    //empty constructor body
                }
    };

}//end of name space

#endif /* ifndef VBF_RIGID_BODIES_H */

