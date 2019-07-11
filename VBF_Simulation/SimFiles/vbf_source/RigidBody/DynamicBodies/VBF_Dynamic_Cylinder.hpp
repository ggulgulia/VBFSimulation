#ifndef DYNAMIC_CYLINDER_H
#define DYNAMIC_CYLINDER_H 

#include <VBF_DynamicBody.hpp>


namespace VBF{

    
    class Dynamic_Cylinder : public DynamicBody{

        private:
            double m_length;

        public:
            
            //user constructor
            explicit Dynamic_Cylinder(double length, btVector3 origin, 
                                  double mass, 
                                  double linFriction=0.5, double rollingFriction=0.5, 
                                  double restitution=0.2, double linDamping=0.0, 
                                  double angularDamping=0.0, size_t index=221);

            //below two lines prevent expensive copy semantics
            Dynamic_Cylinder(const Dynamic_Cylinder&) = delete;
            Dynamic_Cylinder& operator=(Dynamic_Cylinder&) = delete;

            //Destructor
            ~Dynamic_Cylinder();
            virtual std::string get_name() const noexcept override final;

    };
}//end of name space

#endif /* ifndef DYNAMIC_CUBE_H */

