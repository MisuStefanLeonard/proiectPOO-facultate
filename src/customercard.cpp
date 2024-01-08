#include "customercard.h"
#include "../rlutil/rlutil.h"
#define setYellow rlutil::setColor(rlutil::YELLOW)
#define setLightRed rlutil::setColor(rlutil::LIGHTRED)
#define setLightGreen rlutil::setColor(rlutil::GREEN)
#define setRed rlutil::setColor(rlutil::RED)
    string CustomerCard::cardGetName(){
        return Name;
    }
    string CustomerCard::cardGetCardNumber(){
        return CardNumber;
    }
    string CustomerCard::cardGetExpirationDate(){
        return Expiration_Date;
    }
    string CustomerCard::cardGetCVV(){
        return CVV;
    }
    int CustomerCard::getCardMoney(){
        return Money;
    }

    void CustomerCard::setName(const std::string& name){
        this->Name = name;
    }

    void CustomerCard::setCardNumer(const std::string& cardNumber){
        this->CardNumber = cardNumber;
    }

    void CustomerCard::setCvv(const std::string& cvv){
        this->CVV = cvv;
    }

    void CustomerCard::setExpirationDate(const std::string& expdate){
        this->Expiration_Date = expdate;
    }

    void CustomerCard::setMoney(int money){
        this->Money = money;
    }

    std::istream& operator>>(std::istream& is , CustomerCard& cardOb){
        setYellow;
        std::cout << "*************************************\n" ;
        std::cout << "Name written on the credit/debit card \n" ;
        std::cout << "*************************************\n" ;
        std::cin.ignore();
        setLightRed;
        std::getline(is, cardOb.Name);
        std::cout << std::endl;
        setYellow;
        std::cout << "*************************************\n" ;
        std::cout << "Card number \n";
        std::cout << "*************************************\n" ;
        setLightRed;
        std::getline(is, cardOb.CardNumber);
        std::cout << std::endl;
        setYellow;
        std::cout << "*************************************\n";
        std::cout << "Expiration date(mm/yyyy) \n";
        std::cout << "*************************************\n" ;
        setLightRed;
        is >> cardOb.Expiration_Date;
        std::cout << std::endl;
        setYellow;
        std::cout << "*************************************\n" ;
        std::cout << "CVV(three or two digits on the back of the card)\n";
        std::cout << "*************************************\n" ;
        setLightRed;
        is >> cardOb.CVV;
        std::cout << std::endl;
        srand(time(0));
        cardOb.Money = 1000;
        return is;
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

