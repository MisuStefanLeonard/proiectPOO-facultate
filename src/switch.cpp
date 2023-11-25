#include "switch.h"
#include "../date/date.h"
#define setYellow rlutil::setColor(rlutil::YELLOW)
#define setLightRed rlutil::setColor(rlutil::LIGHTRED)
#define setRed rlutil::setColor(rlutil::RED)
#define setGrey rlutil::setColor(rlutil::GREY)
#define setCyan rlutil::setColor(rlutil::CYAN)

                                            // FUNCTIONS FOR CUSTOMER/HOTEL OPERATIONS
                                            // ---------------------------------------
                                            // ---------------------------------------
                                            // ADD CUSTOMER - START
                                            // ------------------
    void SWITCH::Add_Customer(std::vector<Customer>& customer , const char *FILENAME , const string& curr_id){
        Customer c_temp;
        std::cin >> c_temp;
        customer.push_back(c_temp);
        std::ofstream fileout (FILENAME , std::ios::app);
        if(!fileout.is_open()){
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
        if(!read_from.is_open())
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
        if(!write_to_file.is_open())
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
    void SWITCH::Modify_Customer(LinkBetweenAccountAndCustomer LBAAC,std::vector<Customer> &customer,const char*FILENAME , std::unordered_map<string , Customer>& mapofcustomers , const string& currID){
        if(!LBAAC.DataAlreadyEntered(mapofcustomers , currID)){
            setRed;
            std::cout << "Your data cannot be modified because we do not have it in our database.Please first add it(option number 1) " << std::endl;
            rlutil::resetColor();
        }
        Customer c_temp;
        string search_name = c_temp.searchClientbyName();
        auto c = customer.begin();
        bool customer_found = false;
        for(c = customer.begin();c!= customer.end() ; ++c){
            if(search_name == c->getName()){
                setLightGreen;
                std::cout << "Customer found" << std::endl;
                rlutil::resetColor();
                int customer_position = std::distance<std::vector<Customer>::iterator>(customer.begin(), c);
                customer.erase(c);
                std::cin >> c_temp;
                c_temp.setID(currID);
                customer.insert(customer.begin() + customer_position, c_temp);
                customer_found = true;
                std::cout << "Customer modified succesfuly" << std::endl;
                break;
            }
        }
        if(customer_found){
            std::vector<Customer> custTemp;
            ReadFromUSERINFO_INTO_VEC(custTemp , FILENAME);
            ReplaceInTempVec(search_name , custTemp , c_temp);
            WritingModifiedCustomerBackTo_USERINFO(custTemp , FILENAME);
            auto it = mapofcustomers.find(currID);
            it->second = c_temp;
        }
        else{
            setRed;
            std::cout << "There is no customer with the name :" << search_name  << " that you want to modify"<< std::endl;
            rlutil::resetColor();
        }
            
    }
                                                // MODIFY CUSTOMER - END
                                                // ------------------

                                                // SEARCH_CUSTOMER - START
                                                // -------------------
    void SWITCH::Search_Customer(std::vector<Customer> &customer){
        if(customer.empty())
            std::cout << "There are no customers in the list.You cannot modify the respective customer" << std::endl;

        Customer c_temp;
        string search_name = c_temp.searchClientbyName();
        auto c = customer.begin();
        bool customer_found = false;
        for(c = customer.begin() ; c!=customer.end() ; ++c){
            if(search_name == c->getName()){
                std::cout << "Customer found" << std::endl;
                customer_found = true;
                std::cout << *c;
                break;
                }
            }
        if(!customer_found)
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
        if(!LBAAC.DataAlreadyEntered(map_of_customers , currID)){
            setRed;
            std::cout << "Your data cannot be deleted because we do not have it in our database.Please first add it(option number 1) " << std::endl;
            rlutil::resetColor();
        }
        Customer c_temp;
        string search_CNP = c_temp.searchClientbyCNP();
        bool customer_found = false;
        auto c = customer.begin();
        for(c=customer.begin() ; c!= customer.end() ; ++c){
            if(search_CNP == c->getCNP()){
                setLightGreen;
                std::cout << "Customer found" << std::endl;
                rlutil::resetColor();
                string answer;
                setRed;
                std::cout << "Are you sure you want to delete the customer? Type YES or NO(with capital letters): ";
                rlutil::resetColor();
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
        if(customer_found){
            std::vector<Customer> custTemp;
            ReadFromUSERINFO_INTO_VEC(custTemp , "userinfo.txt");   
            REMOVE_IN_VEC(custTemp , c_temp , search_CNP);
            WritingModifiedCustomerBackTo_USERINFO(custTemp , "userinfo.txt"); 
            map_of_customers.erase(currID);

        }
        if(!customer_found)
            std::cout << "There is no customer with the CNP: " << search_CNP << std::endl;
    }
                                                        // REMOVE_CUSTOMER - END
                                                        // --------------------

                                                        // PRINT CURRENT CUSTOMER DATA - START
                                                        // ------------------------------
    int SWITCH::Print_Customer(std::vector<Customer>& customer , std::unordered_map<string , Customer> customerMap , string currID){
        if(customerMap.empty()){
            std::cout << "There are no customers in the list" << std::endl;
            return 0;
        }
        bool customer_found = false;
        //auto c = customer.begin();
        string looking_for_customer;
        std::cout << "Enter the CNP of the customer you want to print data about: ";
        int count_CNP = 0;
        while(true){
        std::cin >> looking_for_customer;
        for(auto it = looking_for_customer.begin();it != looking_for_customer.end() ; ++it){
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
        if(customer_found){
            setLightGreen;
            std::cout << "We found the customer you are looking for" << std::endl;
            std::cout << "------------------------------------" << std::endl;
            std::cout << "------------------------------------" << std::endl;
            std::cout << temp;
            rlutil::resetColor();
            return 1;
        }else{
            setRed;
            std::cout << "There is no customer with the CNP: " << looking_for_customer << " that you want to print data about" << std::endl;
            rlutil::resetColor();
            return 0;
        }
        return 1;
    }
                                                        // PRINT CURRENT CUSTOMER DATA - END
                                                        // --------------------------------
    void SWITCH::Exit_Program(std::vector<Customer> &customer , std::vector<Hotel> &hotel){
        customer.clear();
        hotel.clear();
    }
                                    // SHOW ALL HOTELS - START
                                    // ---------------------
    void SWITCH::Show_Hotels(std::vector<Hotel> & hotel){
        for(auto &h : hotel){
           std::cout << h;
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
                std::cout << h;
                break;
            }
        }
        if(!hotel_found)
            std::cout << "Hotel with the name " << looking_for_hotel << " cannot be found" << std::endl;
    }
                                    // SEARCH HOTEL - END
                                    // -----------------

                                    // BOOK HOTEL - START
                                    // -----------------
    int SWITCH::Answer_BOOKING(std::vector<Customer> &customer , string &ans){
        if(customer.empty()){
            setRed;
            std::cout << "First please enter your info. " << std::endl;
            rlutil::resetColor();
            std::cout.flush();
            return 1;
        }
        string answer;
        int count = 0;
        setCyan;
        std::cout << "Would you like to book a rezervation to the hotel?Please enter the answer here(YES or NO): ";
        while(true){
        setLightGreen;
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
        ans = answer;
        return 0;
    }
    void SWITCH::DATE_CHECKIN_AND_CITY(std::unordered_map<string , City>& cities , string &ans_city , string &checkin_dt , string &checkout_dt)
    {
    setYellow;
    for(auto &city : cities)
        std::cout << "------------ " << city.second.getName() << " ------------"<< std::endl;
    rlutil::resetColor();
    string answer_city , checkin_date , checkout_date;
    setLightRed;
    std::cout << "************************" << std::endl;
    std::cout << "************************" << std::endl;
    std::cout << "Please enter the name of the city you want to go in from the respective list: " << std::endl;
    while(true){
    setLightGreen;
    std::cin >> answer_city;
    bool found = false;
    for(auto &city : cities){
        if(answer_city == city.second.getName()){
             found = true;
             break;
         }
    }
    if(found){
        setLightGreen;
        std::cout << "Valid city entered" << std::endl;
        std::cout << "-------------------" << std::endl;
        rlutil::resetColor();
        break;
        }

    std::cout << answer_city ;
    setLightRed;
    std::cout << " it is not in the list.Please enter name again:";
    rlutil::resetColor();
    }
    bool running_checkdate = true;
    while(running_checkdate)
    {
        setLightGreen;
        std::cout << "Please enter the date of check-in";
        setLightRed;
        std::cout << "(DD.MM.YYYY)" << std::endl; 
        bool checkinDate_flag = false , exit_while = false;
        while(!exit_while)
        {
            while(!checkinDate_flag)
            {
                std::cin >> checkin_date;
                const regex check_date_in("^(0[1-9]|[1-2][0-9]|3[0-1])\\.(0[1-9]|1[0-2])\\.\\d{4}$");
                if(std::regex_match(checkin_date , check_date_in))
                    checkinDate_flag = true;
                else{
                    setLightRed;
                    std::cout << "Please enter a valid date format: ";
                    rlutil::resetColor();
                }
            }
            setLightGreen;
            std::cout << "Please enter the date of check-out";
            setLightRed;
            std::cout << "(DD.MM.YYYY):" << std::endl;
            bool checkoutDate_flag = false;
            while(!checkoutDate_flag )
            {
                std::cin >> checkout_date;
                const regex check_date_out ("^(0[1-9]|[1-2][0-9]|3[0-1])\\.(0[1-9]|1[0-2])\\.\\d{4}$");
                if(std::regex_match(checkout_date , check_date_out))
                    checkoutDate_flag = true;
                else{
                    setLightRed;
                    std::cout << "Please enter a valid date format: ";
                    rlutil::resetColor();
                }
            }

            auto current_date = date::year_month_day{date::floor<date::days>(std::chrono::system_clock::now())};

            std::istringstream iss_check_in(checkin_date);
            std::istringstream iss_check_out(checkout_date);

            date::year_month_day ymd_checkin , ymd_checkout;
            iss_check_in >> date::parse("%d.%m.%Y" , ymd_checkin);
            iss_check_out >> date::parse("%d.%m.%Y" ,ymd_checkout);
            if(ymd_checkin >= current_date && ymd_checkin < ymd_checkout)
            {
                setLightGreen;
                std::cout << "Valid dates of check-in and checkout" << std::endl;
                exit_while = true;
                running_checkdate = false;
            }
            else
            {
                setLightRed;
                checkinDate_flag = false;
                checkoutDate_flag = false;
                exit_while = true;
                std::cout << "--> Check-out day must be bigger than check-in day\n" 
                            "--> Check-out month must be biggerORequal to check-in month\n"
                            "--> Check-in date must be biggerORequal than current date\n";
            }
        }
    }
        ans_city = answer_city;
        checkin_dt = checkin_date;
        checkout_dt = checkout_date;
    }
    void SWITCH::Print_Hotels_From__answer_city(std::vector<Hotel> &hotel,string &answer_city ,int &no_hotel){
        // loading bar here 
        std::cout << "Our sistem is working...Please wait...Thank you" << std::endl;
        std::cout << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        setLightGreen;
        std::cout << "\t\t\tHOTELS IN " << answer_city << std::endl;
        std::cout << "\t\t------------------------------------"<<  std::endl;
        rlutil::resetColor();
        auto h = hotel.begin();
        int no_hotel_cpy = 0;
        setYellow;
        for(h = hotel.begin(); h != hotel.end(); ++h){
            string h_copy_name = h->gethCity();
            if(answer_city == h_copy_name){
                std::cout <<"\t   Hotel " << ++no_hotel_cpy << std::endl;
                std::cout << "-----------------------------------------------------------" << std::endl;
                std::cout << *h;
                std::cout << "-----------------------------------------------------------"  << std::endl;
            }
        }
        no_hotel = no_hotel_cpy;
        rlutil::resetColor();
    }
    void SWITCH::Select_HOTEL(std::vector<Hotel> &hotel, int &p_pos , string &p_answer_booking)
    {   
        string answerbooking_global;
        int poss = -1;
        setLightRed;
        std::cout << "Select which hotel would you like to book(enter the name): ";
        setGrey;
        bool repeat_ans_flag = true;
        while(repeat_ans_flag)
        {
            bool isValidInput = false;
            string answer_booking;
            std::cin >> answer_booking;
            while(isValidInput)
            {
                std::cout << std::endl;
                const regex check("[A-Za-z\\s]+$");
                if(std::regex_match(answer_booking,check))
                    isValidInput = true;
                else{
                    rlutil::resetColor();
                    setRed;
                    std::cout << "Hotel name must contain only letter from enlglish alphabeth.Please enter the name again: ";
                    rlutil::resetColor();
                }
                   
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
                    setYellow;
                    std::cout << "You selected hotel -->  ";
                    rlutil::resetColor();
                    setLightGreen;
                    std::cout << h_curr_name << std::endl;
                    rlutil::resetColor();
                    std::cout << std::endl;
                    poss = std::distance<std::vector<Hotel>::iterator>(hotel.begin(), h);
                    answerbooking_global = answer_booking;
                }
            }
            if(!found_hotel){
                setRed;
                std::cout << "There is no hotel with this name in the list with the name - " << answer_booking << std::endl;
                std::cout << "Would you like to enter the hotel name again?(Y/N)"<< std::endl;
                rlutil::resetColor();
                string repeat_ans;
                std::cin >> repeat_ans;
                setLightGreen;
                if(repeat_ans != "Y" && repeat_ans != "y"){
                    repeat_ans_flag = false;
                }else{
                    std::cout << "Please enter here: ";
                    std::cout << std::endl;
                    rlutil::resetColor();
                }
            }
        }
        p_pos = poss;
        p_answer_booking = answerbooking_global;
    }
    int SWITCH::Rooms_Select(int &roomNUM_ans,int &oneBR_rooms , int &twoBR_rooms , int &threeBR_rooms ,  std::vector<Hotel>::iterator h_selected){
        // de adaugat check la numarul de camere
        bool running_while = true;
        bool exit1 = true , exit2 = true , exit3 = true;
        while(running_while)
        {
        bool input_rooms_flag = false;
            while(!input_rooms_flag)
            {
                int roomNum_answer ,roomNum_answer_cpy,roomNum_answer_cpy2 ,single_rooms = 0 , double_rooms = 0 , triple_rooms = 0;
                setCyan;
                std::cout << "How many rooms would you want?" << std::endl;
                while(true){
                    std::cin >> roomNum_answer;
                    if(roomNum_answer != 0 || roomNum_answer > 0)
                        break;
                    setRed;
                    std::cout << "Room number cannot be 0.Please enter again: ";
                    rlutil::resetColor();
                }
                roomNum_answer_cpy = roomNum_answer;
                roomNum_answer_cpy2 = roomNum_answer;
                bool single_rooms_flag = true;
                bool double_rooms_flag = true;
                bool triple_rooms_flag = true;
                while(single_rooms_flag){
                    setRed;
                    string checkNegativeAns;
                    std::cout << "Number of single rooms:";
                    std::cin >> single_rooms;
                    if(single_rooms > h_selected->gethSingleRoom() || single_rooms < 0 ){
                        setRed;
                        std::cout << "There are no more single rooms avalible/You entered a negative value!!" << std::endl;
                        string continue_flag;
                        std::cout << "Would you like to continue?(Y/N)" << std::endl;
                        std::cin >> continue_flag;
                        if(continue_flag != "Y" && continue_flag != "y"){
                            exit1 = false;
                            single_rooms_flag = false;
                            break;
                        }
                        rlutil::resetColor();
                    }
                    if(single_rooms > roomNum_answer){
                        setRed;
                        std::cout << "You selected total of " << roomNum_answer << ". You cannot select this much romms "<< std::endl;
                        string continue_flag;
                        std::cout << "Would you like to modify?(Y/N)" << std::endl;
                        std::cin >> continue_flag;
                        if(continue_flag != "Y" && continue_flag != "y"){
                            single_rooms_flag = false;
                            roomNum_answer = roomNum_answer_cpy;
                        }
                        rlutil::resetColor();
                        checkNegativeAns = continue_flag;
                    }
                oneBR_rooms = single_rooms;
                roomNum_answer -= oneBR_rooms;
                roomNum_answer_cpy = roomNum_answer;
                if(checkNegativeAns == "Y" || checkNegativeAns == "y"){
                    roomNum_answer = roomNum_answer_cpy2;
                    continue;
                }
                else
                    single_rooms_flag = false;
                }
                if(roomNum_answer < 0){
                    setRed ;
                    std::cout << "Negative value of number of total rooms, select again!" << std::endl;
                    break;
                }
                if(roomNum_answer == 0){
                    int x = 0;
                    std::cout << "Number of double rooms: " << x << std::endl;
                    twoBR_rooms = double_rooms;
                    double_rooms_flag = false;
                    triple_rooms_flag = false;
                }
                setLightRed;
                roomNum_answer_cpy = roomNum_answer;
                roomNum_answer_cpy2 = roomNum_answer;
                while(double_rooms_flag){
                    std::cout << std::endl;
                    string checkNegativeAns2;
                    std::cout << "Number of double rooms:";
                    std::cin >> double_rooms;
                    if(double_rooms > h_selected->gethDoubleRoom() || double_rooms < 0){
                        setRed;
                        std::cout << "There are no more double rooms avalible" << std::endl;
                        string continue_flag;
                        std::cout << "Would you like to continue?(Y/N)" << std::endl;
                        std::cin >> continue_flag;
                        if(continue_flag != "Y" && continue_flag != "y"){
                            exit2 = false;
                            double_rooms_flag = false;
                        }
                        rlutil::resetColor();
                    }
                    if(double_rooms > roomNum_answer){
                        setRed;
                        std::cout << "You selected total of/remaining rooms " << roomNum_answer << ". You cannot select this much romms "<< std::endl;
                        string continue_flag;
                        std::cout << "Would you like to modify?(Y/N)" << std::endl;
                        std::cin >> continue_flag;
                        if(continue_flag != "Y" && continue_flag != "y"){
                            double_rooms_flag = false;
                            roomNum_answer = roomNum_answer_cpy;
                        }
                        checkNegativeAns2 = continue_flag;
                        rlutil::resetColor();
                    }
                twoBR_rooms = double_rooms;
                roomNum_answer -= twoBR_rooms;
                roomNum_answer_cpy = roomNum_answer;
                if(checkNegativeAns2 == "Y" || checkNegativeAns2 == "y"){
                    roomNum_answer = roomNum_answer_cpy2;
                    continue;
                }else
                    double_rooms_flag = false;
                }
                if(roomNum_answer < 0){
                    setRed;
                    std::cout << "Negative value of number of total rooms, select again!" << std::endl;
                    break;
                }
                if(roomNum_answer == 0 && !single_rooms_flag && !double_rooms_flag ){
                    int x = 0;
                    std::cout << std::endl;
                    std::cout << "Number of triple rooms: " << x;
                    threeBR_rooms = triple_rooms;
                    triple_rooms_flag = false;
                }
                roomNum_answer_cpy = roomNum_answer;
                roomNum_answer_cpy2 = roomNum_answer;
                while(triple_rooms_flag){
                    std::cout << std::endl;
                    string checkNegativeAns3;
                    std::cout << "Number of triple rooms:";
                    std::cin >> triple_rooms;
                    if(triple_rooms > h_selected->gethTripleRoom() || triple_rooms < 0){
                        setRed;
                        std::cout << "There are no more triple rooms avalible" << std::endl;
                        string continue_flag;
                        std::cout << "Would you like to continue?(Y/N)" << std::endl;
                        std::cin >> continue_flag;
                        if(continue_flag != "Y" && continue_flag != "y"){
                            exit3 = false;
                            triple_rooms_flag = false;
                            break;
                        }
                        rlutil::resetColor();
                    }
                    if(triple_rooms > roomNum_answer){
                        setRed;
                        std::cout << "You selected total of " << roomNum_answer << ". You cannot select this much romms "<< std::endl;
                        string continue_flag;
                        std::cout << "Would you like to modify?(Y/N)" << std::endl;
                        std::cin >> continue_flag;
                        if(continue_flag != "Y" && continue_flag != "y"){
                            triple_rooms_flag = false;
                            roomNum_answer = roomNum_answer_cpy;
                        }
                        checkNegativeAns3 = continue_flag;
                        rlutil::resetColor();
                    }
                threeBR_rooms = triple_rooms;
                roomNum_answer -= threeBR_rooms;
                roomNum_answer_cpy = roomNum_answer;
                if(checkNegativeAns3 == "Y" || checkNegativeAns3 == "y"){
                    roomNum_answer = roomNum_answer_cpy2;
                    continue;
                }else
                    triple_rooms_flag = false;
                }
                if(roomNum_answer < 0){
                    setRed;
                    std::cout << "Negative value of number of total rooms, select again!" << std::endl;
                    break;
                }
                std::cout << std::endl;
                string answer_modifiy;
                setCyan;
                std::cout << std::endl;
                std::cout << "You selected\t\t\n|\t\t\n|\t\t\n|";
                std::cout << "\t\tv\n";
                std::cout << std::endl;
                setYellow;
                std::cout << "*********************" << std::endl;
                std::cout << "One bedroom rooms: " << single_rooms << std::endl;
                std::cout << "Two bedroom rooms: " << double_rooms << std::endl;
                std::cout << "Triple bedroom rooms: " << triple_rooms << std::endl;
                std::cout << "*********************" << std::endl;
                setRed;
                std::cout << "Would you like to modifiy anything?(Y/N)" << std::endl;
                std::cin  >> answer_modifiy;
                setLightGreen;
                if(answer_modifiy != "N" && answer_modifiy != "n"){
                    roomNum_answer = roomNum_answer_cpy;
                    single_rooms = 0;
                    double_rooms = 0;
                    triple_rooms = 0;
                    continue;
                }else{
                    input_rooms_flag = true;
                    running_while = false;
                }
            }
        }
    if(!exit1 || !exit2 || !exit3)
        return 1;
    return 0;                       
    }
    int SWITCH::TotalPAY_and_WAYtoPay(std::vector<Hotel>::iterator h_selected , int& p_Total_PAY , int& p_pay_answer ,int& oneBR_rooms , int& twoBR_rooms , int& threeBR_rooms ){
        p_Total_PAY = (h_selected->gethPriceSingleRoom() * oneBR_rooms) + (h_selected->gethPriceDoubleRoom() * twoBR_rooms) + (h_selected->gethPriceTripleRoom() * threeBR_rooms);
        setLightGreen;
        std::cout << "Total to pay: " << p_Total_PAY << "$" << std::endl;
        bool pay_flag = false;
        setYellow;
        std::cout << "How would you like to pay?" << std::endl;
        setLightGreen;
        std::cout << "****************************" << std::endl;
        std::cout << "1.Pay now for the whole trip : " << p_Total_PAY << "$" << std::endl;
        std::cout << "****************************" << std::endl;
        std::cout << "|\n|\n";
        setLightRed;
        std::cout << "|\n|\n";
        std::cout << "****************************" << std::endl;
        std::cout << "2.Pay '20%' in advance on credit card and the rest on check-in: Card --> " << p_Total_PAY/5 << "$" << " + Cash --> " <<(p_Total_PAY*4)/5 << "$" << std::endl;
        std::cout << "****************************" << std::endl;
        std::cout << "Please enter: " << std::endl;
        setLightGreen;
        bool pay_exit = true;
        int pay_answer;
        while(!pay_flag){
            std::cin >> pay_answer;
            if(pay_answer != 1 && pay_answer != 2){
                setRed;
                std::cout << "Do u wish to continue with the payment?(Y/N).Please enter here:";
                string response;
                std::cin >> response;
                setLightGreen;
                if(response != "Y" && response != "y"){
                    pay_exit = false;
                    break;
                }
            }else
                pay_flag = true;
        }
        if(!pay_exit)
            return 1;
        p_pay_answer = pay_answer;
        rlutil::resetColor();
        return 0;
    }
    int SWITCH::Pay_Card(int &p_Total_PAY , CustomerCard* cardObj , bool& answer_flag , bool &input_flag , bool &cardName_flag , bool & cardNumber_flag ,
    bool& cardExpDate_flag , bool &cardCVV_flag , bool &checkMoney_flag  , bool& printInfo_flag , bool& checkingCardInfo_flag){
        while(answer_flag)
        {
            input_flag = false;
            std::cin >> *cardObj;
            const regex checkName("^[A-Za-z\\s-]+$");
            if(std::regex_match(cardObj->cardGetName(),checkName))
                cardName_flag = true;
            const regex checkCardNumber("^\\d{4}( \\d{4}){3}$");
            if(std::regex_match(cardObj->cardGetCardNumber() , checkCardNumber))
                cardNumber_flag = true;
            const regex checkExpDate("^(0[1-9]|1[0-2])/[0-9]{4}$");
            if(std::regex_match(cardObj->cardGetExpirationDate(),checkExpDate) ){
                if(cardObj->isValidExpirationDate())
                    cardExpDate_flag = true;
            }
            const regex checkCVV("[0-9\\s]{2,3}$");
            string currCVV = cardObj->cardGetCVV();
            if(std::regex_match(currCVV,checkCVV) && (currCVV.size() == 2 || currCVV.size() == 3))
                cardCVV_flag = true;
            if(cardObj->getCardMoney() >= p_Total_PAY || cardObj->getCardMoney() >= (p_Total_PAY)/5)
                checkMoney_flag = true;
            bool money_flag = false;
            if(!checkMoney_flag)
            {
                std::cout << "You do not have the neccesary amount of money to pay for the reservation" << std::endl;
                std::cout << "Would you like the enter another card?(Y/N)";
                string card_answer;
                std::cin >> card_answer;
                if(card_answer != "Y" && card_answer != "y"){
                    answer_flag = false;
                }
            money_flag = true;
            }
            bool confirmation_answer_flag = false , exit_confirmation = false;
            if(cardName_flag  && cardNumber_flag  && cardExpDate_flag  && cardCVV_flag  && checkMoney_flag )
            {
                setLightRed;
                std::cout << "Please enter YES for confirmation or NO to exit: ";
                string confirmation_answer;
                setLightGreen;
                std::cin >> confirmation_answer;
                if(confirmation_answer == "YES" || confirmation_answer == "yes"){
                    setCyan;
                    std::cout << "Please wait....Checking card informations..." << std::endl;
                    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                    input_flag = true;
                    confirmation_answer_flag = true;
                    printInfo_flag = true;
                    checkingCardInfo_flag = true;
                    exit_confirmation = true;
                }
            }
            if(exit_confirmation )
                return 1;
            if(money_flag ){
                confirmation_answer_flag = true;
                input_flag = true;
            }
            if(!confirmation_answer_flag )
                return 2;
            if(!input_flag && !checkingCardInfo_flag )
                setLightRed;
                std::cout << "The data that you entered it's not correct.Please enter it again: " << std::endl;
            if(!answer_flag )
                break;
        }
        return 0;
    }
    void SWITCH::Print_Data(bool &printInfo_flag , CustomerCard *cardObj , int &p_Total_PAY ,
    std::vector<Hotel>::iterator h_selected , std::vector<Customer>& customer,
    string &p_checkinDate ,string &p_checkOutDate , int &p_singleRooms , int &p_doubleRooms , int &p_tripleRooms , const string& currID , std::unordered_map<string , Customer>& customerMap)
    {
        if(printInfo_flag)
        {
            setLightGreen;
            std::cout << "Payment has been done!Enjoy your reservation!" << std::endl;
            setLightRed;
            std::cout << "\t\t---------------- INFORMATIONS ABOUT YOUR RESERVATION ----------------" << std::endl;
            setLightGreen;
            std::cout << "\t\t\t\t--------- RESERVED HOTEL ---------" << std::endl ;
            setYellow;
            std::cout << *h_selected;
            setLightRed;
            std::cout << "\t------Your Info------ " << std::endl;
            setYellow;
            std::cout << "-----------------------------------------------" << std::endl;
            auto it = customerMap.find(currID);
            Customer temp = it->second;
            std::cout << temp;
            setYellow;
            std::cout << "-----------------------------------------------" << std::endl;
            setLightGreen;
            std::cout <<"Check-in date: " << p_checkinDate << "\t" << "Check-out date: " << p_checkOutDate  << std::endl;
            std::cout <<"---------> ONE BEDROOM ROOMS: " << p_singleRooms << std::endl;
            std::cout <<"---------> TWO BEDROOM ROOMS: " << p_doubleRooms << std::endl;
            std::cout <<"---------> THREE BEDROOM ROOMS: " << p_tripleRooms << std::endl;
            std::cout << std::endl;
            std::cout << std::endl;
            setLightRed;
            std::cout <<"Thank you for using our platform!" << std::endl;
            std::cout <<"-----------------------------------------------" << std::endl;
            rlutil::resetColor();
            delete cardObj;
        }else{
            delete cardObj;
        }
            
    }

                                                            // BOOK HOTEL - END
                                                            // ----------------


    bool SWITCH::Answer_Review(){
        setRed;
        std::cout << "Would you like to leave a review?(Yes/No) ---> ";
        bool ans_flag = true;
        string ans_func;
        while(ans_flag){
            try {
                std::cin >> ans_func;
                if(ans_func == "Yes" || ans_func == "No"){
                    ans_flag = false;
                }else {
                    throw std::runtime_error("Incorrect Answer!Enter again --> ");
                }
            }catch (const std::exception& e){
                setRed;
                std::cout << "Error ---> " << e.what() ;
            }
        }
        if(ans_flag)
            return false;
        return true;
    }


    void SWITCH::Post_Review(std::vector<Customer> customer, const char *FILENAME, std::vector<Hotel> &hotel,std::unordered_map<string , City> cities ,const string& currID) {
    std::ofstream inputReview (FILENAME ,std::ios::app);
    try {
        if(!inputReview.is_open()) {
            setRed;
            throw std::runtime_error("FILE could not be opened");
        }
    }catch (const std::exception& e){
        std::cout << "ERROR --> " << e.what() << std::endl;
    }
    auto current_account = std::make_shared<Customer>();
    for(auto& customer_it : customer){
        if(customer_it.getID() == currID){
            current_account = std::make_shared<Customer>(customer_it);
            break;
        }
    }
    setYellow;
    for(auto &city : cities)
        std::cout << "------------ " << city.second.getName() << " ------------"<< std::endl;
    std::cout << "Select the city that hotel is in --> " ;
    string ans;
    bool city_flag = true;
    while(city_flag){
        try{
            std::cin.clear();
            std::cin >>  ans;
            if(cities.find(ans) == cities.end()){
                throw std::runtime_error("Invalid input. City is not in the out list!");
                std::cout << "\n";
            }else {
                setLightGreen;
                std::cout << "**** VALID CITY ENTERED ****" << std::endl;
                city_flag = false;
            }
        }catch (std::exception& e){
            std::cout << "Error --> " << e.what() << std::endl;
            setLightGreen;
            std::cout << "Enter again --> ";
        }
    }
    std::cout << "Our sistem is working...Please wait...Thank you" << std::endl;
    std::cout << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    setLightGreen;
    std::cout << "\t\t\tHOTELS IN " << ans << std::endl;
    std::cout << "\t\t------------------------------------"<<  std::endl;
    rlutil::resetColor();
    setYellow;
    int no_hotel = 0;
    for(auto h = hotel.begin(); h != hotel.end(); ++h){
        string h_copy_name = h->gethCity();
        if(ans == h_copy_name){
            std::cout <<"\t   Hotel " << ++no_hotel << std::endl;
            std::cout << "-----------------------------------------------------------" << std::endl;
            std::cout << *h;
            std::cout << "-----------------------------------------------------------"  << std::endl;
        }
    }
    string ans_hotel;
    bool ans_hotel_flag = true;
    setYellow;
    std::cout << "Enter hotel name --> ";
    while(ans_hotel_flag){
        try{
            std::cin >> ans_hotel;
            for(auto &h : hotel){
                if(ans_hotel == h.gethName()){
                    setLightGreen;
                    std::cout << "**** VALID HOTEL ENTERED ****" << std::endl;
                    ans_hotel_flag = false;
                }
            }
            if(ans_hotel_flag) {
                throw std::runtime_error("Invalid input.Hotel not in the list or missing letters.");
                std::cout << "\n";
            }
        }catch (std::exception& e){
            std::cout << "Error --> " << e.what() << std::endl;
            setLightGreen;
            std::cout << "Enter again --> ";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    auto hotel_iterator = std::find_if(hotel.begin(), hotel.end(), [&](const Hotel& h) {
        return h.gethName() == ans_hotel;
    });
    if(hotel_iterator != hotel.end()) {
        std::cout << "************* You selected hotel *************  \n";
        std::cout << *(hotel_iterator);
    }

    std::cout << "\n\n";
    //PRINTING REVIEWS
    hotel_iterator->PrintHotelReviews();
    // printing reviews
    setYellow;
    string ans_review;
    bool ans_review_flag = true;
    std::cout << "Would you like your review to be anonymous? (Yes/No) ---> ";
    while(ans_review_flag){
        try{
            std::cin >> ans_review;
            if(ans_review == "Yes" || ans_review == "No"){
                setLightGreen;
                std::cout << "*** VALID ANSWER ENTERED ***" << std::endl;
                ans_review_flag = false;
            }else {
                throw std::runtime_error("Invalid answer!");
                std::cout << "\n";
            }
        }catch (std::exception& e){
            setRed;
            std::cout << "Error --> " << e.what() << std::endl;
            setLightGreen;
            std::cout << "Enter again --> ";
        }
    }
    if(ans_review == "Yes"){
        std::shared_ptr<Review> new_review = std::make_shared<AnonymReview>();
        try{
            auto anonym_rev = std::dynamic_pointer_cast<AnonymReview>(new_review);
            if(anonym_rev == nullptr){
                throw std::runtime_error("Error when converting pointer") ;
            }
            anonym_rev->setCustomer(current_account);
            anonym_rev->ReadReview();
            auto& current_hotel_vec = hotel_iterator->getVectorReviewPtr();
            current_hotel_vec.push_back(anonym_rev);
            std::cout << "EMPTY :"<< hotel_iterator->getVectorReviewPtr().empty() << std::endl;
            setLightGreen;
            std::cout << "***************************************" << std::endl;
            std::cout << "REVIEW ADDED SUCCESSFULLY" << std::endl;
            std::cout << "***************************************" << std::endl;
            rlutil::resetColor();
            inputReview << "***Anonymous***" << "\n";
            inputReview << "ReviewID--> " << anonym_rev->getReviewId() << "\n";
            inputReview << "Hotel-Name--> " << hotel_iterator->gethName() << "\n";
            inputReview << "AnonymousID--> " << anonym_rev->getAnonymId() << "\n";
            inputReview << "Rating--> " << anonym_rev->getStars() << "\n";
            inputReview << "Review--> " << anonym_rev->getReview() << "\n";
            inputReview << "Recommended--> " << anonym_rev->getRecomendOrNot() << "\n";
            inputReview << "\n\n";

        }catch (std::exception& e){
            setRed;
            std::cout << "Error --> " << e.what() << std::endl;
        }
    }else{
        setLightGreen;
        std::cout << "Did you like your staying at our hotel?(Yes/No) --> ";
        bool ans_flag2 = true;
        string ans2;
        while(ans_flag2)
        {
            try{
                std::cin >> ans2;
                if(ans2 == "Yes" || ans2 == "No"){
                    setLightGreen;
                    std::cout << "*** VALID ANSWER ENTERED ***" << std::endl;
                    ans_flag2 = false;
                }else {
                    throw std::runtime_error("Invalid answer!");
                    std::cout << "\n";
                }
            }catch (std::exception& e){
                setRed;
                std::cout << "Error --> " << e.what() << std::endl;
                setLightGreen;
                std::cout << "Enter again --> ";
            }
        }
        if(ans2 == "Yes"){
            std::shared_ptr<Review> new_review = std::make_shared<PositiveReviews>();
            try{
                auto positive_rev = std::dynamic_pointer_cast<PositiveReviews>(new_review);
                if(positive_rev == nullptr){
                    throw std::runtime_error("Error when converting pointer") ;
                }
                positive_rev->setCustomer(current_account);
                positive_rev->ReadReview();
                auto& current_hotel_vec = hotel_iterator->getVectorReviewPtr();
                current_hotel_vec.push_back(positive_rev);
                setLightGreen;
                std::cout << "***************************************" << std::endl;
                std::cout << "REVIEW ADDED SUCCESSFULLY" << std::endl;
                std::cout << "***************************************" << std::endl;
                rlutil::resetColor();
                inputReview << "***Positive***" << "\n";
                inputReview << "ReviewID--> " << positive_rev->getReviewId() << "\n";
                inputReview << "Hotel-Name--> " << hotel_iterator->gethName() << "\n";
                inputReview << "CustomerID--> " << positive_rev->getCustomer()->getID() << "\n";
                inputReview << "Rating--> " << positive_rev->getStars() << "\n";
                inputReview << "Review--> " << positive_rev->getReview() << "\n";
                inputReview << "Recommended--> " << positive_rev->getRecommended() << "\n";
                inputReview << "\n\n";

            }catch (std::exception& e){
                setRed;
                std::cout << "Error --> " << e.what() << std::endl;
            }
        }else{
            std::shared_ptr<Review> new_review = std::make_shared<NegativeReviews>();
            try{
                auto negative_rev = std::dynamic_pointer_cast<NegativeReviews>(new_review);
                if(negative_rev == nullptr){
                    throw std::runtime_error("Error when converting pointer") ;
                }
                negative_rev->setCustomer(current_account);
                negative_rev->ReadReview();
                auto& current_hotel_vec = hotel_iterator->getVectorReviewPtr();
                current_hotel_vec.push_back(negative_rev);
                setLightGreen;
                std::cout << "***************************************" << std::endl;
                std::cout << "REVIEW ADDED SUCCESSFULLY" << std::endl;
                std::cout << "***************************************" << std::endl;
                rlutil::resetColor();
                inputReview << "***Negative***" << "\n";
                inputReview << "ReviewID--> " << negative_rev->getReviewId() << "\n";
                inputReview << "Hotel-Name--> " << hotel_iterator->gethName() << "\n";
                inputReview << "CustomerID--> " << negative_rev->getCustomer()->getID() << "\n";
                inputReview << "Rating--> " << negative_rev->getStars() << "\n";
                inputReview << "Review--> " << negative_rev->getReview() << "\n";
                inputReview << "Not-Recommended--> " << negative_rev->getNOTrecomended() << "\n";
                inputReview << "\n\n";
            }catch (std::exception& e){
                setRed;
                std::cout << "Error --> " << e.what() << std::endl;
            }
        }
    }
    inputReview.close();
}