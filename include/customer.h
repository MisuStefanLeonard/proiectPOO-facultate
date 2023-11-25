#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "InputOutputFunctions.h"
#include <string>
#include <vector>
#include <iostream>
#include <regex>
#include <memory>
using std::string;
using std::regex;
class Customer{
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
protected:
    string ID;
  
public:
    Customer() = default;
    ~Customer() = default;
    void setID(const string& id);
    string getID();
    void setName(const string& name);
    string getName();
    void setPrename(const string& prename);
    string getPrename();
    void setAge(int age);
    int getAge() const;
    void setSex(char sex);
    char getSex() const;
    void setMoney(int money);
    int getMoney() const;
    void setAdult(bool adult);
    bool getAdult() const;
    void setNumber(int number);
    std::vector<int> getNumber();
    void setCNP(const string& cnp);
    string getCNP();
    void setEmail(const string& email);
    string getEmail();
    bool checkName() const;
    bool checkPrename() const;
    bool checkAge() const;
    bool checkAdult() const;
    bool checkMoney() const;
    bool checkCNP() const;
    bool checkEmailAddres();
    friend std::ostream& operator<<(std::ostream& os , Customer& customer);
    friend std::istream& operator>>(std::istream& is , Customer& customer);
    string searchClientbyName() const;
    string searchClientbyCNP() const;
};

#endif
