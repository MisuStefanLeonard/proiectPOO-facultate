#ifndef MENU_H
#define MENU_H
#define START 1

#include <string>
#include <iostream>
#include <time.h>
using std::string;

class Menu{
public:
    string currentDateTime();
    void printMenuFRONT();
    void printMenuHOTEL();
    void printRegisterLoginWindow();
    enum customer{
    ADD_CLIENT = START,
    MODIFY_CIENT,
    SEARCH_CLIENT,
    REMOVE_CLIENT,
    PRINT_CLIENT,
    BOOK_HOTEL_FRONT,
    EXIT_PROGRAM,
    WRONG_OPTION1
    };
    enum mHOTEL{
    BOOK_HOTEL = START,
    SHOW_HOTELS,
    SEARCH_HOTEL,
    GO_BACK,
    WRONG_OPTION2
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
