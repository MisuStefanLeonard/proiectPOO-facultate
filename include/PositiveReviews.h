//
// Created by Misu Stefan on 16.11.2023.
//

#ifndef PROIECTPOO_FACULTATE_POSITIVEREVIEWS_H
#define PROIECTPOO_FACULTATE_POSITIVEREVIEWS_H
#include "review.h"

class PositiveReviews:public Review{
private:
    bool recommended;
public:
   PositiveReviews():Review() , recommended(false){};
   ~PositiveReviews() = default;
   void PrintReview();
   void ReadReview();
   bool getRecommended();
   void setRecomended(bool _recomended);
};



#endif //PROIECTPOO_FACULTATE_POSITIVEREVIEWS_H
