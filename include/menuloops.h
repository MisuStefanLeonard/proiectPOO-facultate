#ifndef MENULOOPS_H
#define MENULOOPS_H

#include "city.h"
#include "hotel.h"
#include "account.h"
#include "accountdatabase.h"
#include "LBAAC.h"
#include "switch.h"
#include "customercard.h"
class MENU_LOOPS{
public:
    void LOGIN_LOOP(Menu m , AccountDataBase accDB , LinkBetweenAccountAndCustomer& LBAAC , bool& EXIT_LOGIN_REGISTER_MENU ,bool& EXIT_PROG , const char* FILENAME , const char* FILENAME2 , string& currID);
    void CustomerAndHotel_MENU(Menu m , SWITCH sw , LinkBetweenAccountAndCustomer& LBAAC , bool EXIT_PROG ,string currID , std::unordered_map<string,Customer>& customerMap , std::vector<Customer>& customer ,std::vector<Hotel>& hotel ,std::unordered_map<string , City> cities  , const char* FILENAME);
};


#endif
