#ifndef ACCOUNTDATABASE_H
#define ACCOUNTDATABASE_H
#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>
#include <vector>
#include <regex>
#include <thread>
#include "account.h"
#include "menu.h"
#include "../include/digestpp/digestpp.hpp"
#include "../include/digestpp/hasher.hpp"
using std::string;
using std::regex;


class AccountDataBase{
private:
    std::unordered_map<string , string> pass_map;
public:
    std::unordered_map<string,string> getPass_Map();
    void ReadingFromRecordsIntoPassMap(const char* FILENAME);
    int Register(const char* FILENAME);
    int ReadFromFileInVector(const char *FILENAME , std::vector<Account> & acc_vec);
    void ReplacingPasswordInVec(std::vector<Account> & acc_vec , std::unordered_map<string,string>::iterator it);
    int WritingVecBackToFile(const char* FILENAME , std::vector<Account> & acc);
    void Free_vec(std::vector<Account>& acc_vec);
    int ForgotPassword(const char* FILENAME);
    int Login(const char* FILENAME , string& p_curr_id);
    string SHA256(const string& input);
};


#endif
