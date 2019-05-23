#ifndef VBF_STATIC_BODY_H
#define VBF_STATIC_BODY_H 

#include "VBF_RigidBodies.hpp"

namespace VBF{

    class StaticBody : public RigidBody{

        private:

        public:

            //default constructor
            //note right now call to this constructor
            //creates hanging pointers, either resolve this
            //or don't permit call to empty constructor
            explicit StaticBody();
            //user constructor
            explicit StaticBody(const std::string& name, CollShape* shape, btVector3 origin,
                               size_t index=0);
            
            //prevent implicit copy Constructor
            StaticBody(const StaticBody& vbf_rb) = delete;
            
            //destructor
            virtual ~StaticBody();
            
            //helper functions
            //virtual void setName(const std::string& name) override;
            virtual btVector3 get_position();
            virtual double get_mass() const; 
            virtual btVector3 get_inertia() const;
    };
}//end of name space

#endif /* ifndef VBF_STATIC_BODY_H */

