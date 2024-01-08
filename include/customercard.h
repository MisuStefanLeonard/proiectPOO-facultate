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


class CustomerCard{
private:
    string Name;
    string CardNumber;
    string Expiration_Date;
    string CVV;
    int Money;
public:
    virtual ~CustomerCard() = default;
    string cardGetName();
    string cardGetCardNumber();
    string cardGetExpirationDate();
    string cardGetCVV();
    int getCardMoney();
    friend std::istream& operator>>(std::istream& is , CustomerCard& cardOb);
    bool isValidExpirationDate();
    void setName(const std::string& name);
    void setCardNumer(const std::string& cardNumber);
    void setCvv(const std::string& cvv);
    void setExpirationDate(const std::string& expdate);
    void setMoney(int money);
};

#endif