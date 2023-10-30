#include "city.h"
#include "hotel.h"
#include "menu.h"
#include "account.h"
#include "LBAAC.h"
#include "menuloops.h"
#include "switch.h"

int main()
{
    std::vector<Hotel> hotel;
    Hotel temp;
    temp.ReadFromFile("hotels.txt" , hotel);
    std::unordered_map<string , City> cities;
    City c_ity;
    c_ity.ReadFromFile_map("cities.txt" , cities);
    std::vector<Customer> customer;
    bool EXIT_PROG = true , EXIT_LOGIN_REGISTER_MENU = true;
    string currID;
    Menu m;
    SWITCH sw;
    AccountDataBase accDB;
    LinkBetweenAccountAndCustomer LBAAC;
    MENU_LOOPS menuLoops;
    std::unordered_map<string , Customer> customerMap = LBAAC.getMap();
    accDB.ReadingFromRecordsIntoPassMap("records.txt");
    menuLoops.LOGIN_LOOP(m , accDB , LBAAC , EXIT_LOGIN_REGISTER_MENU , EXIT_PROG , "records.txt" , "LOGINinfo.txt" ,currID);
    LBAAC.ReadFromFileIntoMap("userinfo.txt" , customerMap);
    menuLoops.CustomerAndHotel_MENU(m , sw , LBAAC , EXIT_PROG , currID , customerMap , customer , hotel , cities , "userinfo.txt");
    return 0;
}

