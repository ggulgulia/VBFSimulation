#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <utility>

namespace VBF{
    class InitializeSim{

        private:
            std::string m_filename;
            std::vector<std::pair<std::string,double>> *m_parameterList = new std::vector<std::pair<std::string, double>>(0);
             
        public:
            //default constructor
            InitializeSim();

            //user constructor 1
            explicit InitializeSim(std::string filename);

            //user constructor2
            explicit InitializeSim(std::string varName, double varVal);
            
            //move constructor
            InitializeSim(InitializeSim&& init);

            //destructor
            ~InitializeSim();

            //prohibit use of copy constructor and copy assignment operators
            InitializeSim(const InitializeSim&) = delete;
            const InitializeSim& operator=(const InitializeSim&) = delete;
            const InitializeSim& operator=(InitializeSim&) = delete;
            
            //this parameter list should be non-mutable once created
            const std::vector<std::pair<std::string, double>>* get_parameter_list() const;
            //overloaded operator<<  to print the paramter list
            friend std::ostream& operator<<(std::ostream& out, const InitializeSim& init ){
    const std::vector<std::pair<std::string, double>>::iterator itr;
    const std::vector<std::pair<std::string, double>> *paramList = init.get_parameter_list() ;

    out << "printing the paramters list that was read from input file: \n";
    //in c++17 : for(const auto& [first, second] : *paramList){ std::cout << first << ":" << second << "\n"; }
    for (const auto pair : *paramList){
        std::cout << pair.first << ":" << pair.second << "\n";
    } 

    return out;
}
    };//end class definition

}//end namespace VBF
