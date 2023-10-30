#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "InputOutputFunctions.h"
#include <string>
#include <vector>
#include <iostream>
#include <regex>
using std::string;
using std::regex;
class Customer:public InputOutputFunctions<Customer>{
private:
    string Name;
    string Prename;
    int Age;
    char Sex;
    int Money;
    bool Adult;
    std::vector<int> Number;
    string CNP;
    string Email;
    string ID;
  
public:
    void setID(string id);
    string getID();
    void setName(string name);
    string getName();
    void setPrename(string prename);
    string getPrename();
    void setAge(int age);
    int getAge();
    void setSex(char sex);
    char getSex();
    void setMoney(int money);
    int getMoney();
    void setAdult(bool adult);
    bool getAdult();
    void setNumber(int number);
    std::vector<int> getNumber();
    void setCNP(string cnp);
    string getCNP();
    void setEmail(string email);
    string getEmail();
    bool checkName();
    bool checkPrename();
    bool checkAge();
    bool checkAdult();
    bool checkMoney();
    bool checkCNP();
    bool checkEmailAddres();
    void Read() override;
    void Print() override;
    string searchClientbyName();
    string searchClientbyCNP();
    void ReadFromFile(const char*FILENAME , std::vector<Customer>& customer) override;
    void ReadFromFile_map(const char* FILENAME , std::unordered_map<string , Customer> & customer) override;
};

#endif
