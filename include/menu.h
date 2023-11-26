#ifndef MENU_H
#define MENU_H
#define START 1

#include <string>
#include <iostream>
#include <ctime>
#include <thread>
#include <chrono>
#include "indicators-master/single_include/indicators/indicators.hpp"
using std::string;

class Menu{
public:
    static string currentDateTime();
    void printMenuFRONT();
    void printMenuHOTEL();
    void printRegisterLoginWindow();
    void SpinnerInTerminal(bool isAuthenticated);
    void ProgressBarExit();
    void ProgramReadyBar();
    enum customer{
    ADD_CLIENT = START,
    MODIFY_ClIENT,
    SEARCH_CLIENT,
    REMOVE_CLIENT,
    PRINT_CLIENT,
    BOOK_HOTEL_FRONT,
    LOG_OUT,
    EXIT_PROGRAM,
    };
    enum mHOTEL{
    BOOK_HOTEL = START,
    SHOW_HOTELS,
    SEARCH_HOTEL,
    LEAVE_RECENSION,
    GO_BACK
    };
    enum Pay{
    ONLY_CARD = START,
    CARD_AND_CASH
    };
    enum RegisterLoginWindow{
        REGISTER = START,
        LOGIN,
        FORGOT_PASS,
        EXIT_PROG_REG_LOG_WIND
    };
};

#endif
