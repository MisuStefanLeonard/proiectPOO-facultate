#ifndef INPUTOUTPUTFUNCTIONS_H
#define INPUTOUTPUTFUNCTIONS_H

#include <vector>
#include <unordered_map>
#include <string>

template <class T>
class InputOutputFunctions
{
public:
    virtual void ReadFromFile(const char *FILENAME, std::vector<T> &t) = 0;
    virtual void ReadFromFile_map(const char *FILENAME, std::unordered_map<std::string, T> &t) = 0;
};

#endif // INPUTOUTPUTFUNCTIONS_H
