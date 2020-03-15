
#ifndef SIMLOOP_H
#define SIMLOOP_H 

#include <VBF_World.hpp>
#include <VBF_CommonPhysics.hpp>
#include <memory>

namespace VBF{

    class SimLoop{
    
        private:
            double m_time; //!< stores the time elapsed since simulation loop began 
            size_t m_numSteps;

//            std::shared_ptr<CommonPhysics> m_physics;
        public:
            /*! @brief Returns the time elapsed since sim loop began
             * @details Non-static public member function that returns the value stored
             * in private member m_time
             */

            SimLoop():m_time{0.0}, m_numSteps{0}
            {
                //empty constructor body
            }
            double get_curr_time() const{
                return m_time;
            }


            size_t get_num_steps()const {

                return m_numSteps;
            }

            /*! @brief Steps (once) the simulation through a time 
             * deltaT
             */
            void step(double const deltaT){
                
                m_time +=deltaT;
                ++m_numSteps;
  //              m_physics->step_simulation(deltaT);
            }
        
    };
}

#endif //SIMLOOP_H
