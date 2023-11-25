//
// Created by Misu Stefan on 16.11.2023.
//

#ifndef PROIECTPOO_FACULTATE_NEGATIVEREVIEWS_H
#define PROIECTPOO_FACULTATE_NEGATIVEREVIEWS_H
#include "review.h"
class NegativeReviews:public Review{
private:
    bool NOTrecommended;
public:
    NegativeReviews():Review() , NOTrecommended(true){};
    ~NegativeReviews() = default;
    void PrintReview();
    void ReadReview();
    bool getNOTrecomended();
    void setNOTrecomended(bool _NOTrecomended);
};


#endif //PROIECTPOO_FACULTATE_NEGATIVEREVIEWS_H
