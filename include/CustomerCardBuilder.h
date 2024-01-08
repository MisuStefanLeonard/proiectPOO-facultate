//
// Created by Misu Stefan on 08.01.2024.
//

#ifndef PROIECTPOO_FACULTATE_CUSTOMERCARDBUILDER_H
#define PROIECTPOO_FACULTATE_CUSTOMERCARDBUILDER_H
#include "customercard.h"
class CustomerCardBuilder {
private:
    CustomerCard card;

public:
    CustomerCardBuilder& setName(const std::string& name);
    CustomerCardBuilder& setCardNumber(const std::string& cardNumber);
    CustomerCardBuilder& setExpirationDate(const std::string& expirationDate) ;
    CustomerCardBuilder& setCVV(const std::string& cvv) ;
    CustomerCardBuilder& setMoney(int money) ;
    CustomerCard build() ;
};


#endif //PROIECTPOO_FACULTATE_CUSTOMERCARDBUILDER_H
