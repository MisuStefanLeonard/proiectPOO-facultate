//
// Created by Misu Stefan on 08.01.2024.
//

#include "../include/CustomerCardBuilder.h"

    CustomerCardBuilder& CustomerCardBuilder::setName(const std::string& name) {
        card.setName(name);
        return *this;
    }

    CustomerCardBuilder& CustomerCardBuilder::setCardNumber(const std::string& cardNumber) {
        card.setCardNumer(cardNumber);
        return *this;
    }

    CustomerCardBuilder& CustomerCardBuilder::setExpirationDate(const std::string& expirationDate) {
        card.setExpirationDate(expirationDate);
        return *this;
    }

    CustomerCardBuilder& CustomerCardBuilder::setCVV(const std::string& cvv) {
        card.setCvv(cvv);
        return *this;
    }

    CustomerCardBuilder& CustomerCardBuilder::setMoney(int money) {
        card.setMoney(money);
        return *this;
    }

    CustomerCard CustomerCardBuilder::build() {
        srand(time(0));
        return card;
    }

