#include <VBF_ReadInputData.hpp>


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
        std::string value;
        int linenum(0);
        while(getline(input_file, varName)){
        //read after ignoring comment and empty lines
            if(varName[0] != '/' && varName.length() !=1){
                std::stringstream line(varName);
                std::string data;
                std::getline(line, data, ' ');
                line >> value;
                ++linenum;

                //check if a string has `+` or `-`
                //symbol charcters
                if(value[0] == '-' || value[0] == '+'){
                    //if the symbols `+` or `-` are present
                    //check that second character is a decimal and third cahracter is a digit
                    //OR
                    //the second character is a digit
                    if((value[1] == '.' && isdigit(value[2])) || isdigit(value[1])){
                        m_numeral_paramList->insert(std::make_pair(data, std::stod(value)));
                    }
                }

                //If all above conditions fail and the first character is a digit
                //the value is assumed to be a double
                else if(isdigit(value[0])){
                m_numeral_paramList->insert(std::make_pair(data, std::stod(value)));
                }
                else
                    m_string_paramList->insert(std::make_pair(data, value));
            }
        }
        std::cout << "Number of parameters read from " << m_filename << ": "<< linenum << "\n";
    }
    catch(const char* exception){
        std::cerr << "Error: " << exception << "\n";
        std::cerr << "Force aborting program\n";
        input_file.close();
        exit(-1);
    }
} 

//user constructor2
VBF::ReadInputData::ReadInputData(std::string varName, double varVal){
    m_numeral_paramList->insert(std::make_pair(varName, varVal));
}
            
            
            
VBF::ReadInputData::~ReadInputData(){
    //std::cout << "Destructor being called\n";
    m_filename.clear();
 }
            
//this parameter list should be non-mutable once created
const std::shared_ptr<numeral_param_type> VBF::ReadInputData::get_parameter_list() const noexcept
{return m_numeral_paramList;}            


double VBF::ReadInputData::get_numeric_value(const std::string&  key) const{
    auto iter = m_numeral_paramList->find(key);
    if(iter != m_numeral_paramList->end()){
        std::cout << "Searched parameter: " << key << " was found in the list\n";

        return iter->second;
    }
    else{
        std::cout << "Searched parameter: " << key << " was NOT found in the list\n";
        throw(std::runtime_error("ERROR: SEARCHED KEY WAS NOT FOUND. PLEASE CHECK THE INPUT FILE"));
        }
}

std::string VBF::ReadInputData::get_string_value(const std::string&  key) const{

    auto iter = m_string_paramList->find(key);
    if(iter != m_string_paramList->end()){
        std::cout << "Searched parameter: " << key << " was found in the list\n";

        return iter->second;
    }
    else{
        std::cout << "Searched parameter: " << key << " was NOT found in the list\n";
        throw(std::runtime_error("ERROR: SEARCHED KEY WAS NOT FOUND. PLEASE CHECK THE INPUT FILE"));
        }
}
