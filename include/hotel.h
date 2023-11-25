#ifndef HOTEL_H
#define HOTEL_H

#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <fstream>
#include <unordered_map>
#include "InputOutputFunctions.h"
#include "review.h"
#include "AnonymReviews.h"
#include "NegativeReviews.h"
#include "PositiveReviews.h"
using std::string;

class Hotel : public InputOutputFunctions<Hotel>
{
private:
    string hotel_name;
    string hotel_address;
    string City;
    int single_rooms;
    int double_rooms;
    int triple_rooms;
    int price_per_single_room;
    int price_per_double_room;
    int price_per_triple_room;
    // clasa de camere + vector
    int hotel_number;
    string hotel_email_address;
    std::vector<std::shared_ptr<Review>> hotel_reviews;
public:
    Hotel(const Hotel &);
    Hotel& operator=(const Hotel& other);
    explicit Hotel(const string& h_name = "", const string& h_address = "", const string& city = "", int s_rooms = 0,
          int d_rooms = 0, int t_rooms = 0, int p_s_room = 0, int p_d_rooms = 0, int p_t_rooms = 0,
          int h_number = 0, const string& h_email = "") : hotel_name(h_name), hotel_address(h_address), City(city), single_rooms(s_rooms), double_rooms(d_rooms),
                                                   triple_rooms(t_rooms), price_per_single_room(p_s_room), price_per_double_room(p_d_rooms), price_per_triple_room(p_t_rooms),
                                                   hotel_number(h_number), hotel_email_address(h_email) ,hotel_reviews(0){}
    virtual ~Hotel() = default;
    void sethName(const string &name);
    const string &gethName() const;
    void sethAddres(const string &address);
    void sethCity(const string &city);
    const string &gethCity() const;
    void sethEmail(const string &hMail);
    void sethSingleRoom(int singleRoom);
    int gethSingleRoom() const;
    void sethDoubleRoom(int doubleRoom);
    int gethDoubleRoom() const;
    void sethTripleRoom(int tripleRoom);
    int gethTripleRoom() const;
    void sethPriceSingleRoom(int price_single_room);
    int gethPriceSingleRoom() const ;
    void sethPriceDoubleRoom(int price_double_room);
    int gethPriceDoubleRoom() const;
    void sethPriceTripleRoom(int price_triple_room);
    int gethPriceTripleRoom() const;
    void sethNumber(int number);
    std::vector<std::shared_ptr<Review>>& getVectorReviewPtr();
    void PrintHotelReviews();
    friend std::ostream &operator<<(std::ostream &os, Hotel &h);
    void ReadReviewsFromFile(const char* FILENAME , std::vector<Hotel> &hotel , std::vector<Customer> customer);
    void ReadFromFile(const char *FILENAME, std::vector<Hotel> &hotel) override;
    void ReadFromFile_map(const char *FILENAME, std::unordered_map<string, Hotel> &map) override;
    string searchHotel();
};

#endif