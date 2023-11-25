#include "customer.h"
    void Customer::setID(const string& id){
        this->ID = id;
    }
    string Customer::getID(){
        return ID;
    }
    void Customer::setName(const string& name){
        Name = name;
    }
    string Customer::getName(){
        return Name;
    }
    void Customer::setPrename(const string& prename){
        Prename = prename;
    }
    string Customer::getPrename(){
        return Prename;
    }
    void Customer::setAge(int age){
        Age = age;
    }
    int Customer::getAge() const{
        return Age;
    }
    void Customer::setSex(char sex){
        Sex = sex;
    }
    char Customer::getSex() const {
        return Sex;
    }
    void Customer::setMoney(int money){
        Money = money;
    }
    int Customer::getMoney() const {
        return Money;
    }
    void Customer::setAdult(bool adult){
        Adult = adult;
    }
    bool Customer::getAdult() const {
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
    void Customer::setCNP(const string& cnp){
        CNP = cnp;
    }
    string Customer::getCNP(){
        return CNP;
    }
    void Customer::setEmail(const string&email){
        Email = email;
    }
    string Customer::getEmail(){
        return Email;
    }
    bool Customer::checkName() const{
        // 65 - 122
        for(int i = 0 ; i < Name.size();i++){
            if(isalpha(Name[i]) == 0){
                std::cout << "Name must contain only letters from english alphabeth" << std::endl;
                return false;
            }
        }
        return true;
    }
    bool Customer::checkPrename() const{
        // 65 - 122
        for(int i = 0 ; i < Prename.size();i++){
            if(isalpha(Prename[i]) == 0){
                std::cout << "Prename must contain only letters from english alphabeth" << std::endl;
                return false;
            }
        }
        return true;
    }
    bool Customer::checkAge() const{
    if(Age >= 0 && Age <= 200)
        return true; 
    return false;
    }
    bool Customer::checkAdult() const{
        if(Adult == 0)
            return false;
        return true;
    }
    bool Customer::checkMoney() const{
        if(Money < 0)
            return false;
        return true;
    }
    bool Customer::checkCNP() const{
        int count = 0 ;
        for(auto it = CNP.begin(); it != CNP.end() ; ++it){
            if(isdigit((*it)) == true){
                count++;
                continue;
            }
        }
        if(count == 13)
            return true;
        else{
            return false;
        }
        
    }
    bool Customer::checkEmailAddres(){
        
        const regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
        if(std::regex_match(Email,pattern))
            return true;
        return false;       
    }
    std::istream& operator>>(std::istream& is , Customer& customer){
        std::cout << "Your name : " << std::endl;
        while(true){
            is >> customer.Name;
            if(customer.checkName())
                break;
            std::cout << "Please enter your name again:";
        }
        std::cout << "Your prename : " << std::endl;
        while(true){
            is >> customer.Prename;
            if(customer.checkPrename())
                 break;
            std::cout << "Please enter your prename again: ";
        }
        std::cout << "Your age(only digits):" << std::endl;
        while (true) {
            is >> customer.Age;
            if (is.fail()) {
                std::cout << "Age must be a number. Please enter your age again: " << std::endl;
                is.clear();
                is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }else{
                if (customer.checkAge())
                    break;
                std::cout << "Invalid age. Please enter your age again: " << std::endl;
            }
}

        std::cout << "Your sex(M(male) , F(female): " << std::endl;
        while(true){
            is >> customer.Sex;
            if(customer.Sex == 'M' || customer.Sex == 'F')
                break;
            if(customer.Sex == 'm' || customer.Sex == 'f'){
               toupper(customer.Sex);
               break;
            }
            if(customer.Sex != 'M' || customer.Sex != 'm' || customer.Sex != 'F' || customer.Sex != 'f'){
                std::cout << "Wrong input. Please only M / m or F / f ";
            }
        }
        is.clear();
        is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "How much money are you willing to spend on the reservation ? Please enter the amount here($) : " << std::endl;
        while (true) {
            std::cin >> customer.Money;
            if(is.fail()){
                std::cout << "Money must be a number. Please enter your money again: ";
                is.clear();
                is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }else{ 
                if(customer.checkMoney())
                    break;
                std::cout << "Money cannot be a negative number.Please enter the amount again: ";
            }
                
        }
        if(customer.Age >= 18)
            customer.Adult = 1;
        else    
            customer.Adult = 0;
        std::cout << "Please enter your phone number(9 digits starting with the digit after 0): " << std::endl;
        int number;
        while(true){
        is >> number;
        if(is.fail()){
            std::cout << "Phone number must contain only digits.";
            is.clear();
            is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout<<" Please enter the phone number again: " << std::endl;
        }else
            break;
        }
        while(number<=9){
            int last = number%10;
            customer.Number.push_back(last);
            number = number/10;
        }
        customer.Number.push_back(number);
        std::cout << "Please enter your CNP(only digits) :"  << std::endl;
        while(true){
            is >> customer.CNP;
            if(customer.checkCNP())
                break;
            else
                std::cout << "CNP must contain only digits/Invalid CNP.Please enter your CNP again:";
        }
        std::cout << "Please enter your E-mail addres : ";
        while(true){
            is >> customer.Email;
            if(customer.checkEmailAddres())
                break;
            else
            std::cout << "Please enter a valid E-mail addres: ";
        }
        return is;
    }
    std::ostream& operator<<(std::ostream& os , Customer& customer){
        os << "Account username: " << customer.ID << std::endl;
        os << "Name:" << customer.Name << std::endl;
        os << "Prename:" << customer.Prename << std::endl;
        os << "Age:" << customer.Age << std::endl;
        os << "Sex:" << customer.Sex << std::endl;
        os << "Money:" << customer.Money << "$"<< std::endl;
        os << "Adult:";
        if(!customer.checkAdult())
            os<<"No" << std::endl;
        else    
            os << "Yes" << std::endl;
        std::cout << "Phone number:0";
        for(auto i=customer.Number.begin() ; i!=customer.Number.end();++i)
            os<< *i;
        os << std::endl;
        os << "CNP: " << customer.CNP << std::endl;
        os << "E-mail: " << customer.Email << std::endl;
        return os;
    }

    string Customer::searchClientbyName() const{
        string nameToSearch;
        std::cout << "Enter the name of the customer you want to find: ";
        while(true){
        std::cin >> nameToSearch;
        if(checkName())
            break;
        else
            std::cout << "Name must contain only letters from english alphabet.Please enter the name again: ";
        }
        std::cout << std::endl;
        return nameToSearch;
    }
    //503/123/034/092/5
    string Customer::searchClientbyCNP() const{
        string CNPtoSearch;
        std::cout << "Enter the CNP of the customer you want to find: ";
        while(true){
        std::cin >> CNPtoSearch;
        if(checkCNP())
            break;
        else
            std::cout << "CNP must contain only digits.Please enter the CNP again: ";
        }
        std::cout << std::endl;
        return CNPtoSearch;
    }