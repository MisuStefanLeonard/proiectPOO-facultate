#include "customer.h"

    void Customer::setID(string id){
        ID = id;
    }
    string Customer::getID(){
        return ID;
    }
    void Customer::setName(string name){
        Name = name;
    }
    string Customer::getName(){
        return Name;
    }
    void Customer::setPrename(string prename){
        Prename = prename;
    }
    string Customer::getPrename(){
        return Prename;
    }
    void Customer::setAge(int age){
        Age = age;
    }
    int Customer::getAge(){
        return Age;
    }
    void Customer::setSex(char sex){
        Sex = sex;
    }
    char Customer::getSex(){
        return Sex;
    }
    void Customer::setMoney(int money){
        Money = money;
    }
    int Customer::getMoney(){
        return Money;
    }
    void Customer::setAdult(bool adult){
        Adult = adult;
    }
    bool Customer::getAdult(){
        return Adult;
    }
    void Customer::setNumber(int number){
        Number.clear();
        while(number<=9){
            int last_digit = number%10;
            Number.push_back(last_digit);
            number = number/10;
        }
        Number.push_back(number);
        
    }
    std::vector<int> Customer::getNumber(){
        return Number;
    }
    void Customer::setCNP(string cnp){
        CNP = cnp;
    }
    string Customer::getCNP(){
        return CNP;
    }
    void Customer::setEmail(string email){
        Email = email;
    }
    string Customer::getEmail(){
        return Email;
    }
    bool Customer::checkName(){
        int i = 0 ;
        // 65 - 122
        for(i = 0 ; i < Name.size();i++){
            if(isalpha(Name[i]) == 0){
                std::cout << "Name must contain only letters from english alphabeth" << std::endl;
                return false;
            }
        }
        return true;
    }
    bool Customer::checkPrename(){
        int i = 0 ;
        // 65 - 122
        for(i = 0 ; i < Prename.size();i++){
            if(isalpha(Prename[i]) == 0){
                std::cout << "Prename must contain only letters from english alphabeth" << std::endl;
                return false;
            }
        }
        return true;
    }
    bool Customer::checkAge(){
    if(Age >= 0 && Age <= 200)
        return true; 
    return false;
    }
    bool Customer::checkAdult(){
        if(Adult == 0)
            return false;
        return true;
    }
    bool Customer::checkMoney(){
        if(Money < 0)
            return false;
        return true;
    }
    bool Customer::checkCNP(){
        auto it = CNP.begin();
        for(it = CNP.begin(); it != CNP.end() ; ++it){
            if(isdigit((*it)) == true)
                continue;
            else
                return false;
        }
        return true;
    }
    bool Customer::checkEmailAddres(){
        const regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
        if(std::regex_match(Email,pattern) == true)
            return true;
        return false;
        
        
    }
    void Customer::Read(){
        std::cout << "Your name : " << std::endl;
        while(true){
            std::cin >> Name;
            if(checkName() == true)
                break;
            std::cout << "Please enter your name again:";
        }
        std::cout << "Your prename : " << std::endl;
        while(true){
            std::cin >> Prename;
            if(checkPrename() == true)
                 break;
            std::cout << "Please enter your prename again: ";
        }
        std::cout << "Your age(only digits):" << std::endl;
        while (true) {
            std::cin >> Age;
            if (std::cin.fail()) {
                std::cout << "Age must be a number. Please enter your age again: " << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }else{
                if (checkAge() == true)
                    break;
                std::cout << "Invalid age. Please enter your age again: " << std::endl;
            }
}

        std::cout << "Your sex(M(male) , F(female): " << std::endl;
        while(true){
            std::cin >> Sex;
            if(Sex == 'M' || Sex == 'F')
                break;
            if(Sex == 'm' || Sex == 'f'){
               toupper(Sex);
               break;
            }
        }
        std::cout << "How much money are you willing to spend on the reservation ? Please enter the amount here($) : " << std::endl;
        while (true) {
            std::cin >> Money;
            if(std::cin.fail()){
                std::cout << "Money must be a number. Please enter your money again: ";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }else{ 
                if(checkMoney() == true)
                    break;
                std::cout << "Money cannot be a negative number.Please enter the amount again: ";
            }
                
        }
        if(Age >= 18)
            Adult = 1;
        else    
            Adult = 0;
        std::cout << "Please enter your phone number(9 digits starting with the digit after 0): " << std::endl;
        int number;
        while(true){
        std::cin >> number;
        if(std::cin.fail()){
            std::cout << "Phone number must contain only digits.";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout<<" Please enter the phone number again: " << std::endl;
        }else
            break;
        }
        while(number<=9){
            int last = number%10;
            Number.push_back(last);
            number = number/10;
        }
        Number.push_back(number);
        std::cout << "Please enter your CNP(only digits) :"  << std::endl;;
        while(true){
            std::cin >> CNP;
            if(checkCNP() == true)
                break;
            else
                std::cout << "CNP must contain only digits.Please enter your CNP again:";
        }
        std::cout << "Please enter your E-mail addres : ";
        while(true){
        std::cin >> Email;
        if(checkEmailAddres() == true)
            break;
        else
        std::cout << "Please enter a valid E-mail addres: ";
        }
    }
    void Customer::Print(){
        std::cout << "Account username: " << ID << std::endl;
        std::cout << "Name:" << Name << std::endl;
        std::cout << "Prename:" << Prename << std::endl;
        std::cout << "Age:" << Age << std::endl;
        std::cout << "Sex:" << Sex << std::endl;
        std::cout << "Money:" << Money << "$"<< std::endl;
        std::cout << "Adult:";
        if(checkAdult() == false)
            std::cout<<"No" << std::endl;
        else    
            std::cout << "Yes" << std::endl;
        std::cout << "Phone number:0";
        for(auto i=Number.begin() ; i!=Number.end();++i)
            std::cout<< *i;
        std::cout << std::endl;
        std::cout << "CNP: " << CNP << std::endl;
        std::cout << "E-mail: " << Email << std::endl;
    }

    string Customer::searchClientbyName(){
        string nameToSearch;
        std::cout << "Enter the name of the customer you want to find: ";
        while(true){
        std::cin >> nameToSearch;
        if(checkName() == true)
            break;
        else
            std::cout << "Name must contain only letters from english alphabet.Please enter the name again: ";
        }
        std::cout << std::endl;
        return nameToSearch;
    }
    string Customer::searchClientbyCNP(){
        string CNPtoSearch;
        std::cout << "Enter the CNP of the customer you want to find: ";
        while(true){
        std::cin >> CNPtoSearch;
        if(checkCNP() == true)
            break;
        else
            std::cout << "CNP must contain only digits.Please enter the CNP again: ";
        }
        std::cout << std::endl;
        return CNPtoSearch;
    }
    void Customer::ReadFromFile(const char*FILENAME , std::vector<Customer>& customer){

    }
    void Customer::ReadFromFile_map(const char* FILENAME , std::unordered_map<string , Customer> & customer){

    }