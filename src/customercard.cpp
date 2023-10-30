#include "customercard.h"

    void CustomerCard::cardSetName(string name){
        Name = name;
    }
    string CustomerCard::cardGetName(){
        return Name;
    }
    void CustomerCard::cardSetCardNumver(string cardnumber){
        CardNumber = cardnumber;
    }
    string CustomerCard::cardGetCardNumber(){
        return CardNumber;
    }
    void CustomerCard::cardSetExpirationDate(string exp_date){
        Expiration_Date = exp_date;
    }
    string CustomerCard::cardGetExpirationDate(){
        return Expiration_Date;
    }
    void CustomerCard::cardSetCVV(string cvv){
        CVV = cvv;
    }
    string CustomerCard::cardGetCVV(){
        return CVV;
    }
    void CustomerCard::setCardMoney(int money){
        Money = money;
    }
    int CustomerCard::getCardMoney(){
        return Money;
    }
    void CustomerCard::Read(){
        std::cout << "Name written on the credit/debit card: ";
        std::cin.ignore();
        std::getline(std::cin, Name);
        std::cout << std::endl;
        std::cout << "Card number: ";
        std::getline(std::cin, CardNumber);
        std::cout << std::endl;
        std::cout << "Expiration date(mm/yyyy): ";
        std::cin >> Expiration_Date;
        std::cout << std::endl;
        std::cout << "CVV(three or two digits on the back of the card):";
        std::cin >> CVV;
        std::cout << std::endl;
        srand(time(0));
        Money = 1000;
    }
    bool CustomerCard::isValidExpirationDate(){
        bool flag1 = false , flag2 = false;
        time_t now = time(0);
        tm *current_time = localtime(&now);
        int curr_year = 1900 +current_time->tm_year;
        int curr_month = 1 + current_time->tm_mon;
        string year = Expiration_Date.substr(3,6);
        int year_int = std::stoi(year);
        if(curr_year <= year_int)
            flag2 = true;
        auto second = Expiration_Date.begin() + 1;
        if(year_int == curr_year){
            if(((*second) - '0') > curr_month)
                flag1 = true;
        }
        if(year_int > curr_year)
            flag1 = true;
        if(flag1 == true && flag2 == true)
            return true;
        return false;
    }
    void CustomerCard::ReadFromFile_map(const char *FILENAME , std::unordered_map<string , CustomerCard> & map){

    }
    void CustomerCard::ReadFromFile(const char* FILENAME , std::vector <CustomerCard>& card_customer){

    }
    void CustomerCard::Print(){

    }

