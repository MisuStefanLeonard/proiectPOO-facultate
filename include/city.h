#ifndef CITY_H
#define CITY_H

#include "InputOutputFunctions.h"
#include <string>
#include <iostream>
#include <fstream>
using std::string;

class City:public InputOutputFunctions<City>{
private:
    string Name;
public:
    void setName(const string& name);
    string getName();
    void ReadFromFile_map(const char* FILENAME , std::unordered_map<string , City>& cities) override ;
    void ReadFromFile(const char* FILENAME , std::vector<City>& cities) override;
};


#endif
