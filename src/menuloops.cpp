#include "menuloops.h"

                                                    // LOGIN MENU ---- START
                                                    // --------------------
    void MENU_LOOPS::LOGIN_LOOP(Menu m , AccountDataBase accDB , LinkBetweenAccountAndCustomer& LBAAC , bool& EXIT_LOGIN_REGISTER_MENU ,bool& EXIT_PROG , const char* FILENAME , const char* FILENAME2 , string& currID){
        int option_number;
        while(EXIT_LOGIN_REGISTER_MENU == true){
            m.printRegisterLoginWindow();
            std::cout << "Enter the option: ";
            std::cin >> option_number;
            switch(option_number){
                case m.REGISTER:
                {
                    int ret = accDB.Register("records.txt");
                    if(ret == 1)
                        break;
                    break;
                }
                case m.LOGIN:
                {
                    int try_count = 0;
                    int ret2 = accDB.Login("LOGINinfo.txt" , &currID);
                    if(ret2 == 0){
                    EXIT_LOGIN_REGISTER_MENU = false;
                    EXIT_PROG = false;
                    }
                    if(ret2 == 1){
                        EXIT_LOGIN_REGISTER_MENU = false;
                    }
                    break;
                }
                case m.FORGOT_PASS:
                {
                    int ret3 = accDB.ForgotPassword("records.txt");
                    if(ret3 == 0)
                        break;
                    break;
                }
                case m.EXIT_PROG_REG_LOG_WIND:
                {
                    EXIT_LOGIN_REGISTER_MENU = false;
                    EXIT_PROG = false;
                    break;
                }
                default:
                    break;
            }
        }
    
    }
                                                                        
                                                           // LOGIN MENU ---- END
                                                           // ------------------

                                                        // CUSTOMER/HOTEL MENU ------ START
                                                        // -----------------------------
    void MENU_LOOPS::CustomerAndHotel_MENU(Menu m , SWITCH sw , LinkBetweenAccountAndCustomer& LBAAC , bool EXIT_PROG ,string currID , std::unordered_map<string,Customer>& customerMap , std::vector<Customer>& customer ,std::vector<Hotel>& hotel ,std::unordered_map<string , City> cities  , const char* FILENAME){
        int option_number_2;
        while(EXIT_PROG == true)
        {
            SWITCH sw;
            std::cout << "You are logged as " << currID << std::endl;
            std::cout << "----------------------------" << std::endl;
            std::cout << "----------------------------" << std::endl;
            m.printMenuFRONT();
            std::cin.clear();
            std::cout << "Enter an option: " ;
            std::cin >> option_number_2;
            switch(option_number_2)
            {
                case m.ADD_CLIENT:
                {
                    if(LBAAC.DataAlreadyEntered(customerMap , currID) == true){
                        LBAAC.AddFromMapToCustomerVec(customerMap , currID , customer);
                        std::cout << "We have your data in the database system already." << std::endl;
                        break;
                    }
                    sw.Add_Customer(customer , FILENAME , currID);
                    LBAAC.ReadFromFileIntoMap(FILENAME , customerMap);
                    break;
                }
                case m.MODIFY_CIENT:
                {
                    //LBAAC.AddFromMapToCustomerVec(customerMap , currID , customer); mistake here  !!!!
                    sw.Modify_Customer(LBAAC,customer , FILENAME , customerMap , currID);
                    LBAAC.ReadFromFileIntoMap(FILENAME , customerMap);
                    break;
                }
                case m.SEARCH_CLIENT:
                {
                    sw.Search_Customer(customer);
                    break;
                }
                case m.REMOVE_CLIENT:
                {
                    LBAAC.AddFromMapToCustomerVec(customerMap , currID , customer);
                    sw.Remove_Customer(LBAAC,customer , customerMap , FILENAME , currID);
                    LBAAC.ReadFromFileIntoMap(FILENAME, customerMap);
                    break;
                }
                case m.PRINT_CLIENT:
                {
                    LBAAC.ReadFromFileIntoMap(FILENAME, customerMap);
                    int returnVal = sw.Print_Customer(customer , customerMap , currID);
                    break;
                }
                case m.BOOK_HOTEL_FRONT:
                {
                    std::cout.flush();
                    bool EXIT_HOTEL_MENU = true;
                    while (EXIT_HOTEL_MENU == true)
                    {
                        m.printMenuHOTEL();
                        int option_booking_hotel;
                        std::cout << "Enter an option: ";
                        std::cin >> option_booking_hotel;
                        switch(option_booking_hotel)
                        {
                            case m.BOOK_HOTEL:
                            {
                                string answer;
                                int ret = sw.Answer_BOOKING(customer , &answer);
                                if(ret == 1){
                                    EXIT_HOTEL_MENU = false;
                                    break;
                                }
                                if(answer == "YES")
                                {
                                    string answer_city , checkin_date , checkout_date;
                                    sw.DATE_CHECKIN_AND_CITY(cities , &answer_city , &checkin_date , &checkout_date);
                                    int no_hotel = 0;
                                    sw.Print_Hotels_From__answer_city(hotel , &answer_city , &no_hotel);
                                    if(no_hotel == 0){
                                        std::cout <<"We have no hotels in this city.We are sorry for the inconvinience" << std::endl;
                                        break;
                                    }
                                    int pos = -1;
                                    string answer_booking;
                                    sw.Select_HOTEL(hotel , &pos , &answer_booking);
                                    if(pos == -1){
                                        break;
                                    }
                                    auto h_selected = hotel.begin() + pos;
                                    std::cout << *h_selected;
                                    int roomNum_answer , single_rooms , double_rooms , triple_rooms;
                                    int ret2 = sw.Rooms_Select(&roomNum_answer , &single_rooms , &double_rooms , &triple_rooms , h_selected);
                                    if(ret2 == 1){
                                        EXIT_HOTEL_MENU = false;
                                        break;
                                    }
                                    int Total_PAY = 0;
                                    int pay_answer;
                                    int ret3 = sw.TotalPAY_and_WAYtoPay(h_selected , &Total_PAY , &pay_answer , &single_rooms , &double_rooms , &triple_rooms);
                                    //std::cout << Total_PAY << std::endl;
                                    if(ret3 == 1){
                                        EXIT_HOTEL_MENU = false;
                                        break;
                                    }
                                    switch(pay_answer)
                                    {
                                        case m.ONLY_CARD:
                                        {
                                            bool cardName_flag = false;
                                            bool cardNumber_flag = false;
                                            bool cardExpDate_flag = false;
                                            bool cardCVV_flag = false;
                                            bool checkMoney_flag = false;
                                            bool input_flag = false;
                                            bool answer_flag = true;
                                            bool printInfo_flag = false;
                                            bool checkingCardInfo_flag = false;
                                            CustomerCard *cardObj = new CustomerCard;
                                            int ret4 = sw.Pay_Card(&Total_PAY , cardObj , &answer_flag , &input_flag , &cardName_flag ,
                                            &cardNumber_flag , &cardExpDate_flag , &cardCVV_flag , &checkMoney_flag , &printInfo_flag , &checkingCardInfo_flag);
                                            if(ret4 == 1){
                                                sw.Print_Data(&printInfo_flag , cardObj , &Total_PAY , h_selected , customer , &checkin_date , &checkout_date , &single_rooms , &double_rooms , &triple_rooms , currID , customerMap);
                                                break;
                                            }
                                            else if(ret4 == 2)
                                                break;
                                            break;
                                        }
                                        case m.CARD_AND_CASH:
                                        {
                                            bool cardName_flag = false;
                                            bool cardNumber_flag = false;
                                            bool cardExpDate_flag = false;
                                            bool cardCVV_flag = false;
                                            bool checkMoney_flag = false;
                                            bool input_flag = false;
                                            bool answer_flag = true;
                                            bool printInfo_flag = false;
                                            bool checkingCardInfo_flag = false;
                                            CustomerCard *cardObj = new CustomerCard;
                                            int ret4 = sw.Pay_Card(&Total_PAY , cardObj , &answer_flag , &input_flag , &cardName_flag ,
                                            &cardNumber_flag , &cardExpDate_flag , &cardCVV_flag , &checkMoney_flag , &printInfo_flag , &checkingCardInfo_flag);
                                            if(ret4 == 1){
                                                sw.Print_Data(&printInfo_flag , cardObj , &Total_PAY , h_selected , customer , &checkin_date , &checkout_date , &single_rooms , &double_rooms , &triple_rooms , currID , customerMap);
                                                int money = cardObj->getCardMoney();
                                                money = money + (Total_PAY*4)/5;
                                                std::cout << "Left to pay: " << (4*Total_PAY)/5 << "$ in cash" << std::endl;
                                                break;
                                            }
                                            else if(ret4 == 2)
                                                break;
                                            break;
                                        }
                                        default:
                                            break;
                                    }
                                }
                                if(answer == "NO" || answer == "no")
                                    break;
                            }
                            break;
                            case m.SHOW_HOTELS:
                            {
                                sw.Show_Hotels(hotel);
                                break;
                            }
                            case m.SEARCH_HOTEL:
                            {
                                sw.Search_Hotel(hotel);
                                break;
                            }
                            case m.GO_BACK:
                            { 
                                std::cout.flush();
                                EXIT_HOTEL_MENU = false;
                                break;
                            }
                            default:
                                break;
                        }
                    }
                break;
                }
                case m.EXIT_PROGRAM:
                {
                    sw.Exit_Program(customer , hotel);
                    EXIT_PROG = false;
                    break;
                }
                default:
                    break;
                }     
        }
    }

                                                        // CUSTOMER/HOTEL MENU ------- END
                                                        // -----------------------------

