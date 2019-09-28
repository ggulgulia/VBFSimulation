#ifndef READ_INPUT_DATA_H
#define READ_INPUT_DATA_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <utility>
#include <unordered_map>
#include <memory>
#include <cctype>
#include <exception>

/*! The purpose of of VBF::ReadInputData is to initialize VBF Simulation by reading the input file, which will contain several
 * simulation input, run time and output parameters. 
 *
 * Currently this class in not complete as the VBF::Simulation itself is under progress and the full extent of parameters
 * on which VBF Simulation will depend is not determined.
 *
 * @warning The class assumes that the parameter has a name and a value of type double. This is not true and change it by using correct 
 * implementation.
 *
 * TODO: Complete implementation as the simulation development progresses. 
 * @todo Change the private member variable from a pointer to a non-pointer object since std::vector guarantees heap memory allocation.
 */

typedef std::unordered_map<std::string, double> numeral_param_type;
typedef std::unordered_map<std::string, std::string> string_param_type;
namespace VBF{
    class ReadInputData{

        private:
            std::string m_filename; /*!< Input file name */
            std::shared_ptr<numeral_param_type> m_numeral_paramList = std::make_shared<numeral_param_type>(); /*!< container that stores a parameter name and a corresponding numeric value */
            std::shared_ptr<string_param_type> m_string_paramList = std::make_shared<string_param_type>(); /*!< container that stores parameter name and  corresponding string value */
             
        public:
            /*! @brief Default constructor
             * @Details Currently the default constuctor doesn't do
             * anything. 
             *
             * @todo Define proper impelementation. If in future it 
             * seems useless, delete the default constructor.
             */
            ReadInputData() = default;

            /*! @brief User constructor 1
             *
             * @details Creates a VBF::IniitalizeSim object by reading
             * the input file. The body of the constructor reads line
             * by line each parameter name and its value and stores it
             * in the memeber variable m_numeral_paramList
             * @param filename : string that determines path to input
             * file.
             */
            explicit ReadInputData(std::string filename);

            /*! @brief user constructor2
             *
             * @details This constructor allows user to create a 
             * VBF::ReadInputData object by passing a parameter name 
             * and a parameter value. Later if more parameters is 
             * desired to be added to the object, the public member 
             * method VBF::ReadInputData::add_parameter method could 
             * be used.
             * @todo Implement add_parameter method for this class.
             *
             * @param varName  : string name of parameter.
             * @param varVal   : value of parameter.  
             *
             * @warning The method assumes that the parameter value 
             * is double. In reality this is not true.
             * @todo Correct the second parameter type to accept any
             * type. 
             */
            explicit ReadInputData(std::string varName, double varVal);
            
            //move constructor
            //ReadInputData(InitializeSim&& init);

            /*! @brief Destructor
             * @details The destructor clears the contents of variable
             * m_numeral_paramList and releases any memory held by it.
             */
            ~ReadInputData();

            /*! @brief Deleted copy constructor to prevent copy 
             * semantics.
             */
            ReadInputData(const ReadInputData&) = delete;

            /*! @brief Deleted copy assignment operator
             */
            const ReadInputData& operator=(const ReadInputData&) = delete;
            
            /*! @brief This method gives read only access to 
             * parameter list.
             *
             * @details User has to ensure that the parameters for 
             * simulation is correct before the simulation begins 
             * otherwise entire simulation data can be corrupted. In
             * the case of a worng parameter for VBF simulation, the 
             * simulation has to be restarted. This is the rationale
             * behind providing read only access to parameter list.
             */
            const std::shared_ptr<numeral_param_type> get_parameter_list() const noexcept;


            /*! @brief Method passes a reference to std::ostream
             * so that parameterlist encapsulated within 'this' object
             * could be printed on the screen (or on a file)
             */
            friend std::ostream& operator<<(std::ostream& out, const ReadInputData& init ){

                std::shared_ptr<numeral_param_type> paramList = init.m_numeral_paramList;
                std::shared_ptr<string_param_type> paramList2 = init.m_string_paramList;

                out << "printing the paramters list that was read from input file: \n";
                //in c++17 : for(const auto& [first, second] : *paramList){ std::cout << first << ":" << second << "\n"; }
                for(const auto& [first, second] : *paramList){
                    std::cout << first << ":" << second << "\n";
                } 

                for(const auto& [first, second] : *paramList2){
                    std::cout << first << ":" << second << "\n";
                } 

                return out;
             }

        /*! @brief Returns the numerical value of the parameter
         *
         *  @details Public method that retruns the encapsulated
         *  numerical value of the passed key. The user has to
         *  ensure that the value held in the key exists and is a
         *  a numerical value
         *
         *  @param key : std::string name of parameter
         *  for which the numerical value is sought
         *
         *  @returns double numerical value of the key 
         *  if it exists else the method throws to inform 
         *  the user that the parameter doesn't exist
         *  and it should be added to the input file
         */
        double get_numeric_value(const std::string&  key) const ;
        /*! @brief Returns the string value of the parameter
         * for e.g. : file path for  CAD data
         *
         *  @details Public method that retruns the encapsulated
         *  numerical value of the passed key. The user has to
         *  ensure that the value held in the key exists and is a
         *  a numerical value
         *
         *  @param key : std::string name of parameter
         *  for which the string value is sought
         *
         *  @returns std::string value of the key 
         *  if it exists else the method throws to inform 
         *  the user that the parameter doesn't exist
         *  and it should be added to the input file
         */
        std::string get_string_value(const std::string&  key)const ;

    };//end class definition

}//end namespace VBF

#endif
