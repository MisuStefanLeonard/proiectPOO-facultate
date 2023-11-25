#include "include/city.h"
#include "include/hotel.h"
#include "include/menu.h"
#include "include/account.h"
#include "include/LBAAC.h"
#include "include/menuloops.h"

int main()
{
    Menu m;
    std::vector<Hotel> hotel;
    Hotel temp;
    std::vector<Customer> customer;
    temp.ReadFromFile("hotels.txt" , hotel);
    std::unordered_map<string , City> cities;
    City c_ity;
    c_ity.ReadFromFile_map("cities.txt" , cities);
    bool EXIT_PROG = true , EXIT_LOGIN_REGISTER_MENU = true;
    string currID;
    AccountDataBase accDB;
    LinkBetweenAccountAndCustomer LBAAC;
    MENU_LOOPS menuLoops;
    std::unordered_map<string , Customer> customerMap = LBAAC.getMap();
    accDB.ReadingFromRecordsIntoPassMap("records.txt");
    m.ProgramReadyBar();
    menuLoops.LOGIN_LOOP(m , accDB , LBAAC , EXIT_LOGIN_REGISTER_MENU , EXIT_PROG , "records.txt" , "LOGINinfo.txt" ,currID);
    LBAAC.ReadFromFileIntoMap("userinfo.txt" , customerMap);
    menuLoops.CustomerAndHotel_MENU(accDB,m , LBAAC , EXIT_PROG , currID , customerMap , customer , hotel , cities , "userinfo.txt" , "reviews.txt");

    return 0;
}

