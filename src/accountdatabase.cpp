#include "accountdatabase.h"
#include "../rlutil/rlutil.h"
#include "termios.h"

#define setYellow rlutil::setColor(rlutil::YELLOW)
#define setLightRed rlutil::setColor(rlutil::LIGHTRED)
#define setLightGreen rlutil::setColor(rlutil::GREEN)
#define setRed rlutil::setColor(rlutil::RED)
    

    // FUNCTIONS FOR LOGIN MENU
    //--------------
    //--------------

    // PASSWORD ENCRYPTION
    string AccountDataBase::SHA256(const std::string &input) {
    digestpp::sha256 HASH;
    HASH.absorb(input);
    string hashedInput = HASH.hexdigest();
    return hashedInput;
    }
    // -------------------

                                                    // ---REGISTER FUNC-----
                                                    // --????--????--
                                                    // --????--????--
    void AccountDataBase::ReadingFromRecordsIntoPassMap(const char* FILENAME){
        string id_records , password_records;
        std::ifstream filein(FILENAME);
        if(!filein.is_open()){
            std::cerr << FILENAME << " could not be opened" << std::endl;
        }
        while(filein >> id_records >> password_records){
            pass_map[id_records] = password_records;
        }
        filein.close();
    }
    int AccountDataBase::Register(const char* FILENAME){
        setLightGreen;
        std::cout << "Would you like to make a new account?(Y/N)";
        rlutil::resetColor();
        bool exit_flag = true;
        while(exit_flag){
            string answer;
            std::cin >> answer;
            if(answer == "Y" || answer == "y"){
                exit_flag = false;
            }
            if(exit_flag)
                break;
        }
        if(exit_flag){
            std::cout << "Exiting option" << std::endl;
            return 1;
        }
        std::ofstream fileout(FILENAME, std::ios::app);
        if(fileout.is_open() == 0){
            std::cerr << "File that contains the records could not be opened" << std::endl;
            return 1;
        }
        string id, password;
        setLightRed;
        std::cout << "---------------------------------------" << std::endl;
        std::cout << "\t\tName requirements" << std::endl;
        std::cout << "---------------------------------------" << std::endl;
        std::cout << "-> Name cannot contain special characters" << std::endl;
        std::cout << "-> Must be in the range of 16 characters(lowercase/uppercase letter and numbers only" << std::endl;
        std::cout << "ENTER --------> ";
        rlutil::resetColor();
        bool exit_id_flag = true , exit_id_flag2 = true;
        while(exit_id_flag && exit_id_flag2){
            std::cin >> id;
            const regex checkID("^[a-zA-Z0-9_]{8,}$");
            if(std::regex_match(id , checkID))
                exit_id_flag = false;
            else{
                setRed;
                std::cout << "Name must be in the range of 16 character and it cannot contain special characters.Please enter another ID ---> " << std::endl;
                rlutil::resetColor();
            }
            if(pass_map.find(id) == pass_map.end())
                exit_id_flag2 = false;
            else{
                setRed;
                std::cout << "Name already exists. Please enter another ID ---> " ;
                rlutil::resetColor();
            }
        }
        setRed;
        std::cout << "---------------------------------------------------------" << std::endl;
        std::cout << "\t\t\t\t\tPassword requirements" << std::endl;
        std::cout << "---------------------------------------------------------" << std::endl;
        std::cout << "-> Password must contain at least one uppercase letter" << std::endl;
        std::cout << "-> Password must contain at least one lowercase letter" << std::endl;
        std::cout << "-> Password must contain at least one number" << std::endl;
        std::cout << "-> Password must contain at least one special character" << std::endl;
        std::cout << "ENTER --------> ";
        rlutil::resetColor();
        bool exit_password_flag = true;
        while(exit_password_flag){
            std::cin >> password;
            const regex checkPassword("(?=.*[!@#$%^&*()_+\\-=[\\]{};':\"\\\\|,.<>\\/?])(?=.*[A-Z])(?=.*[a-z])(?=.*[0-9]).{8,}$");
            if(std::regex_match(password , checkPassword))
                exit_password_flag = false;
            else
            {
                setRed;
                std::cout << "You must respect all the requirements from above.Please enter anothed password ---> ";
                rlutil::resetColor();
            }
        }
        setLightGreen;
        std::cout << "Account created succesfuly" << std::endl;
        rlutil::resetColor();
        string passwordStored = SHA256(password);
        std::cout << "passwordStored on register " << passwordStored << std::endl;
        fileout << id << " " << passwordStored << std::endl;
        fileout.close();
        return 0;
    }
                                                // --????--????-- END
                                                // --????--????-- END


                                                    //--??--??-- forgotPASSWORD funcitons
                                                    //--??--??-- forgotPASSWORD functions
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
            file_out << acc_it.getId() << " " << acc_it.getPass() << std::endl;
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
        while(running)
        {
            setRed;
            std::cout << "Forgot password?(Y/N) " << std::endl;
            string answer;
            setLightGreen;
            std::cin >> answer;
            if(answer == "N" || answer == "n")
               return 0;
            string name_to_search;
            setYellow;
            std::cout << "Please enter the name of the account " << std::endl;
            setRed;
            std::cin >> name_to_search;
            if(pass_map.find(name_to_search) == pass_map.end()){
                setRed;
                std::cout << "There is no account with the name " << name_to_search << std::endl;
                string answer2;
                std::cout << "Would you like to enter the name again?(Y/N) " << std::endl;
                setLightGreen;
                std::cin >> answer2;
                if(answer2 == "N" || answer2 == "n")
                    return 0;
                break;
            }else{
                it = pass_map.find(name_to_search);
                setLightGreen;
                std::cout << "Account found!" << std::endl;
                string new_password;
                setRed;
                std::cout << "---------------------------------------------------------" << std::endl;
                std::cout << "\t\t\t\t\tPassword requirements" << std::endl;
                std::cout << "---------------------------------------------------------" << std::endl;
                std::cout << "-> Password must contain at least one uppercase letter" << std::endl;
                std::cout << "-> Password must contain at least one lowercase letter" << std::endl;
                std::cout << "-> Password must contain at least one number" << std::endl;
                std::cout << "-> Password must contain at least one special character" << std::endl;
                std::cout << "ENTER NEW PASSWORD --------> ";
                rlutil::resetColor();
                bool exit_password_flag = true;
                while(exit_password_flag){
                    std::cin >> new_password;
                    const regex checkPassword("(?=.*[!@#$%^&*()_+\\-=[\\]{};':\"\\\\|,.<>\\/?])(?=.*[A-Z])(?=.*[a-z])(?=.*[0-9]).{8,}$");
                    if(std::regex_match(new_password , checkPassword))
                        exit_password_flag = false;
                    else
                        std::cout << "You must respect all the requirements from above.Please enter another password ---> ";
                }
                // replacing the old password with the new one in map
                string  account_id;
                string newPasswordHashed = SHA256(new_password);
                it->second = newPasswordHashed;;
                account_id = it->first;
                std::vector<Account> acc_vec;
                // in file
                ReadFromFileInVector(FILENAME, acc_vec);
                ReplacingPasswordInVec(acc_vec , it);
                int ret2 = WritingVecBackToFile(FILENAME , acc_vec);
                if(ret2 == 0){
                    std::cout << " PROBLEM WHEN WRITING VEC BACK TO FILE " << std::endl;
                    return 0;
                }
                pass_map[account_id] = it->second;
                std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                setLightGreen;
                std::cout << "Password renewed succefuly" << std::endl;
                std::cout << " --------------------------- " << std::endl;
                std::cout << " --------------------------- " << std::endl;
                rlutil::resetColor();
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
    int AccountDataBase::Login(const char* FILENAME , string& p_curr_id)
    {
        bool running = true;
        ReadingFromRecordsIntoPassMap("records.txt");
//        for(auto& it: pass_map){
//            std::cout << "ID: " << it.first << std::endl;
//            std::cout << "PASS: " << it.second << std::endl;
//        }
        while(running){
            string login_id, login_pass;
            char ch = '\0';
            setLightGreen;
            std::cout << "Name: ";
            rlutil::resetColor();
            std::cin >> login_id;
            setLightRed;
            std::cout << "Password:";
            rlutil::resetColor();
            struct termios oldt, newt;
            tcgetattr(STDIN_FILENO, &oldt);
            newt = oldt;
            newt.c_lflag &= ~ECHO;
            tcsetattr(STDIN_FILENO, TCSANOW, &newt);
            // Read the password character by character
            std::cin.ignore(1, '\n');
            login_pass = "";
            while (ch != '\n') {
                ch = std::cin.get();
                if(ch != '\n'){
                    std::cout << '*'; // Print an asterisk for each character
                    login_pass += ch;
                }
            }
            tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
            std::cout << std::endl; 
            bool find_id = false , find_pass = false , isAuthenticated = true;
            string passwordHashed = SHA256(login_pass);
            Menu m;
            if(pass_map.find(login_id) != pass_map.end()){
                find_id = true;
                auto it = pass_map.find(login_id);
                if(it->second == passwordHashed) {
                    find_pass = true;
                }
            }
            if(find_id && find_pass){
                isAuthenticated = true;
                m.SpinnerInTerminal(isAuthenticated);
                std::ofstream fileout (FILENAME , std::ios::app);
                if(fileout.is_open() == 0){
                    std::cerr << FILENAME << " couldn't open" << std::endl;
                    return 0;
                }
                fileout << login_id << " " << passwordHashed << " " << Menu::currentDateTime() << std::endl;
                fileout.close();
                setLightGreen;
                std::cout << "Welcome " << login_id << ". We are happy that you choose to use our system! Have a good day!" << std::endl;
                rlutil::resetColor();
                p_curr_id = login_id;
                return 1;
            }else{
                isAuthenticated = false;
                m.SpinnerInTerminal(isAuthenticated);
                setLightRed;
                std::cout << "Name or password is incorrect. Would you like to entering the name and password again?(Y/N) " << std::endl;
                rlutil::resetColor();
                string ans;
                setLightGreen;
                std::cin >> ans;
                rlutil::resetColor();
                // DE ADAUGAT IN  ASA FEL INCAT ATUNCI CAND RASPUNSUL ESTE NU SA TE INTOARCA INAPOI LA MENIU
                if(ans == "N" || ans == "n"){
                    return 0;
                }
                if(ans == "Y" || ans == "y")
                    continue;
                std::cout << "----------------------" << std::endl;

            }
        }
        return 0;
    }

                                                        //-----END LOG FUNC--------
                                                        //-----END LOG FUNC--------


