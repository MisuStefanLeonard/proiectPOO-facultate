#include "city.h"

    void City::setName(const string& name){
        Name = name;
    }
    string City::getName(){
        return Name;
    }
    void City::ReadFromFile_map(const char* FILENAME , std::unordered_map<string , City>& cities){
        std::ifstream filein_cities;
        string name;
        filein_cities.open(FILENAME);
        if(filein_cities.is_open() == 0){
            std::cerr << "File could not be opened" << std::endl;
        }
        while(filein_cities >> name){
            City temp;
            temp.setName(name);
            cities[name] = temp;
        }
        filein_cities.close();
    }
    void City::ReadFromFile(const char *FILENAME, std::vector<City> &cities) {
    std::cout << "Not implemented" << std::endl;
    }

