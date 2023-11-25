//
// Created by Misu Stefan on 07.11.2023.
//

#ifndef PROIECTPOO_FACULTATE_REVIEW_H
#define PROIECTPOO_FACULTATE_REVIEW_H
#include "../rlutil/rlutil.h"
#include "customer.h"
#define setYellow rlutil::setColor(rlutil::YELLOW)
#define setLightRed rlutil::setColor(rlutil::LIGHTRED)
#define setLightGreen rlutil::setColor(rlutil::LIGHTGREEN)
#define setRed rlutil::setColor(rlutil::RED)
#define setGrey rlutil::setColor(rlutil::GREY)
#define setCyan rlutil::setColor(rlutil::CYAN)
using std::string;

class Review{
private:
protected:
    std::shared_ptr<Customer> customer;
    static int Review_Id;
    string ReviewText;
    int Stars;
public:
    const string& getReview() const;
    void setStars(int _stars);
    void setReview(const string& review_text);
    int getStars();
    void setCustomer(std::shared_ptr<Customer> customer2);
    static int getReviewId();
    std::shared_ptr<Customer> getCustomer();
    virtual void PrintReview();
    virtual void ReadReview();
    Review& operator=(const Review&);
    Review();
    virtual ~Review() = default;
};

#endif //PROIECTPOO_FACULTATE_REVIEW_H
