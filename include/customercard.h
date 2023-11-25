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
};

#endif