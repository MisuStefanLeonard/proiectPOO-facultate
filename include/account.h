#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <string>
using std::string;

class Account{
private:
    string Id;
    string Pass;
public:
    void setId(string id);
    string getId();
    void setPass(string pass);
    string getPass();
};

#endif
