//
// Created by Misu Stefan on 16.11.2023.
//

#include "../include/AnonymReviews.h"

bool AnonymReview::getRecomendOrNot() {
    return RecomendOrNot;
}

void AnonymReview::setRecomendOrNot(bool _recomendOrNot) {
    RecomendOrNot = _recomendOrNot;
}

const string& AnonymReview::getAnonymId() {
    return AnonymId;
}

void AnonymReview::setAnonymId(const string& _AnonymId) {
    AnonymId = _AnonymId;
}


void AnonymReview::ReadReview() {
    std::cout << "Anonymous ID ---> ";
    string anonymID;
    std::cin >>  anonymID;
    AnonymId = anonymID;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    string text;
    std::cout << "Your review: ";
    std::getline(std::cin , text);
    ReviewText = text;
    bool inputCheck = true;
    while(inputCheck) {
        try {
            setLightGreen;
            std::cout << "Number of stars --> ";
            std::cin >> Stars;
            if(!std::cin){
                throw std::runtime_error("Input cannot be 0 or less and cannot contain letters");
            }
            if(Stars <= 0 ){
                throw  std::runtime_error("Input cannot be 0 or less");
            }
            inputCheck = false;
        }
        catch(const std::exception& e){
            setRed;
            std::cout << "Error ---> " << e.what() << "\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    setLightGreen;
    std::cout << "Would you recommend this hotel?(Yes/No) ----> " ;
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
        RecomendOrNot = true;
    else
        RecomendOrNot = false;

}

void AnonymReview::PrintReview() {
    setCyan;
    std::cout << "--> Anonymous ID -> "<< getAnonymId();
    std::cout << "Review stars: ";
    switch (Stars) {
        case 1:{
            setRed;
            std::cout << "--> *" << "\n";
            break;
        }
        case 2:{
            setRed;
            std::cout << "--> * * " << "\n";
            break;
        }
        case 3:{
            setLightGreen;
            std::cout << "--> * * *" << "\n";
            break;
        }
        case 4:{
            setLightGreen;
            std::cout << "--> * * * *" << "\n";
            break;
        }
        case 5:{
            setLightGreen;
            std::cout << "--> * * * * *" << "\n";
            break;
        }
        default:{
            break;
        }
    }
    setRed;
    std::cout << "--> Review: " << ReviewText << "\n";
    if (getRecomendOrNot()) {
        setLightGreen;
        std::cout << "--> Recommended" << std::endl;
    } else {
        setRed;
        std::cout << "--> Not recommended" << std::endl;

    }
}