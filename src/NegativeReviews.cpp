//
// Created by Misu Stefan on 16.11.2023.
//

#include "../include/NegativeReviews.h"

bool NegativeReviews::getNOTrecomended() {
    return NOTrecommended;
}

void NegativeReviews::setNOTrecomended(bool NOTrecomended) {
    this->NOTrecommended = NOTrecomended;
}

void NegativeReviews::ReadReview() {
    Review::ReadReview();
    setLightGreen;
    std::cout << "Would you recommend this hotel?(Yes/No) ----> " ;
    bool Ans_Flag = true;
    string ans;
    while(Ans_Flag){
        std::cin >> ans;
        if(ans == "YES" || ans == "Yes" || ans == "No" || ans == "NO"){
            Ans_Flag = false;
        }else{
            setRed;
            std::cout << "Please enter a valid answer! Enter---> ";
        }
    }
    if(ans == "YES" || ans == "Yes")
        NOTrecommended = false;
    else
        NOTrecommended = true;

}

void NegativeReviews::PrintReview() {
    Review::PrintReview();
    if (NOTrecommended) {
        setRed;
        std::cout << "--> Not recommended" << std::endl;
    } else {
        setLightGreen;
        std::cout << "--> Recommended" << std::endl;
    }
}
