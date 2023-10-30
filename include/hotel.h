#ifndef HOTEL_H
#define HOTEL_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <unordered_map>
#include "InputOutputFunctions.h"
using std::string;

class Hotel : public InputOutputFunctions<Hotel>
{
private:
    string hotel_name;
    string hotel_addres;
    string City;
    int single_rooms;
    int double_rooms;
    int triple_rooms;
    int price_per_single_room;
    int price_per_double_room;
    int price_per_triple_room;
    int hotel_number;
    string hotel_email_address;

public:
    Hotel(const Hotel &);
    Hotel(string h_name = "", string h_address = "", string city = "", int s_rooms = 0,
          int d_rooms = 0, int t_rooms = 0, int p_s_room = 0, int p_d_rooms = 0, int p_t_rooms = 0,
          int h_number = 0, string h_email = "") : hotel_name(h_address), hotel_addres(h_address), City(city), single_rooms(s_rooms), double_rooms(d_rooms),
                                                   triple_rooms(t_rooms), price_per_single_room(p_s_room), price_per_double_room(p_d_rooms), price_per_triple_room(p_t_rooms),
                                                   hotel_number(h_number), hotel_email_address(h_email) {}
    void sethName(const string &name);
    const string &gethName() const;
    void sethAddres(const string &addres);
    const string &gethAddres() const;
    void sethCity(const string &city);
    const string &gethCity() const;
    void sethEmail(const string &hMail);
    const string &gethEmail();
    void sethSingleRoom(int singleRoom);
    int gethSingleRoom() const;
    void sethDoubleRoom(int doubleRoom);
    int gethDoubleRoom() const;
    void sethTripleRoom(int tripleRoom);
    int gethTripleRoom() const;
    void sethPriceSingleRoom(int price_single_room);
    int gethPriceSingleRoom();
    void sethPriceDoubleRoom(int price_double_room);
    int gethPriceDoubleRoom();
    void sethPriceTripleRoom(int price_triple_room);
    int gethPriceTripleRoom();
    void sethNumber(int number);
    int gethNumber() const;
    void Print() override;
    friend std::ostream &operator<<(std::ostream &os, Hotel &h);
    void ReadFromFile(const char *FILENAME, std::vector<Hotel> &hotel) override;
    void Read() override;
    void ReadFromFile_map(const char *FILENAME, std::unordered_map<string, Hotel> &map) override;
    string searchHotel();
};

#endif