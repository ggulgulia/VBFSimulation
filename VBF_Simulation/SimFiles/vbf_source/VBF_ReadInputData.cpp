#include <VBF_InitializeSim.hpp>

VBF::ReadInputData::ReadInputData(){  }

//user constructor 1
VBF::ReadInputData::ReadInputData(std::string filename):
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
        while(getline(input_file, varName)){
        //read after ignoring comment and empty lines
            if(varName[0] != '/' && varName.length() !=1){
                std::stringstream line(varName);
                std::string data;
                std::getline(line, data, ' ');
                line >> value;
                //std::cout <<linenum++ << " "<< data << ": " << value <<"\n"; 
                ++linenum;
                //std::pair<std::string, double> temp(data, value);
                m_parameterList->insert(std::make_pair(data, value));
                //(*m_parameterList)[data] = value;
                //m_parameterList->push_back(temp);
            }
        }
        std::cout << "Number of parameters read from " << m_filename << ": "<< linenum << "\n";
    }
    catch(const char* exception){
        std::cerr << "Error: " << exception << "\n";
        std::cerr << "Force aborting program\n";
        exit(-1);
    }
} 

//user constructor2
VBF::ReadInputData::ReadInputData(std::string varName, double varVal){
    m_parameterList->insert(std::make_pair(varName, varVal));
}
            
            
            
VBF::ReadInputData::~ReadInputData(){
    //std::cout << "Destructor being called\n";
    m_filename.clear();
    if(m_parameterList){
        m_parameterList->clear();
        delete m_parameterList;
        m_parameterList=nullptr;
    }
 }
            
//this parameter list should be non-mutable once created
const std::unordered_map<std::string, double>* VBF::ReadInputData::get_parameter_list() const{return m_parameterList;}            


double VBF::ReadInputData::operator[](const std::string&  s){
    auto iter = m_parameterList->find(s);
    if(iter != m_parameterList->end()){
        std::cout << "Searched parameter: " << s << " was found in the list\n";

        return iter->second;
    }
    else{
        std::cout << "Searched parameter: " << s << " was NOT found in the list\n";
        std::cout << "returning a stub value\n";
        return 0.0;
        }
}

