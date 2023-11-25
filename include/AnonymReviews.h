//
// Created by Misu Stefan on 16.11.2023.
//

#ifndef PROIECTPOO_FACULTATE_ANONYMREVIEWS_H
#define PROIECTPOO_FACULTATE_ANONYMREVIEWS_H
#include "review.h"
using std::string;
class AnonymReview:public Review{
private:
    bool RecomendOrNot;
    string AnonymId;
public:
    void ReadReview();
    void PrintReview();
    AnonymReview():Review() , RecomendOrNot(false){};
    ~AnonymReview() = default;
    bool getRecomendOrNot();
    void setRecomendOrNot(bool _recomendOrNot);
    const string& getAnonymId();
    void setAnonymId(const string& _AnonymId);
};
#endif //PROIECTPOO_FACULTATE_ANONYMREVIEWS_H
