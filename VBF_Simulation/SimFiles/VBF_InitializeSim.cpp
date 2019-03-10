#include "VBF_InitializeSim.hpp"
#include <iostream>

VBF::InitializeSim::InitializeSim(){  }

//user constructor 1
VBF::InitializeSim::InitializeSim(std::string filename):
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
} 

//user constructor2
VBF::InitializeSim::InitializeSim(std::string varName, double varVal){
    m_parameterList->push_back(std::pair<std::string, double>(varName, varVal));
}
            
            
//move constructor
VBF::InitializeSim::InitializeSim(InitializeSim&& init) :
                    m_filename(init.m_filename),
                    m_parameterList(init.m_parameterList){
        std::cout << "Move constructor called in InitializeSim object\n";
        init.m_parameterList = nullptr;
}  
            
VBF::InitializeSim::~InitializeSim(){
    std::cout << "Destructor being called\n";
    m_filename.clear();
    if(m_parameterList){
        m_parameterList->clear();
        delete m_parameterList;
        m_parameterList=nullptr;
    }
 }
            
//this parameter list should be non-mutable once created
const std::vector<std::pair<std::string, double>>* VBF::InitializeSim::get_parameter_list() const{return m_parameterList;}
            
//overloaded operator<<  to print the paramter list
