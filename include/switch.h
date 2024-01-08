#ifndef SWITCH_H
#define SWITCH_H

#include "customer.h"
#include "LBAAC.h"
#include "hotel.h"
#include "customercard.h"
#include "city.h"
#include "review.h"
#include "AnonymReviews.h"
#include "PositiveReviews.h"
#include "NegativeReviews.h"
#include "CustomerCardBuilder.h"


class SWITCH{
public:
    void Add_Customer(std::vector<Customer>& customer , const char *FILENAME , const string& curr_id);
    void ReadFromUSERINFO_INTO_VEC(std::vector<Customer>& custTemp , const char* FILENAME);
    void ReplaceInTempVec(string searchname , std::vector<Customer>& custTemp , Customer& c_temp);
    void WritingModifiedCustomerBackTo_USERINFO(std::vector<Customer>& custTemp , const char *FILENAME);
    void Modify_Customer(LinkBetweenAccountAndCustomer LBAAC,std::vector<Customer> &customer,const char*FILENAME , std::unordered_map<string , Customer>& mapofcustomers , const string& currID);
    void Search_Customer(std::vector<Customer> &customer);
    void REMOVE_IN_VEC(std::vector<Customer>& custTemp, Customer& c_temp, string CNP_search);
    void Remove_Customer(LinkBetweenAccountAndCustomer LBAAC,std::vector<Customer> &customer , std::unordered_map<string , Customer>& map_of_customers , const char* FILENAME , string currID);
    int Print_Customer(std::vector<Customer>& customer , std::unordered_map<string , Customer> customerMap , string currID);
    void Exit_Program(std::vector<Customer> &customer , std::vector<Hotel> &hotel);
    void Show_Hotels(std::vector<Hotel> & hotel);
    void Search_Hotel(std::vector<Hotel>& hotel);
    int Answer_BOOKING(std::vector<Customer> &customer , string &ans);
    void DATE_CHECKIN_AND_CITY(std::unordered_map<string , City>& cities , string &ans_city , string &checkin_dt , string &checkout_dt);
    void Print_Hotels_From__answer_city(std::vector<Hotel> &hotel,string &answer_city ,int &no_hotel);
    void Select_HOTEL(std::vector<Hotel> &hotel, int &p_pos , string &p_answer_booking);
    int Rooms_Select(int &roomNUM_ans,int &oneBR_rooms , int &twoBR_rooms , int &threeBR_rooms ,  std::vector<Hotel>::iterator h_selected);
    int TotalPAY_and_WAYtoPay(std::vector<Hotel>::iterator h_selected , int& p_Total_PAY , int& p_pay_answer ,int& oneBR_rooms , int& twoBR_rooms , int& threeBR_rooms );
    int Pay_Card(int &p_Total_PAY , CustomerCard* cardObj ,CustomerCardBuilder& cardBuilder ,bool& answer_flag , bool& input_flag , bool& cardName_flag , bool&  cardNumber_flag ,
    bool& cardExpDate_flag , bool &cardCVV_flag , bool &checkMoney_flag  , bool& printInfo_flag , bool& checkingCardInfo_flag);
    void Print_Data(bool &printInfo_flag , CustomerCard *cardObj , int& p_Total_PAY ,
    std::vector<Hotel>::iterator h_selected , std::vector<Customer>& customer,
    string &p_checkinDate ,string &p_checkOutDate , int &p_singleRooms , int &p_doubleRooms , int &p_tripleRooms , const string& currID , std::unordered_map<string , Customer>& customerMap);
    bool Answer_Review();
    void Post_Review(std::vector<Customer> customer  , const char *FILENAME , std::vector<Hotel>& hotel,std::unordered_map<string , City> cities,const string& currID);
    // adaugat sa vezi rezervarile vechi poate
};
#endif
