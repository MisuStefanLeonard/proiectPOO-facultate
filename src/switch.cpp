#include "switch.h"

                                            // FUNCTIONS FOR CUSTOMER/HOTEL OPERATIONS
                                            // ---------------------------------------
                                            // ---------------------------------------
                                            // ADD CUSTOMER - START
                                            // ------------------
    void SWITCH::Add_Customer(std::vector<Customer>& customer , const char *FILENAME , string curr_id){
        Customer c_temp;
        c_temp.Read();
        customer.push_back(c_temp);
        std::ofstream fileout (FILENAME , std::ios::app);
        if(fileout.is_open() == false){
            std::cerr << "File " << FILENAME << " could not be opened" << std::endl;
        }
        std::vector<int> temp_vec_phone_number = c_temp.getNumber();
        fileout << curr_id << "\n" 
            << c_temp.getName() << "\n"
            << c_temp.getPrename() << "\n"
            << c_temp.getAge() << "\n"
            << c_temp.getSex() << "\n"
            << c_temp.getMoney() << "\n"
            << c_temp.getAdult() << "\n";
        fileout << '0';
        for(auto it = temp_vec_phone_number.begin();it!=temp_vec_phone_number.end();++it)
            fileout << *it;
        fileout << "\n";
        fileout << c_temp.getCNP() << "\n";
        fileout << c_temp.getEmail() << "\n";
        fileout << "\n\n\n";
        fileout.close();
        std::cout << "Customer added succesfuly" << std::endl;
    }
                                            //ADD CUSTOMER - END
                                            //----------------

                                            //MODIFY CUSTOMER - START
                                            //------------------
    void SWITCH::ReadFromUSERINFO_INTO_VEC(std::vector<Customer>& custTemp , const char* FILENAME){
        std::ifstream read_from(FILENAME);
        if(read_from.is_open() == false)
            std::cerr << FILENAME << " could not be opened" << std::endl;
        string userName , name , prename , CNP , email;
        char sex;
        int age,money , number;
        bool adult;
        while(read_from >> userName >> name >> prename >> age >> sex >> money >> adult >> number >> CNP >> email){
            Customer customertemp;
            customertemp.setID(userName);
            customertemp.setName(name);
            customertemp.setPrename(prename);
            customertemp.setAge(age);
            customertemp.setSex(sex);
            customertemp.setMoney(money);
            customertemp.setAdult(adult);
            customertemp.setNumber(number);
            customertemp.setCNP(CNP);
            customertemp.setEmail(email);
            custTemp.push_back(customertemp);
            for (int i = 0; i < 3; ++i){
                std::string temp;
                std::getline(read_from, temp);
            }
        }
        // std::cout << "AM AJUNS AICI " << std::endl;
        // std::cout << custTemp.size() << std::endl;
        read_from.close();
        std::ofstream temp_open(FILENAME , std::ios::trunc);
        if(temp_open.is_open() == 0){
            std::cerr << FILENAME << "could not be open and than delete it s contents" << std::endl;
        }
        temp_open.close();
       
    }
    void SWITCH::ReplaceInTempVec(string searchname , std::vector<Customer>& custTemp , Customer& c_temp){
         for(auto it = custTemp.begin() ; it!=custTemp.end() ; ++it){
            if(it->getName() == searchname){
                int customer_position = std::distance<std::vector<Customer>::iterator>(custTemp.begin(), it);
                custTemp.erase(it);
                custTemp.insert(custTemp.begin() + customer_position, c_temp);
                
            }
        }
    }
    void SWITCH::WritingModifiedCustomerBackTo_USERINFO(std::vector<Customer>& custTemp , const char *FILENAME){
        std::ofstream write_to_file(FILENAME , std::ios::app);
        if(write_to_file.is_open() == false)
            std::cerr << FILENAME << " could not be opened";
        for(auto c = custTemp.begin() ; c != custTemp.end() ; ++c){
            std::vector<int> temp_vec_phone_number = c->getNumber();
            write_to_file << c->getID()<< "\n" 
                << c->getName() << "\n"
                << c->getPrename() << "\n"
                << c->getAge() << "\n"
                << c->getSex() << "\n"
                << c->getMoney() << "\n"
                << c->getAdult() << "\n";
            write_to_file << '0';
            for(auto it = temp_vec_phone_number.begin();it!=temp_vec_phone_number.end();++it)
                 write_to_file << *it;
            write_to_file << "\n";
            write_to_file << c->getCNP() << "\n";
            write_to_file << c->getEmail() << "\n";
            write_to_file << "\n\n\n";
        }
        write_to_file.close();
        
    }
    void SWITCH::Modify_Customer(LinkBetweenAccountAndCustomer LBAAC,std::vector<Customer> &customer,const char*FILENAME , std::unordered_map<string , Customer>& mapofcustomers , string currID){
        if(LBAAC.DataAlreadyEntered(mapofcustomers , currID) == false){
            std::cout << "Your data cannot be modified because we do not have it in our database.Please first add it(option number 1) " << std::endl;
        }
        Customer c_temp;
        string search_name = c_temp.searchClientbyName();
        auto c = customer.begin();
        bool customer_found = false;
        for(c = customer.begin();c!= customer.end() ; ++c){
            if(search_name == c->getName()){
                std::cout << "Customer found" << std::endl;
                int customer_position = std::distance<std::vector<Customer>::iterator>(customer.begin(), c);
                customer.erase(c);
                c_temp.Read();
                c_temp.setID(currID);
                customer.insert(customer.begin() + customer_position, c_temp);
                customer_found = true;
                std::cout << "Customer modified succesfuly" << std::endl;
                break;
            }
        }
        if(customer_found == true){
            std::vector<Customer> custTemp;
            ReadFromUSERINFO_INTO_VEC(custTemp , FILENAME);
            ReplaceInTempVec(search_name , custTemp , c_temp);
            WritingModifiedCustomerBackTo_USERINFO(custTemp , FILENAME);
            auto it = mapofcustomers.find(currID);
            it->second = c_temp;
        }
        if(customer_found == false)
            std::cout << "There is no customer with the name :" << search_name  << " that you want to modify"<< std::endl;
            
    }
                                                // MODIFY CUSTOMER - END
                                                // ------------------

                                                // SEARCH_CUSTOMER - START
                                                // -------------------
    void SWITCH::Search_Customer(std::vector<Customer> &customer){
        if(customer.empty() == true)
            std::cout << "There are no customers in the list.You cannot modify the respective customer" << std::endl;

        Customer c_temp;
        string search_name = c_temp.searchClientbyName();
        auto c = customer.begin();
        bool customer_found = false;
        for(c = customer.begin() ; c!=customer.end() ; ++c){
            if(search_name == c->getName()){
                std::cout << "Customer found" << std::endl;
                customer_found = true;
                c->Print();
                break;
                }
            }
        if(customer_found == false)
            std::cout << "There is no customer with the name :" << search_name << std::endl;
    }
                                                    // SEARCH_CUSTOMER - END
                                                    // ---------------------

                                                    // REMOVE_CUSTOMER - START
                                                    // ------------------
    void SWITCH::REMOVE_IN_VEC(std::vector<Customer>& custTemp, Customer& c_temp, string CNP_search){
        auto it = custTemp.begin();
        while(it != custTemp.end()){
            if(it->getCNP() == CNP_search){
                it = custTemp.erase(it);
            }else{
                ++it;
            }
        }
    }   
    void SWITCH::Remove_Customer(LinkBetweenAccountAndCustomer LBAAC,std::vector<Customer> &customer , std::unordered_map<string , Customer>& map_of_customers , const char* FILENAME , string currID){
        if(LBAAC.DataAlreadyEntered(map_of_customers , currID) == false){
            std::cout << "Your data cannot be deleted because we do not have it in our database.Please first add it(option number 1) " << std::endl;
        }
        Customer c_temp;
        string search_CNP = c_temp.searchClientbyCNP();
        bool customer_found = false;
        auto c = customer.begin();
        for(c=customer.begin() ; c!= customer.end() ; ++c){
            if(search_CNP == c->getCNP()){
                std::cout << "Customer found" << std::endl;
                string answer;
                std::cout << "Are you sure you want to delete the customer? Type YES or NO(with capital letters): ";
                std::cin >> answer;
                if(answer == "NO"){
                    break;
                    customer_found = true;
                }
                if(answer == "YES"){
                    c_temp = *c;
                    c_temp.setID(currID);
                    customer.erase(c);
                    customer_found = true;
                    std::cout << "Customer deleted succesfuly" << std::endl;
                    break;
                }
            }
        }
        if(customer_found == true){
            std::vector<Customer> custTemp;
            ReadFromUSERINFO_INTO_VEC(custTemp , "userinfo.txt");   
            REMOVE_IN_VEC(custTemp , c_temp , search_CNP);
            WritingModifiedCustomerBackTo_USERINFO(custTemp , "userinfo.txt"); 
            map_of_customers.erase(currID);

        }
        if(customer_found == false)
            std::cout << "There is no customer with the CNP: " << search_CNP << std::endl;
    }
                                                        // REMOVE_CUSTOMER - END
                                                        // --------------------

                                                        // PRINT CURRENT CUSTOMER DATA - START
                                                        // ------------------------------
    int SWITCH::Print_Customer(std::vector<Customer>& customer , std::unordered_map<string , Customer> customerMap , string currID){
        if(customerMap.empty() == true){
            std::cout << "There are no customers in the list" << std::endl;
            return 0;
        }
        bool customer_found = false;
        auto c = customer.begin();
        string looking_for_customer;
        std::cout << "Enter the CNP of the customer you want to print data about: ";
        int count_CNP = 0;
        while(true){
        std::cin >> looking_for_customer;
        auto it = looking_for_customer.begin();
        for(it = looking_for_customer.begin();it != looking_for_customer.end() ; ++it){
            if(isdigit((*it)) == true){
                count_CNP++;
                continue;
            }
                break;
        }
        if(count_CNP == looking_for_customer.size())
            break;
        }
        Customer temp;
        if(customerMap.find(currID) != customerMap.end()){
            auto it = customerMap.find(currID);
            temp = it->second;
            customer_found = true;
        }
        if(customer_found == true){
            std::cout << "We found the customer you are looking for" << std::endl;
            std::cout << "------------------------------------" << std::endl;
            std::cout << "------------------------------------" << std::endl;
            temp.Print();
            return 1;
        }
        if(customer_found == false){
            std::cout << "There is no customer with the CNP: " << looking_for_customer << " that you want to print data about" << std::endl;
            return 0;
        }
    }
                                                        // PRINT CURRENT CUSTOMER DATA - END
                                                        // --------------------------------
    void SWITCH::Exit_Program(std::vector<Customer> &customer , std::vector<Hotel> &hotel){
        auto c = customer.begin();
        while (c != customer.end()){
            c = customer.erase(c);
        }
        auto h = hotel.begin();
        while (h != hotel.end()){
            h = hotel.erase(h);
        }
        std::cout << "Exiting program" << std::endl;
    }
                                    // SHOW ALL HOTELS - START
                                    // ---------------------
    void SWITCH::Show_Hotels(std::vector<Hotel> & hotel){
        for(auto &h : hotel){
            h.Print();
        }
    }
                                    // SHOW ALL HOTELS - END
                                    // --------------------

                                    // SEARCH HOTEL - START
                                    // ------------------
    void SWITCH::Search_Hotel(std::vector<Hotel>& hotel){
        Hotel HOTEL;
        string looking_for_hotel = HOTEL.searchHotel(); 
        bool hotel_found = false;
        for(auto &h : hotel){
            if(looking_for_hotel == h.gethName()){
                hotel_found = true;
                std::cout << "Hotel found " << std::endl;
                h.Print();
                break;
            }
        }
        if(hotel_found == false)
            std::cout << "Hotel with the name " << looking_for_hotel << " cannot be found" << std::endl;
    }
                                    // SEARCH HOTEL - END
                                    // -----------------

                                    // BOOK HOTEL - START
                                    // -----------------
    int SWITCH::Answer_BOOKING(std::vector<Customer> &customer , string *ans){
        if(customer.size() == 0){
            std::cout << "First please enter your info. " << std::endl;
            std::cout.flush();
            return 1;
        }
        string answer;
        int count = 0;
        std::cout << "Would you like to book a rezervation to the hotel?Please enter the answer here(YES or NO): ";
        while(true){
        std::cin >> answer;
            if(answer == "yes" || answer == "no"){
                auto it = answer.begin();
                for(it = answer.begin() ; it != answer.end() ; ++it){
                    *it = toupper((*it));
                }
            }
            auto it = answer.begin();
            for(it = answer.begin();it != answer.end(); ++it){
                if(isalpha((*it)) != 0){
                    count++;
                    continue;
                }
            }
            if(count == answer.size())
                break;
            std::cout << "Please enter a valid answer: ";
        }
        *ans = answer;
        return 0;
    }
    void SWITCH::DATE_CHECKIN_AND_CITY(std::unordered_map<string , City>& cities , string *ans_city , string *checkin_dt , string *checkout_dt){
    for(auto &city : cities)
        std::cout << city.second.getName() << std::endl;
    string answer_city , checkin_date , checkout_date;
    std::cout << "--------------" << std::endl;
    std::cout << "--------------" << std::endl;
    std::cout << "Please enter the name of the city you want to go in from the respective list: " << std::endl;
    while(true){
    std::cin >> answer_city;
    bool found = false;
    for(auto &city : cities){
        if(answer_city == city.second.getName()){
             found = true;
             break;
         }
    }
    if(found == true){

        std::cout << "Valid city entered" << std::endl;
        std::cout << "-------------------" << std::endl;
        break;
        }
    std::cout << answer_city <<  " it is not in the list.Please enter name again:" << std::endl;
    }
    std::cout << "Please enter the date of check-in(DD.MM.YYYY): " << std::endl;
    bool checkinDate_flag = false , exit_while = false;
    while(exit_while == false)
        {
        while(checkinDate_flag == false){
            std::cin >> checkin_date;
            const regex check_date_in("^(0[1-9]|[1-2][0-9]|3[0-1])\\.(0[1-9]|1[0-2])\\.\\d{4}$");
            if(std::regex_match(checkin_date , check_date_in))
                checkinDate_flag = true;
            else
                std::cout << "Please enter a valid date format: ";
        }
        std::cout << "Please enter the date of check-out(DD.MM.YYYY): " << std::endl;
        bool checkoutDate_flag = false;
        while(checkoutDate_flag == false){
            std::cin >> checkout_date;
            const regex check_date_out ("^(0[1-9]|[1-2][0-9]|3[0-1])\\.(0[1-9]|1[0-2])\\.\\d{4}$");
            if(std::regex_match(checkout_date , check_date_out))
                checkoutDate_flag = true;
            else
            std::cout << "Please enter a valid date format: ";
        }
        string day_checkin = checkin_date.substr(0,2);
        int int_day_checkin = std::stoi(day_checkin);
        string day_checkout = checkout_date.substr(0,2);
        int int_day_checkout = std::stoi(day_checkout);
        bool flag1 = false , help_flag_month = false;
        string month_checkin = checkin_date.substr(3,2);
        int int_month_checkin = std::stoi(month_checkin);
        string month_checkout = checkout_date.substr(3,2);
        int int_month_checkout = std::stoi(month_checkout);
        bool flag2 = false;
        if(int_month_checkin < int_month_checkout)
            help_flag_month = true;
        if(int_month_checkin == int_month_checkout)
            flag2 = true;
        if(int_day_checkin < int_day_checkout && flag2 == true)
            flag1 = true;
        if(int_day_checkin > int_day_checkout && help_flag_month == true){
            flag2 = true;
            flag1 = true;
        }
        string year_checkin = checkin_date.substr(6,4);
        int int_year_checkin = std::stoi(year_checkin);
        string year_checkout = checkout_date.substr(6,4);
        int int_year_checkout = std::stoi(year_checkout);
        bool flag3 = false;
        if(int_year_checkin <= int_year_checkout)
            flag3 = true;
        if(flag1 == true && flag2 == true && flag3 == true)
            break;
        if(flag1 == false || flag2 == false || flag3 == false)
            std::cout << "Check-out day must be bigger than check-in day\nCheck-out month must be biggerORequal to check-in month\n";
        }
    *ans_city = answer_city;
    *checkin_dt = checkin_date;
    *checkout_dt = checkout_date;
    }
    void SWITCH::Print_Hotels_From__answer_city(std::vector<Hotel> &hotel,string *answer_city ,int *no_hotel){
        std::cout << "Our sistem is working...Please wait...Thank you" << std::endl;
        std::cout << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        std::cout << "\t\t\tHOTELS IN " << *answer_city << std::endl;
        std::cout << "\t\t------------------------------------"<<  std::endl;
        auto h = hotel.begin();
        int no_hotel_cpy = 0;
        for(h = hotel.begin(); h != hotel.end(); ++h){
            string h_copy_name = h->gethCity();
            if(*answer_city == h_copy_name){
                std::cout <<"\t   Hotel " << ++no_hotel_cpy << std::endl;
                std::cout << "-----------------------------------------------------------" << std::endl;
                std::cout << *h;
                std::cout << "-----------------------------------------------------------"  << std::endl;
            }
        }
        *no_hotel = no_hotel_cpy;
    }
    void SWITCH::Select_HOTEL(std::vector<Hotel> &hotel, int *p_pos , string *p_answer_booking)
    {   
        string answerbooking_global;
        int poss = -1;
        std::cout << "Select which hotel would you like to book(enter the name): ";
        bool repeat_ans_flag = true;
        while(repeat_ans_flag == true)
        {
            bool isValidInput = false;
            string answer_booking;
            std::cin >> answer_booking;
            while(isValidInput == false)
            {
                std::cout << std::endl;
                const regex check("[A-Za-z\\s]+$");
                if(std::regex_match(answer_booking,check) == true)
                    isValidInput = true;
                else
                    std::cout << "Hotel name must contain only letter from enlglish alphabeth.Please enter the name again: ";
            }
            const char* str = answer_booking.c_str();
            auto h = hotel.begin();
            bool found_hotel = false;
            for(h = hotel.begin();h!=hotel.end();++h){
                string h_curr_name = h->gethName();
                const char* cstr_h_curr_name = h_curr_name.c_str();
                if((strcasecmp(cstr_h_curr_name , str) == 0 && answer_booking == h->gethName())){
                    found_hotel = true;
                    repeat_ans_flag = false;
                    std::cout << "You selected hotel " << h_curr_name << std::endl;
                    std::cout << std::endl;
                    poss = std::distance<std::vector<Hotel>::iterator>(hotel.begin(), h);
                    answerbooking_global = answer_booking;
                }
            }
            if(found_hotel == false){
                std::cout << "There is no hotel with this name in the list with the name - " << answer_booking << std::endl;
                std::cout << "Would you like to enter the hotel name again?(Y/N)"<< std::endl;
                string repeat_ans;
                std::cin >> repeat_ans;
                if(repeat_ans != "Y" && repeat_ans != "y"){
                    repeat_ans_flag = false;
                }else{
                    std::cout << "Please enter here: ";
                    std::cout << std::endl;
                }
            }
        }
        *p_pos = poss;
        *p_answer_booking = answerbooking_global;
    }
    int SWITCH::Rooms_Select(int *roomNUM_ans,int *oneBR_rooms , int *twoBR_rooms , int *threeBR_rooms ,  std::vector<Hotel>::iterator h_selected){
        int roomNum_answer , single_rooms , double_rooms , triple_rooms;
        std::cout << "How many rooms would you want?" << std::endl;
        while(true){
            std::cin >> roomNum_answer;
            if(roomNum_answer != 0 || roomNum_answer > 0)
                break;
            std::cout << "Room number cannot be 0.Please enter again: ";
        }
        bool input_rooms_flag = false;
        bool exit1 = true , exit2 = true , exit3 = true;
        while(input_rooms_flag == false)
        {
            std::cout << "Number of single rooms:";
            while(true){
                std::cin >> single_rooms;
                if(single_rooms > h_selected->gethSingleRoom() || single_rooms < 0){
                    std::cout << "There are no more single rooms avalible" << std::endl;
                    string continue_flag;
                    std::cout << "Would you like to continue?(Y/N)" << std::endl;
                    std::cin >> continue_flag;
                    if(continue_flag != "Y" && continue_flag != "y"){
                         exit1 = false;
                         break;
                    }
                }
            *oneBR_rooms = single_rooms;
            break;
            }
            std::cout << std::endl;
            std::cout << "Number of double rooms:";
            while(true){
                std::cin >> double_rooms;
                if(double_rooms > h_selected->gethDoubleRoom() || double_rooms < 0){
                    std::cout << "There are no more double rooms avalible" << std::endl;
                    string continue_flag;
                    std::cout << "Would you like to continue?(Y/N)" << std::endl;
                    std::cin >> continue_flag;
                    if(continue_flag != "Y" && continue_flag != "y"){
                        exit2 = false;
                        break;
                    }
                }
            *twoBR_rooms = double_rooms;
            break;
            }           
            std::cout << std::endl;
            std::cout << "Number of triple rooms:";
            while(true){
                std::cin >> triple_rooms;
                if(triple_rooms > h_selected->gethTripleRoom() || triple_rooms < 0){
                    std::cout << "There are no more triple rooms avalible" << std::endl;
                    string continue_flag;
                    std::cout << "Would you like to continue?(Y/N)" << std::endl;
                    std::cin >> continue_flag;
                    if(continue_flag != "Y" && continue_flag != "y"){
                        exit3 = false;
                        break;
                    }
                }
            *threeBR_rooms = triple_rooms;
            break;
            }
            std::cout << std::endl;
            string answer_modifiy;
            std::cout << "You selected" << std::endl;
            std::cout << "One bedroom rooms: " << single_rooms << std::endl;
            std::cout << "Two bedroom rooms: " << double_rooms << std::endl;
            std::cout << "Triple bedroom rooms: " << triple_rooms << std::endl;
            std::cout << "Would you like to modifiy anything?(Y/N)" << std::endl;
            std::cin  >> answer_modifiy;
            if(answer_modifiy != "N" && answer_modifiy != "n")
                continue;
            else
                input_rooms_flag = true;
        }
    if(exit1 == false || exit2 == false || exit3 == false)
        return 1;
    return 0;                       
    }
    int SWITCH::TotalPAY_and_WAYtoPay(std::vector<Hotel>::iterator h_selected , int* p_Total_PAY , int *p_pay_answer ,int *oneBR_rooms , int *twoBR_rooms , int *threeBR_rooms ){
        *p_Total_PAY = h_selected->gethPriceSingleRoom() * (*oneBR_rooms) + h_selected->gethPriceDoubleRoom() * (*twoBR_rooms) + h_selected->gethPriceTripleRoom() * (*threeBR_rooms);
        std::cout << "Total to pay: " << *p_Total_PAY << "$" << std::endl;
        bool pay_flag = false;
        std::cout << "How would you like to pay? You can either pay now for the whole trip OR you can pay in advance 20 percent on card and the rest in the day of the check in." << std::endl;
        std::cout << "1 is for the first option and 2 is for the second option. Please enter:";
        bool pay_exit = true;
        int pay_answer;
        while(pay_flag == false){
            std::cin >> pay_answer;
            if(pay_answer != 1 && pay_answer != 2){
                std::cout << "Do u wish to continue with the payment?(Y/N).Please enter here:";
                string response;
                std::cin >> response;
                if(response != "Y" && response != "y"){
                    pay_exit = false;
                    break;
                }
            }else
                pay_flag = true;
        }
        if(pay_exit == false)
            return 1;
        *p_pay_answer = pay_answer;
        return 0;
    }
    int SWITCH::Pay_Card(int *p_Total_PAY , CustomerCard* cardObj , bool* answer_flag , bool *input_flag , bool *cardName_flag , bool * cardNumber_flag ,
    bool* cardExpDate_flag , bool *cardCVV_flag , bool *checkMoney_flag  , bool* printInfo_flag , bool* checkingCardInfo_flag){
        while(*answer_flag == true)
        {
            *input_flag = false;
            cardObj->Read();
            const regex checkName("^[A-Za-z\\s-]+$");
            if(std::regex_match(cardObj->cardGetName(),checkName) == true)
                *cardName_flag = true;
            const regex checkCardNumber("^\\d{4}( \\d{4}){3}$");
            if(std::regex_match(cardObj->cardGetCardNumber() , checkCardNumber) == true)
                *cardNumber_flag = true;
            const regex checkExpDate("^(0[1-9]|1[0-2])/[0-9]{4}$");
            if(std::regex_match(cardObj->cardGetExpirationDate(),checkExpDate) == true){
                if(cardObj->isValidExpirationDate() == true) 
                    *cardExpDate_flag = true;
            }
            const regex checkCVV("[0-9\\s]{2,3}$");
            string currCVV = cardObj->cardGetCVV();
            if(std::regex_match(currCVV,checkCVV) && (currCVV.size() == 2 || currCVV.size() == 3) == true)
                *cardCVV_flag = true;
            if(cardObj->getCardMoney() >= *p_Total_PAY || cardObj->getCardMoney() >= (*p_Total_PAY)/5)
                *checkMoney_flag = true;
            bool money_flag = false;
            if(*checkMoney_flag == false)
            {
                std::cout << "You do not have the neccesary amount of money to pay for the reservation" << std::endl;
                std::cout << "Would you like the enter another card?(Y/N)";
                string card_answer;
                std::cin >> card_answer;
                if(card_answer != "Y" && card_answer != "y"){
                    *answer_flag = false;
                }
            money_flag = true;
            }
            bool confirmation_answer_flag = false , exit_confirmation = false;
            if(*cardName_flag == true && *cardNumber_flag == true && *cardExpDate_flag == true && *cardCVV_flag == true && *checkMoney_flag == true)
            {
                std::cout << "Please enter YES for confirmation or NO to exit: ";
                string confirmation_answer;
                std::cin >> confirmation_answer;
                if(confirmation_answer == "YES" || confirmation_answer == "yes"){
                    std::cout << "Please wait....Checking card informations..." << std::endl;
                    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                    *input_flag = true;
                    confirmation_answer_flag = true;
                    *printInfo_flag = true;
                    *checkingCardInfo_flag = true;
                    exit_confirmation = true;
                }
            }
            if(exit_confirmation == true)
                return 1;
            if(money_flag == true){
                confirmation_answer_flag = true;
                *input_flag = true;
            }
            if(confirmation_answer_flag == false)
                return 2;
            if(*input_flag == false && *checkingCardInfo_flag == false)
                std::cout << "The data that you entered it's not correct.Please enter it again: " << std::endl;
            if(*answer_flag == false)
                break;
        }
        return 0;
    }
    void SWITCH::Print_Data(bool *printInfo_flag , CustomerCard *cardObj , int *p_Total_PAY ,
    std::vector<Hotel>::iterator h_selected , std::vector<Customer>& customer,
    string *p_checkinDate ,string *p_checkOutDate , int *p_singleRooms , int *p_doubleRooms , int *p_tripleRooms , string currID , std::unordered_map<string , Customer>& customerMap)
    {
        if(*printInfo_flag == true)
        {
            int money = cardObj->getCardMoney();
            money -= (*p_Total_PAY);
            std::cout << "Payment has been done!Enjoy your reservation!" << std::endl;
            std::cout << "\t\t----------------INFORMATIONS ABOUT YOUR RESERVATION----------------" << std::endl;
            std::cout << "\t\t\t\t---------RESERVED HOTEL---------" << std::endl ;
            std::cout << *h_selected;
            std::cout << "\t\t\t------Your Info------ " << std::endl;
            std::cout << "-----------------------------------------------" << std::endl;
            auto it = customerMap.find(currID);
            Customer temp = it->second;
            temp.Print();
            std::cout <<"Check-in date: " << *p_checkinDate << "\t" << "Check-out date: " << *p_checkOutDate  << std::endl;
            std::cout <<"---------> ONE BEDROOM ROOMS: " << *p_singleRooms << std::endl;
            std::cout <<"---------> TWO BEDROOM ROOMS: " << *p_doubleRooms << std::endl;
            std::cout <<"---------> THREE BEDROOM ROOMS: " << *p_tripleRooms << std::endl;
            std::cout << std::endl;
            std::cout << std::endl;
            std::cout <<"Thank you for using our platform!" << std::endl;
            delete cardObj;
        }else{
            delete cardObj;
        }
            
    }
                                                            // BOOK HOTEL - END
                                                            // ----------------

