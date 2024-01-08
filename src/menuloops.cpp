#include "menuloops.h"
#define setYellow rlutil::setColor(rlutil::YELLOW)
#define setRed rlutil::setColor(rlutil::RED)
#define setGreen rlutil::setColor(rlutil::GREEN)
#define setLightGreen rlutil::setColor(rlutil::LIGHTGREEN)
#define setLightRed rlutil::setColor(rlutil::LIGHTRED)

                                                    // LOGIN MENU ---- START
                                                    // --------------------
    void MENU_LOOPS::LOGIN_LOOP(Menu m , AccountDataBase& accDB , LinkBetweenAccountAndCustomer& LBAAC , bool& EXIT_LOGIN_REGISTER_MENU ,bool& EXIT_PROG , const char* FILENAME , const char* FILENAME2 , string& currID){
        int option_number;
        while(EXIT_LOGIN_REGISTER_MENU){
            m.printRegisterLoginWindow();
            std::cout << "Enter the option: ";
            std::cin >> option_number;
            switch(option_number){
                case m.REGISTER:
                {
                    int ret = accDB.Register(FILENAME);
                    if(ret == 1)
                        break;
                    break;
                }
                case m.LOGIN:
                {
                    int ret2 = accDB.Login(FILENAME2 , currID);
                    if(ret2 == 0){
                    EXIT_LOGIN_REGISTER_MENU = true;
                    }
                    if(ret2 == 1){
                        EXIT_LOGIN_REGISTER_MENU = false;
                    }
                    break;
                }
                case m.FORGOT_PASS:
                {
                    int ret3 = accDB.ForgotPassword(FILENAME);
                    if(ret3 == 0)
                        break;
                    break;
                }
                case m.EXIT_PROG_REG_LOG_WIND:
                {
                    setRed;
                    Menu m;
                    m.ProgressBarExit();
                    rlutil::resetColor();
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
    void MENU_LOOPS::CustomerAndHotel_MENU(AccountDataBase& accDB , Menu m , LinkBetweenAccountAndCustomer& LBAAC , bool EXIT_PROG ,string currID , std::unordered_map<string,Customer>& customerMap , std::vector<Customer>& customer ,std::vector<Hotel>& hotel ,std::unordered_map<string , City> cities  , const char* FILENAME , const char* FILENAME2){
        int option_number_2;
        while(EXIT_PROG)
        {
            SWITCH sw;
            setLightGreen;
            std::cout << "----------------------------" << std::endl;
            std::cout << "----------------------------" << std::endl;
            std::cout << "You are logged as " ;
            setLightRed;
            std::cout << currID << std::endl;
            setLightGreen;
            std::cout << "----------------------------" << std::endl;
            std::cout << "----------------------------" << std::endl;
            rlutil::resetColor();
            m.printMenuFRONT();
            std::cin.clear();
            std::cout << "Enter an option: " ;
            std::cin >> option_number_2;
            switch(option_number_2)
            {
                case m.ADD_CLIENT:
                {
                    if(LBAAC.DataAlreadyEntered(customerMap , currID)){
                        LBAAC.AddFromMapToCustomerVec(customerMap , currID , customer);
                        setLightRed;
                        std::cout << "We have your data in the database system already." << std::endl;
                        rlutil::resetColor();
                        break;
                    }
                    sw.Add_Customer(customer , FILENAME , currID);
                    LBAAC.ReadFromFileIntoMap(FILENAME , customerMap);
                    break;
                }
                case m.MODIFY_ClIENT:
                {
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
                    sw.Print_Customer(customer , customerMap , currID);
                    break;
                }
                case m.BOOK_HOTEL_FRONT:
                {
                    std::cout.flush();
                    bool EXIT_HOTEL_MENU = true;
                    while (EXIT_HOTEL_MENU)
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
                                int ret = sw.Answer_BOOKING(customer , answer);
                                if(ret == 1){
                                    EXIT_HOTEL_MENU = false;
                                    break;
                                }
                                if(answer == "YES")
                                {
                                    string answer_city , checkin_date , checkout_date;
                                    sw.DATE_CHECKIN_AND_CITY(cities , answer_city , checkin_date , checkout_date);
                                    int no_hotel = 0;
                                    sw.Print_Hotels_From__answer_city(hotel , answer_city , no_hotel);
                                    if(no_hotel == 0){
                                        std::cout <<"We have no hotels in this city.We are sorry for the inconvinience" << std::endl;
                                        break;
                                    }
                                    int pos = -1;
                                    string answer_booking;
                                    sw.Select_HOTEL(hotel , pos , answer_booking);
                                    if(pos == -1){
                                        break;
                                    }
                                    auto h_selected = hotel.begin() + pos;
                                    setLightRed;
                                    std::cout << *h_selected;
                                    rlutil::resetColor();
                                    int roomNum_answer , single_rooms , double_rooms , triple_rooms;
                                    int ret2 = sw.Rooms_Select(roomNum_answer , single_rooms , double_rooms , triple_rooms , h_selected);
                                    if(ret2 == 1){
                                        EXIT_HOTEL_MENU = false;
                                        break;
                                    }
                                    int Total_PAY = 0;
                                    int pay_answer;
                                    int ret3 = sw.TotalPAY_and_WAYtoPay(h_selected , Total_PAY , pay_answer , single_rooms , double_rooms , triple_rooms);
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
                                            auto *cardObj = new CustomerCard();
                                            CustomerCardBuilder cardBuilder;
                                            int ret4 = sw.Pay_Card(Total_PAY , cardObj ,cardBuilder ,answer_flag , input_flag , cardName_flag ,
                                            cardNumber_flag , cardExpDate_flag , cardCVV_flag , checkMoney_flag , printInfo_flag , checkingCardInfo_flag);
                                            if(ret4 == 1){
                                                sw.Print_Data(printInfo_flag , cardObj , Total_PAY , h_selected , customer , checkin_date , checkout_date , single_rooms , double_rooms , triple_rooms , currID , customerMap);
                                                break;
                                            }
                                            else if(ret4 == 2) {
                                                delete cardObj;
                                                break;
                                            }
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
                                            auto *cardObj = new CustomerCard();
                                            CustomerCardBuilder cardBuilder;
                                            int ret4 = sw.Pay_Card(Total_PAY , cardObj , cardBuilder,answer_flag , input_flag , cardName_flag ,
                                            cardNumber_flag , cardExpDate_flag , cardCVV_flag , checkMoney_flag , printInfo_flag , checkingCardInfo_flag);
                                            if(ret4 == 1){
                                                sw.Print_Data(printInfo_flag , cardObj , Total_PAY , h_selected , customer , checkin_date , checkout_date , single_rooms , double_rooms , triple_rooms , currID , customerMap);
                                                std::cout << "Left to pay: " << (4*Total_PAY)/5 << "$ in cash" << std::endl;
                                                break;
                                            }
                                            else if(ret4 == 2){
                                                delete cardObj;
                                                break;
                                            }

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

                            case m.LEAVE_RECENSION:
                            {
                                bool ans = sw.Answer_Review();
                                if(!ans){
                                    break;
                                }
                                Hotel h;
                                h.ReadReviewsFromFile(FILENAME2 , hotel , customer);
                                sw.Post_Review(customer , FILENAME2 , hotel , cities ,currID);
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
                    Menu m;
                    m.ProgressBarExit();
                    EXIT_PROG = false;
                    break;
                }
                case m.LOG_OUT:
                {
                    bool TO_LOG_IN = true;
                    // to add progress bar of loggin out !!!
                    LOGIN_LOOP(m, accDB , LBAAC , TO_LOG_IN , EXIT_PROG , "records.txt" , "LOGINinfo.txt" ,currID);
                    break;
                }
                default:
                    break;
                }     
        }
    }

                                                        // CUSTOMER/HOTEL MENU ------- END
                                                        // -----------------------------

