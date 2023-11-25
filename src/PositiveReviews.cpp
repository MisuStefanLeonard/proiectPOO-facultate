//
// Created by Misu Stefan on 16.11.2023.
//


#include "../include/PositiveReviews.h"

bool PositiveReviews::getRecommended() {
    return recommended;
}

void PositiveReviews::setRecomended(bool _recomended) {
    recommended = _recomended;
}

void PositiveReviews::ReadReview() {
    Review::ReadReview();
    setLightGreen;
    std::cout << "Would you recommend this hotel?(Yes/No) ----> ";
    bool Ans_Flag = true;
    string ans;
    while(Ans_Flag){
        std::cin >> ans;
        if(ans == "YES" || ans == "Yes" || ans == "No" || ans == "NO"){
            Ans_Flag = false;
        }else {
            setRed;
            std::cout << "Please enter a valid answer! Enter---> ";
        }
    }
    if(ans == "YES" || ans == "Yes")
        recommended = true;
    else
        recommended = false;

}

void PositiveReviews::PrintReview() {
    Review::PrintReview();
    if(recommended) {
        setLightGreen;
        std::cout << "--> Recommended" << std::endl;
    }else {
        setRed;
        std::cout << "--> Not recommended" << std::endl;
    }

}