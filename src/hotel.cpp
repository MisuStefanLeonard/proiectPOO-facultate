#include "hotel.h"

void Hotel::sethName(const string &name)
{
    hotel_name = name;
}
const string &Hotel::gethName() const
{
    return hotel_name;
}
void Hotel::sethAddres(const string &addres)
{
    hotel_addres = addres;
}
const string &Hotel::gethAddres() const
{
    return hotel_addres;
}
void Hotel::sethCity(const string &city)
{
    City = city;
}
const string &Hotel::gethCity() const
{
    return City;
}
void Hotel::sethEmail(const string &hMail)
{
    hotel_email_address = hMail;
}
const string &Hotel::gethEmail()
{
    return hotel_email_address;
}
void Hotel::sethSingleRoom(int singleRoom)
{
    single_rooms = singleRoom;
}
int Hotel::gethSingleRoom() const
{
    return single_rooms;
}
void Hotel::sethDoubleRoom(int doubleRoom)
{
    double_rooms = doubleRoom;
}
int Hotel::gethDoubleRoom() const
{
    return double_rooms;
}
void Hotel::sethTripleRoom(int tripleRoom)
{
    triple_rooms = tripleRoom;
}
int Hotel::gethTripleRoom() const
{
    return triple_rooms;
}
void Hotel::sethPriceSingleRoom(int price_single_room)
{
    price_per_single_room = price_single_room;
}
int Hotel::gethPriceSingleRoom()
{
    return price_per_single_room;
}
void Hotel::sethPriceDoubleRoom(int price_double_room)
{
    price_per_double_room = price_double_room;
}
int Hotel::gethPriceDoubleRoom()
{
    return price_per_double_room;
}
void Hotel::sethPriceTripleRoom(int price_triple_room)
{
    price_per_triple_room = price_triple_room;
}
int Hotel::gethPriceTripleRoom()
{
    return price_per_triple_room;
}
void Hotel::sethNumber(int number)
{
    hotel_number = number;
}
int Hotel::gethNumber() const
{
    return hotel_number;
}
void Hotel::Print()
{
}
void Hotel::Read()
{
}
void Hotel::ReadFromFile_map(const char *FILENAME, std::unordered_map<string, Hotel> &map)
{
}

Hotel::Hotel(const Hotel &another)
{
    hotel_name = another.hotel_name;
    hotel_addres = another.hotel_addres;
    City = another.City;
    single_rooms = another.single_rooms;
    double_rooms = another.double_rooms;
    triple_rooms = another.triple_rooms;
    price_per_single_room = another.price_per_single_room;
    price_per_double_room = another.price_per_double_room;
    price_per_triple_room = another.price_per_triple_room;
    hotel_number = another.hotel_number;
    hotel_email_address = another.hotel_email_address;
}

std::ostream &operator<<(std::ostream &os, Hotel &h)
{
    os << "Hotel name : " << h.hotel_name << std::endl;
    os << "Hotel addres : " << h.hotel_addres << std::endl;
    os << "Hotel city: " << h.City << std::endl;
    os << "Hotel rooms ->   Single rooms: " << h.single_rooms;
    os << " Price single room: " << h.price_per_single_room << "$" << std::endl;
    os << "\t\t Double rooms: " << h.double_rooms;
    os << " Price double room: " << h.price_per_double_room << "$" << std::endl;
    os << "\t\t Triple rooms: " << h.triple_rooms;
    os << " Price triple room :" << h.price_per_triple_room << "$" << std::endl;
    os << "Hotel e-mail addres: " << h.hotel_email_address << std::endl;
    os << "Hotel number: 0" << h.hotel_number << std::endl;
    os << std::endl;
    os << std::endl;
    return os;
}

void Hotel::ReadFromFile(const char *FILENAME, std::vector<Hotel> &hotel)
{
    std::ifstream filein;
    filein.open(FILENAME);
    if (filein.is_open() == 0)
    {
        std::cerr << "File could not be opened" << std::endl;
    }
    int hSingleRooms, hSingleRoom_price, hDoubleRooms, hDoubleRoom_price, hTripleRooms, hTripleRoom_price, hNumber;
    string hName, hAddres, hCity, hEmailAddres;
    while (filein >> hName >> hAddres >> hCity >> hSingleRooms >> hSingleRoom_price >> hDoubleRooms >> hDoubleRoom_price >> hTripleRooms >> hTripleRoom_price >> hNumber >> hEmailAddres)
    {
        // testing// std::cout << "Read :" << hName << " " << hAddres << " " << hCity << " " << hSingleRooms << " "<< hSingleRoom_price << " " << hDoubleRooms << " " << hDoubleRoom_price << " " << hTripleRooms << " " << hTripleRoom_price  << " "<< hNumber << std::endl;
        Hotel temp;
        temp.sethName(hName);
        temp.sethAddres(hAddres);
        temp.sethCity(hCity);
        temp.sethSingleRoom(hSingleRooms);
        temp.sethPriceSingleRoom(hSingleRoom_price);
        temp.sethDoubleRoom(hDoubleRooms);
        temp.sethPriceDoubleRoom(hDoubleRoom_price);
        temp.sethTripleRoom(hTripleRooms);
        temp.sethPriceTripleRoom(hTripleRoom_price);
        temp.sethNumber(hNumber);
        temp.sethEmail(hEmailAddres);
        hotel.push_back(temp);
    }
    filein.close();
}
string Hotel::searchHotel()
{
    string searchHotel;
    int count = 0;
    std::cout << "Enter the hotel name you are looking for: ";
    auto it = searchHotel.begin();
    while (true)
    {
        std::cin >> searchHotel;
        for (it = searchHotel.begin(); it != searchHotel.end(); ++it)
        {
            if (isalpha((*it)) == true)
            {
                count++;
                continue;
            }
        }
        if (count == searchHotel.size())
            break;
        std::cout << "Hotel name must contain only letter from english alphabeth.Please enter the name of the hotel again: ";
    }
    return searchHotel;
}