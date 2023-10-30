#ifndef CUSTOMERCARD_H
#define CUSTOMERCARD_H


#include "InputOutputFunctions.h"
#include <iostream>
#include <unordered_map>
#include <fstream>
#include <string>
#include <regex>
#include <thread>
using std::string;
using std::regex;


class CustomerCard:public InputOutputFunctions<CustomerCard>{
private:
    string Name;
    string CardNumber;
    string Expiration_Date;
    string CVV;
    int Money;
public:
    void cardSetName(string name);
    string cardGetName();
    void cardSetCardNumver(string cardnumber);
    string cardGetCardNumber();
    void cardSetExpirationDate(string exp_date);
    string cardGetExpirationDate();
    void cardSetCVV(string cvv);
    string cardGetCVV();
    void setCardMoney(int money);
    int getCardMoney();
    void Read() override;
    bool isValidExpirationDate();
    void ReadFromFile_map(const char *FILENAME , std::unordered_map<string , CustomerCard> & map) override;
    void ReadFromFile(const char* FILENAME , std::vector <CustomerCard>& card_customer) override;
    void Print() override;
};

#endif