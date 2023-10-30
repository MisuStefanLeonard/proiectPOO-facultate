#ifndef LBAAC_H
#define LBAAC_H

#include <fstream>
#include <iostream>
#include <unordered_map>
#include "customer.h"
using std::string;

class LinkBetweenAccountAndCustomer{
private:
    std::unordered_map<string , Customer> customerMAP;
public:
    std::unordered_map<string,Customer> getMap();
    void ReadFromFileIntoMap(const char* FILENAME , std::unordered_map<string , Customer>& map_of_customers);
    bool DataAlreadyEntered(std::unordered_map<string , Customer>& customermap , string currID);
    void AddFromMapToCustomerVec(std::unordered_map<string , Customer>& customermap , string currID , std::vector<Customer>& customer);
};

#endif