#include "menu.h"

    string Menu::currentDateTime(){
        time_t     now = time(0);
        struct tm  tstruct;
        char       buf[80];
        tstruct = *localtime(&now);
        strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
        return buf;
        //2023-07-16.16:02:46 
    }
    void Menu::printMenuFRONT(){
        std::cout << currentDateTime() << std::endl;
        std::cout << "WELCOME TO OUR BOOKING SYSTEM\t\t\t" << std::endl;
        std::cout << "1.---Add customer data---" << std::endl;
        std::cout << "2.---Modify customer data---" << std::endl;
        std::cout << "3.---Search customer---" << std::endl;
        std::cout << "4.---Remove customer data---" << std::endl;
        std::cout << "5.---Print customer data---" << std::endl;
        std::cout << "6.---Book a hotel(next page)---" << std::endl;
        std::cout << "7.---Exit program---" << std::endl;
    }
    void Menu::printMenuHOTEL(){
        std::cout << currentDateTime() << std::endl;
        std::cout << "WELCOME TO OUR BOOKING SYSTEM\t\t\t" << std::endl;
        std::cout << "1.---Book a hotel---" << std::endl;
        std::cout << "2.---Show all hotels---" << std::endl;
        std::cout << "3.---Search hotel---" << std::endl;
        std::cout << "4.---go back---" << std::endl;
    }
    void Menu::printRegisterLoginWindow(){
        std::cout << currentDateTime() << std::endl;
        std::cout << "WELCOME TO OUR BOOKING SYSTEM\t\t\t" << std::endl;
        std::cout << "1.---Register---" << std::endl;
        std::cout << "2.---Login---" << std::endl;
        std::cout << "3.---Forgot password---" << std::endl;
        std::cout << "4.---EXIT---" << std::endl;
    }
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
