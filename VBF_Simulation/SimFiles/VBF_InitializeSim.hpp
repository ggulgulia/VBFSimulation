#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <utility>

namespace VBF{
    class InitializeSim{

        private:
            std::string m_filename;
            std::vector<std::pair<std::string,double>> m_parameterList;
            
        public:
            InitializeSim(std::string filename):
                m_filename(filename){
                
                    std::ifstream input_file;
                    try{
                        std::cout << "attempting to open the input file\n";
                        input_file.open(m_filename);
                        if(!input_file.is_open())
                            throw "failed to open the file, please make sure the file exists in the path specified\n";
                        std::string variable_name;
                        double value;
                        int linenum(0);
                        while(getline(input_file, variable_name)){
                            if(variable_name[0] != '/' && variable_name.length() !=1){
                            std::stringstream line(variable_name);
                            std::string data;
                            std::getline(line, data, '=');
                            std::cout <<linenum++ << " "<< data << "\n"; 

                            }
                        }
                    }
                    catch(const char* exception){
                        std::cerr << "Error: " << exception << "\n";
                        std::cerr << "Force aborting program\n";
                        exit(-1);
                    }
                }
    };//end class definition

}//end namespace VBF
