#include <fstream>
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
            InitializeSim(){  }

            //user constructor 1
            explicit InitializeSim(std::string filename):
                m_filename(filename){
                    std::ifstream input_file;
                    try{
                        std::cout << "attempting to open the input file\n";
                        input_file.open(m_filename);
                        if(!input_file.is_open())
                            throw "failed to open the file, please make sure the file exists in the path specified\n";
                        std::string varName;
                        double value;
                        int linenum(0);
                        //read after ignoring comment and empty lines
                        while(getline(input_file, varName)){
                            if(varName[0] != '/' && varName.length() !=1){
                            std::stringstream line(varName);
                            std::string data;
                            std::getline(line, data, '=');
                            line >> value;
                            //std::cout <<linenum++ << " "<< data << ": " << value <<"\n"; 
                            ++linenum;
                            std::pair<std::string, double> temp(data, value);
                            m_parameterList->push_back(temp);
                            }
                        }
                        std::cout << "Number of parameters read from " << m_filename << ": "<< linenum << "\n";
                    }
                    catch(const char* exception){
                        std::cerr << "Error: " << exception << "\n";
                        std::cerr << "Force aborting program\n";
                        exit(-1);
                    }
                } //end of user constructor1

            //user constructor2
            explicit InitializeSim(std::string varName, double varVal){
            m_parameterList->push_back(std::pair<std::string, double>(varName, varVal));
            }
            
            //prohibit use of copy constructor and copy assignment operators
            InitializeSim(const InitializeSim&) = delete;
            const InitializeSim& operator=(const InitializeSim&) = delete;
            const InitializeSim& operator=(InitializeSim&) = delete;
            
            //move constructor
            InitializeSim(InitializeSim&& init) :
                m_filename(init.m_filename),
                m_parameterList(init.m_parameterList){
                    std::cout << "Move constructor called in InitializeSim object\n";
                    init.m_parameterList = nullptr;
                }  
            
            ~InitializeSim(){
                std::cout << "Destructor being called\n";
                m_filename.clear();
                if(m_parameterList){
                    m_parameterList->clear();
                    delete m_parameterList;
                    m_parameterList=nullptr;
                }
            }
            
            //this parameter list should be non-mutable once created
            const std::vector<std::pair<std::string, double>>* get_parameter_list() const{return m_parameterList;}
            
            //overloaded operator<<  to print the paramter list
            friend std::ostream& operator<<(std::ostream& out, const InitializeSim& init ){
                const std::vector<std::pair<std::string, double>>::iterator itr;
                int num(0);
                const std::vector<std::pair<std::string, double>> *paramList = init.get_parameter_list() ;

                out << "printing the paramters list that was read from input file: \n";
                //in c++17 : for(const auto& [first, second] : *paramList){ std::cout << first << ":" << second << "\n"; }
                for (const auto pair : *paramList){
                    std::cout << pair.first << ":" << pair.second << "\n";
                } 
            }
    };//end class definition

}//end namespace VBF
