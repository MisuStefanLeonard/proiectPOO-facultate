#include "LBAAC.h"

    std::unordered_map<string,Customer> LinkBetweenAccountAndCustomer::getMap(){
        return customerMAP;
    }

    void LinkBetweenAccountAndCustomer::ReadFromFileIntoMap(const char* FILENAME , std::unordered_map<string , Customer>& map_of_customers){
        std::ifstream filein(FILENAME);
        if(!filein.is_open()){
            std::cerr << FILENAME << " could not be opened" << std::endl;
        }
        string userName , name , prename , CNP , email;
        char sex;
        int age,money , number;
        bool adult;
        while(filein >> userName >> name >> prename >> age >> sex >> money >> adult >> number >> CNP >> email){

            Customer customertemp;
            customertemp.setID(userName);
            customertemp.setName(name);
            customertemp.setPrename(prename);
            customertemp.setAge(age);
            customertemp.setSex(sex);
            customertemp.setMoney(money);
            customertemp.setAdult(adult);
            customertemp.setNumber(number);
            customertemp.setCNP(CNP);
            customertemp.setEmail(email);
            map_of_customers[userName] = customertemp;

            for (int i = 0; i < 3; ++i){
                std::string temp;
                std::getline(filein, temp);
            }
        }
        filein.close();
    }
    bool LinkBetweenAccountAndCustomer::DataAlreadyEntered(std::unordered_map<string , Customer>& customermap , string currID){
        if(customermap.find(currID) != customermap.end())
            return true;
        return false;
    }

    void LinkBetweenAccountAndCustomer::AddFromMapToCustomerVec(std::unordered_map<string , Customer>& customermap , string currID , std::vector<Customer>& customer){
        auto it = customermap.find(currID);
        Customer temp = it->second;
        customer.push_back(temp);
    }
