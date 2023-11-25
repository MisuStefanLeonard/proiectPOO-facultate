//
// Created by Misu Stefan on 10.11.2023.
//

#include "../include/review.h"
int Review::Review_Id = 0;

const string& Review::getReview() const {
    return ReviewText;
}

void Review::setReview(const std::string &review_text) {
    ReviewText = review_text;
}

void Review::setStars(int _stars) {
    Stars = _stars;
}

int Review::getStars() {
    return Stars;
}

void Review::setCustomer(std::shared_ptr<Customer> customer_new){
    this->customer = customer_new;
}

std::shared_ptr<Customer> Review::getCustomer() {
    return customer;
}

Review::Review():customer(nullptr),ReviewText("") , Stars(0) {
    Review_Id++;
}

int Review::getReviewId() {
    return Review_Id;
}

Review& Review::operator=(const Review &another) {
    if(this != &another) {
        ReviewText = another.ReviewText;
        Stars = another.Stars;
        customer = another.customer;
    }
    return *this;
}



void Review::PrintReview(){
    setCyan;
    std::cout << "--> User -> "<< customer->getID() << std::endl;
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
    setYellow;
    std::cout << "--> Review: " << ReviewText << "\n";
}

void Review::ReadReview(){
    std::cout << "Account ID ---> " << customer->getID() << "\n";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Your review ---> ";
    std::getline(std::cin , ReviewText);
    bool inputCheck = true;
    while(inputCheck) {
        try {
            setLightGreen;
            std::cout << "Number of stars ---> ";
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
}



