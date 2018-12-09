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
            btRigidBody *m_rbody;

        public:

            //default constructor
            explicit RigidBody();

            //user constructor
            explicit RigidBody(std::string name, VBF_Shape* shape, btVector3 origin,
                               double mass, btVector3 inertia, size_t index);
            
            //copy Constructor
            RigidBody(const RigidBody& vbf_rb):
            m_name(vbf_rb.get_name()),
            m_shape(vbf_rb.get_shape()),
            m_origin(vbf_rb.get_origin()), 
            m_mass(vbf_rb.get_mass()),
            m_inertia(vbf_rb.get_inertia()), 
            m_index(vbf_rb.get_index()+1),
            m_rbody(vbf_rb.get_rbody())
            { //empty copy constructor body
             }
            
            //constructor that simply creates a copy of RigidBody 
            //by transforming its position (and orientation)   
            RigidBody(const RigidBody& rbody, btVector3 origin):
            RigidBody(rbody) //call the copy constructor
            {
                m_origin = origin; //
                btTransform shapeTransform;
                shapeTransform.setIdentity();
                shapeTransform.setOrigin(m_origin);
                MotionState *motionState = new MotionState(shapeTransform);
                btRbConstrInfo rbinfo(m_mass, motionState, m_shape, m_inertia);
                m_rbody = new btRigidBody(rbinfo);
            }
            

            virtual btRigidBody* get_rbody() const;
            virtual std::string get_name()   const;
            virtual VBF_Shape* get_shape()   const { return m_shape;  } 
            virtual btVector3 get_origin()   const { return m_origin; }
            virtual double get_mass()        const { return m_mass;   }
            virtual btVector3 get_inertia()  const { return m_inertia;}
            virtual size_t get_index()       const { return m_index;  }
    };
    
    class Cube : public RigidBody{

        private:
            double m_length;

        public:

            explicit Cube(double length, btVector3 origin, btVector3 inertia, double mass, size_t index);
            
            Cube(const Cube& cube, btVector3 origin):
                       m_length(get_length()),
                       RigidBody(cube, origin)
           { }

            ~Cube();
            virtual std::string get_name();
            double get_length() const { return m_length;}
    };

    class Sphere: public RigidBody{
        
        private:
            double m_radius;

        public:

            explicit Sphere(double radius, btVector3 origin, btVector3 inertia, double mass, size_t index);
            
            Sphere(const Sphere& sphere, btVector3 origin):
                    m_radius(get_radius()),
                    RigidBody(sphere, origin)
            { }
             
            ~Sphere();

            virtual std::string get_name();
            double get_radius() const { return m_radius;}
    };

}//end of name space

#endif /* ifndef VBF_RIGID_BODIES_H */

