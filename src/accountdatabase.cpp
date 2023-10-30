#include "accountdatabase.h"

    std::unordered_map<string,string> AccountDataBase::getPass_Map(){
        return pass_map;
    }
    // FUNCTIONS FOR LOGIN MENU
    //--------------
    //--------------
                                                    // ---REGISTER FUNC-----
                                                    // --????--????--
                                                    // --????--????--
    void AccountDataBase::ReadingFromRecordsIntoPassMap(const char* FILENAME){
        string id_records , password_records;
        std::ifstream filein(FILENAME);
        if(filein.is_open() == false){
            std::cerr << FILENAME << " could not be opened" << std::endl;
        }
        while(filein >> id_records >> password_records){
            pass_map[id_records] = password_records;
        }
        filein.close();
    }
    int AccountDataBase::Register(const char* FILENAME){
        std::cout << "Would you like to make a new account?(Y/N)";
        bool exit_flag = true;
        while(exit_flag == true){
            string answer;
            std::cin >> answer;
            if(answer == "Y" || answer == "y"){
                exit_flag = false;
            }
            if(exit_flag == true)
                break;
        }
        if(exit_flag == true){
            std::cout << "Exiting option" << std::endl;
            return 1;
        }
        std::ofstream fileout(FILENAME, std::ios::app);
        if(fileout.is_open() == 0){
            std::cerr << "File that contains the records could not be opened" << std::endl;
            return 1;
        }
        string id, password;
        std::cout << "ENTER THE NAME THAT YOU WILL LOGIN WITH " << std::endl;
        std::cout << "---------------------------------------" << std::endl;
        std::cout << "\t\tName requirements" << std::endl;
        std::cout << "---------------------------------------" << std::endl;
        std::cout << "-> Name cannot contain special characters" << std::endl;
        std::cout << "-> Must be in the range of 16 characters(lowercase/uppercase letter and numbers only" << std::endl;
        std::cout << "ENTER --------> ";
        bool exit_id_flag = true , exit_id_flag2 = true;
        while(exit_id_flag == true && exit_id_flag2 == true){
            std::cin >> id;
            const regex checkID("^[a-zA-Z0-9_]{8,}$");
            if(std::regex_match(id , checkID))
                exit_id_flag = false;
            else
                std::cout << "Name must be in the range of 16 character and it cannot contain special characters.Please enter another ID ---> " << std::endl;
            if(pass_map.find(id) == pass_map.end())
                exit_id_flag2 = false;
            else
                std::cout << "Name already exists. Please enter another ID ---> " ;
        }
        std::cout << "---------------------------------------------------------" << std::endl;
        std::cout << "EMTER THE PASSWORD THAT YOU WILL LOGIN WITH" << std::endl;
        std::cout << "---------------------------------------" << std::endl;
        std::cout << "\t\tPassword requirements" << std::endl;
        std::cout << "---------------------------------------" << std::endl;
        std::cout << "-> Password must contain at least one uppercase letter" << std::endl;
        std::cout << "-> Password must contain at least one lowercase letter" << std::endl;
        std::cout << "-> Password must contain at least one number" << std::endl;
        std::cout << "-> Password must contain at least one special character" << std::endl;
        bool exit_password_flag = true;
        while(exit_password_flag == true){
            std::cin >> password;
            const regex checkPassword("(?=.*[!@#$%^&*()_+\\-=[\\]{};':\"\\\\|,.<>\\/?])(?=.*[A-Z])(?=.*[a-z])(?=.*[0-9]).{8,}$");
            if(std::regex_match(password , checkPassword))
                exit_password_flag = false;
            else
                std::cout << "You must respect all the requirements from above.Please enter anothed password ---> ";
        }
        std::cout << "Account created succesfuly" << std::endl;
        fileout << id << " " << password << std::endl;
        fileout.close();
        return 0;
    }
                                                // --????--????-- END
                                                // --????--????-- END


                                                    //--??--??-- forgotPASSWORD funcions
                                                    //--??--??-- forgotPASSWORD funcions
    int AccountDataBase::ReadFromFileInVector(const char *FILENAME , std::vector<Account> & acc_vec){
        string id, pass;
        std::ifstream file_in (FILENAME);
            if(file_in.is_open() == 0){
                std::cerr << "File could not be opened < " << FILENAME << " >" << std::endl;
                return 0;
            }
        while(file_in >> id >> pass){
            Account acc_temp;
            acc_temp.setId(id);
            acc_temp.setPass(pass);
            acc_vec.push_back(acc_temp);
        }
        file_in.clear();
        file_in.close();
        return 1;
    }
    void AccountDataBase::ReplacingPasswordInVec(std::vector<Account> & acc_vec , std::unordered_map<string,string>::iterator it){
        string account_id = it->first;
        for(auto &acc_it : acc_vec){
            if(acc_it.getId() == account_id){
                acc_it.setPass(it->second);
            }
        }
    }
    int AccountDataBase::WritingVecBackToFile(const char* FILENAME , std::vector<Account> & acc){
        std::ofstream file_out (FILENAME);
        if(file_out.is_open() == 0){
            std::cerr << "File could not be opened < " << FILENAME << " >" << std::endl;
            return 0;
        }
        for(auto & acc_it : acc){
            file_out << acc_it.getId() << " " << acc_it.getPass();
        }
        file_out.close();
        return 1;
    }
    void AccountDataBase::Free_vec(std::vector<Account>& acc_vec){
        acc_vec.clear();
    }
    int AccountDataBase::ForgotPassword(const char* FILENAME){
        bool running = true;
        std::unordered_map<string , string>::iterator it;
        while(running == true)
        {
            std::cout << "Forgot password?(Y/N) " << std::endl;
            string answer;
            std::cin >> answer;
            if(answer == "N" || answer == "n")
               return 0;
            string name_to_search;
            std::cout << "Please enter the name of the account " << std::endl;
            std::cin >> name_to_search;
            if(pass_map.find(name_to_search) == pass_map.end()){
                std::cout << "There is no account with the name " << name_to_search << std::endl;
                string answer2;
                std::cout << "Would you like to enter the name again?(Y/N) " << std::endl;
                std::cin >> answer2;
                if(answer2 == "N" || answer2 == "n")
                    return 0;
                break;
            }else{
                it = pass_map.find(name_to_search);
                std::cout << "Account found!" << std::endl;
                string new_password;
                std::cout << "Please enter the new password: " << std::endl;
                std::cout << "---------------------------------------" << std::endl;
                std::cout << "\t\tPassword requirements" << std::endl;
                std::cout << "---------------------------------------" << std::endl;
                std::cout << "-> Password must contain at least one uppercase letter" << std::endl;
                std::cout << "-> Password must contain at least one lowercase letter" << std::endl;
                std::cout << "-> Password must contain at least one number" << std::endl;
                std::cout << "-> Password must contain at least one special character" << std::endl;
                bool exit_password_flag = true;
                while(exit_password_flag == true){
                    std::cin >> new_password;
                    const regex checkPassword("(?=.*[!@#$%^&*()_+\\-=[\\]{};':\"\\\\|,.<>\\/?])(?=.*[A-Z])(?=.*[a-z])(?=.*[0-9]).{8,}$");
                    if(std::regex_match(new_password , checkPassword))
                        exit_password_flag = false;
                    else
                        std::cout << "You must respect all the requirements from above.Please enter anothed password ---> ";
                }
                // replacing the old password with the new one in map
                string old_pass = it->second;
                string id, pass  , account_id;
                it->second = new_password;
                account_id = it->first;
                std::vector<Account> acc_vec;
                // in file
                ReadFromFileInVector("records.txt", acc_vec);
                ReplacingPasswordInVec(acc_vec , it);
                int ret2 = WritingVecBackToFile("records.txt" , acc_vec);
                if(ret2 == 0){
                    std::cout << " PROBLEM WHEN WRITING VEC BACK TO FILE " << std::endl;
                    return 0;
                }
                pass_map[account_id] = it->second;
                std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                std::cout << "Password renewed succefuly" << std::endl;
                std::cout << " --------------------------- " << std::endl;
                std::cout << " --------------------------- " << std::endl;
                Free_vec(acc_vec);
                running = false;
            }
        }
        return 1;
    }
                                                    //--??--??-- END forgotPASSWORD functions
                                                    //--??--??-- END forgotPASSWORD functions
    
                                                        //----LOGIN FUNC-----
                                                        //----------
                                                        //----------
    int AccountDataBase::Login(const char* FILENAME , string* p_curr_id)
    {
        bool running = true;
        ReadingFromRecordsIntoPassMap("records.txt");
        while(running == true){
            string login_id, login_pass;
            std::cout << "Name: ";
            std::cin >> login_id;
            std::cout << "Password: ";
            std::cin >> login_pass;
            bool find_id = false , find_pass = false;
            if(pass_map.find(login_id) != pass_map.end()){
                find_id = true;
                auto it = pass_map.find(login_id);
                if(it->second == login_pass)
                    find_pass = true;
            }
            if(find_id == true && find_pass == true){
                std::ofstream fileout (FILENAME , std::ios::app);
                if(fileout.is_open() == 0){
                    std::cerr << FILENAME << " couldn't open" << std::endl;
                    return 0;
                }
                string TOKEN = generateUniqueToken(login_id , login_pass);
                fileout << login_id << " " << login_pass << " " << TOKEN << std::endl;
                fileout.close();
                std::cout << "Welcome " << login_id << ". We are happy that you choose to use our system! Have a good day!" << std::endl;
                *p_curr_id = login_id;
                return 1;
            }else{
                std::cout << "Name or password is incorrect. Would you like to entering the name and password again?(Y/N) " << std::endl;
                string ans;
                std::cin >> ans;
                if(ans == "N" || ans == "n"){
                    running = false;
                    break;
                }
                std::cout << "----------------------" << std::endl;

            }
        }
        return 0;
    }

                                                        //-----END LOG FUNC--------
                                                        //-----END LOG FUNC--------

                                                        // ---------------------------------------
                                                        // ---------------------------------------
                                                        // CUSTOM FUNCTION GENERATING A UNIQUE TOKEN ON LOGIN THAT CHANGES VALUE
    string AccountDataBase::createLastPartOfToken(){
        Menu m;
        string currTime = m.currentDateTime(); // 2023-07-16.16:02:46
                                            // 0123 4 56 7 89 10(.) HH(1112) 13(:) MM(1415) 16(:) SS(17-18) 
        string Hours , Minutes , Seconds , LastPartOfToken;
        Hours = currTime.substr(11,12);
        Minutes = currTime.substr(14,15);
        Seconds = currTime.substr(17,18);
        LastPartOfToken = Hours + Minutes + Seconds;
        return LastPartOfToken;
    }
    void AccountDataBase::ID_PASSWORD_CRYPT(string *p_id , string *p_password){
        string copy_id , copy_password;
        copy_id = *p_id;
        copy_password = *p_password;
        for(auto it = copy_id.begin() ; it != copy_id.end() ; ++it ){
           char shifted_char = (*it) + '3';
           if(shifted_char > 'z'){
                shifted_char = 'a' + (shifted_char - 'z' - 1) % 26;
           }
            (*it) = shifted_char;
        }
        for(auto it2 = copy_password.begin() ; it2  != copy_password.end(); ++it2){
           char shifted_char = (*it2) + '3';
           if(shifted_char > 'z'){
                shifted_char = 'a' + (shifted_char - 'z' - 1) % 26;
           }
           (*it2) = shifted_char;
        }
        *p_id = copy_id;
        *p_password = copy_password;
    }
    string AccountDataBase::generateUniqueToken(string id , string password){
        string copy_id , copy_password;
        copy_id = id;
        copy_password = password;
        string lastPartOfToken = createLastPartOfToken();
        string token;
        ID_PASSWORD_CRYPT(&copy_id , &copy_password);
        token = copy_id + copy_password + lastPartOfToken;
        return token;
    }
                                            // -------END criptyng func-------
                                            //---------END criptyng func------
    long long currentTime(){
        auto currTime = std::chrono::system_clock::now();
        std::time_t currTime_seconds = std::chrono::system_clock::to_time_t(currTime);
        std::time_t currTime_minutes = currTime_seconds / 60;
        return currTime_minutes;
    }

