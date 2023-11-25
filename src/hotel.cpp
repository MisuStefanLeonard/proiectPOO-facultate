#include <sstream>
#include "hotel.h"
void Hotel::sethName(const string &name)
{
    hotel_name = name;
}
const string &Hotel::gethName() const
{
    return hotel_name;
}
void Hotel::sethAddres(const string &address)
{
    hotel_address = address;
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
int Hotel::gethPriceSingleRoom() const
{
    return price_per_single_room;
}
void Hotel::sethPriceDoubleRoom(int price_double_room)
{
    price_per_double_room = price_double_room;
}
int Hotel::gethPriceDoubleRoom() const
{
    return price_per_double_room;
}
void Hotel::sethPriceTripleRoom(int price_triple_room)
{
    price_per_triple_room = price_triple_room;
}
int Hotel::gethPriceTripleRoom() const
{
    return price_per_triple_room;
}
void Hotel::sethNumber(int number)
{
    hotel_number = number;
}

void Hotel::ReadFromFile_map(const char *FILENAME, std::unordered_map<string, Hotel> &map){
    std::cout << "Not implemented" << std::endl;
}

std::vector<std::shared_ptr<Review>>& Hotel::getVectorReviewPtr() {
    return hotel_reviews;
}

Hotel& Hotel::operator=(const Hotel& another){
    if(this != &another){
        hotel_name = another.hotel_name;
        hotel_address = another.hotel_address;
        City = another.City;
        single_rooms = another.single_rooms;
        double_rooms = another.double_rooms;
        triple_rooms = another.triple_rooms;
        price_per_single_room = another.price_per_single_room;
        price_per_double_room = another.price_per_double_room;
        price_per_triple_room = another.price_per_triple_room;
        hotel_number = another.hotel_number;
        hotel_email_address = another.hotel_email_address;
        hotel_reviews = another.hotel_reviews;
    }
    return *this;
}

Hotel::Hotel(const Hotel &another)
{
    hotel_name = another.hotel_name;
    hotel_address = another.hotel_address;
    City = another.City;
    single_rooms = another.single_rooms;
    double_rooms = another.double_rooms;
    triple_rooms = another.triple_rooms;
    price_per_single_room = another.price_per_single_room;
    price_per_double_room = another.price_per_double_room;
    price_per_triple_room = another.price_per_triple_room;
    hotel_number = another.hotel_number;
    hotel_email_address = another.hotel_email_address;
    hotel_reviews = another.hotel_reviews;
}


std::ostream &operator<<(std::ostream &os, Hotel &h)
{
    setYellow;
    os << "Hotel name : " << h.hotel_name << std::endl;
    os << "Hotel address : " << h.hotel_address << std::endl;
    os << "Hotel city: " << h.City << std::endl;
    os << "Hotel rooms ->   Single rooms: " << h.single_rooms;
    os << " Price single room: " << h.price_per_single_room << "$" << std::endl;
    os << "\t\t Double rooms: " << h.double_rooms;
    os << " Price double room: " << h.price_per_double_room << "$" << std::endl;
    os << "\t\t Triple rooms: " << h.triple_rooms;
    os << " Price triple room :" << h.price_per_triple_room << "$" << std::endl;
    os << "Hotel e-mail address: " << h.hotel_email_address << std::endl;
    os << "Hotel number: 0" << h.hotel_number << std::endl;
    setRed;
    os << "***********************"<<std::endl;
    os << "***********************"<<std::endl;
    return os;
}

void Hotel::PrintHotelReviews() {
    if(hotel_reviews.empty()){
        setRed;
        std::cout << "There are no reviews for this hotel" << std::endl;
    }else{
        setYellow;
        std::cout << "*********************" << std::endl;
        std::cout << "****** REVIEWS ******" << std::endl;
        for(auto &h_review: hotel_reviews){
            if(dynamic_cast<AnonymReview*>(h_review.get())){
                setYellow;
                std::cout << "------ ANONYM REVIEW ------" << "\n";
                rlutil::resetColor();
                h_review->PrintReview();
                setYellow;
                std::cout << "---------------------------" << "\n";
            }else if(dynamic_cast<NegativeReviews*>(h_review.get())){
                setRed;
                std::cout << "------ NEGATIVE REVIEW ------" << "\n";
                rlutil::resetColor();
                h_review->PrintReview();
                setRed;
                std::cout << "---------------------------" << "\n";
            }else if(dynamic_cast<PositiveReviews*>(h_review.get())){
                setLightGreen;
                std::cout << "------ POSITIVE REVIEW ------" << "\n";
                rlutil::resetColor();
                h_review->PrintReview();
                setLightGreen;
                std::cout << "---------------------------" << "\n";
            }
        }
        setYellow;
        std::cout << "****** REVIEWS ******" << std::endl;
        std::cout << "*********************" << std::endl;
    }
}

void Hotel::ReadReviewsFromFile(const char *FILENAME, std::vector<Hotel> &hotel , std::vector<Customer> customer) {
    std::ifstream filein;
    filein.open(FILENAME);
    if (!filein.is_open()) {
        std::cerr << "File could not be opened " << std::endl;
        return;
    }

    string RevText, RevHotelName, RevCustomerID;
    int RevStars , RevID;
    bool RecommendedOrNot = false;

    string line;

    while (std::getline(filein, line)) {
        std::istringstream iss(line);
        string dummy1;
        iss >> dummy1;
        if (dummy1 == "***Anonymous***") {
            std::shared_ptr<Review> new_review = std::make_shared<AnonymReview>();
            try {
                auto anonym_rev = std::dynamic_pointer_cast<AnonymReview>(new_review);
                if (anonym_rev == nullptr)
                    throw std::runtime_error("Error in converting ptr");

                bool bfoundRevID;
                std::getline(filein, line); // - aici
                if(line.find("ReviewID--> ") != std::string::npos)
                    bfoundRevID = true;
                else
                    bfoundRevID = false;
                if (bfoundRevID)
                {
                    string::size_type foundRevID = line.find("ReviewID--> ");
                    string REVID = line.substr(foundRevID + 12);
                    RevID = stoi(REVID);
                }

                bool bfoundHotelName;
                std::getline(filein, line); // - aici
                if(line.find("Hotel-Name--> ") != std::string::npos)
                    bfoundHotelName = true;
                else
                    bfoundHotelName = false;
                if (bfoundHotelName)
                {
                    string::size_type foundHotelName = line.find("Hotel-Name--> ");
                    string strHotelName = line.substr(foundHotelName + 14);
                    RevHotelName = strHotelName;
                }

                bool bfoundAnonymous;
                std::getline(filein, line); // - aici
                if(line.find("AnonymousID--> ") != std::string::npos)
                    bfoundAnonymous = true;
                else
                    bfoundAnonymous = false;
                if (bfoundAnonymous)
                {
                    string::size_type foundAnoymousID = line.find("AnonymousID--> ");
                    string strAnonymousID = line.substr(foundAnoymousID + 15);
                    RevCustomerID = strAnonymousID;
                }

                bool bfoundRating;
                std::getline(filein, line); // - aici
                if(line.find("Rating--> ") != std::string::npos)
                    bfoundRating = true;
                else
                    bfoundRating = false;
                if (bfoundRating)
                {
                    string::size_type foundRating = line.find("Rating--> ");
                    string strRating = line.substr(foundRating + 10);
                    RevStars = stoi(strRating);
                }

                bool bfoundReviewText;
                std::getline(filein, line); // - aici
                if(line.find("Review--> ") != std::string::npos)
                    bfoundReviewText = true;
                else
                    bfoundReviewText = false;
                if (bfoundReviewText)
                {
                    string::size_type foundRating = line.find("Review--> ");
                    string strRating = line.substr(foundRating + 10);
                    RevText = strRating;
                }

                bool bfoundRecommended;
                std::getline(filein, line); // - aici
                if(line.find("Recommended--> ") != std::string::npos)
                    bfoundRecommended = true;
                else
                    bfoundRecommended = false;
                if ( bfoundRecommended)
                {
                    string::size_type foundRecommended = line.find("Recommended--> ");
                    string strReviewText = line.substr(foundRecommended + 15);
                    RecommendedOrNot = (bool) stoi(strReviewText);
                }

                auto current_account = std::make_shared<Customer>();
                for(auto& customer_it : customer){
                    if(customer_it.getID() == RevCustomerID){
                        current_account = std::make_shared<Customer>(customer_it);
                        break;
                    }
                }
                auto hotel_iterator = std::find_if(hotel.begin(), hotel.end(), [&](const Hotel& h) {
                    return h.gethName() == RevHotelName;
                });
                if(hotel_iterator != hotel.end()) {
                    auto &curr_hotel_vec = hotel_iterator->getVectorReviewPtr();
                    anonym_rev->setCustomer(current_account);
                    anonym_rev->setRecomendOrNot(RecommendedOrNot);
                    anonym_rev->setAnonymId(RevCustomerID);
                    anonym_rev->setStars(RevStars);
                    anonym_rev->setReview(RevText);
                    curr_hotel_vec.push_back(anonym_rev);
                }else
                    std::cout << "NOT FOUND !" << std::endl;
            } catch (std::exception &e) {
                setRed;
                std::cout << "Error -> " << e.what() << std::endl;
            }

        } else if (dummy1 == "***Positive***") {
            std::shared_ptr<Review> new_review = std::make_shared<PositiveReviews>();
            try {
                auto positive_rev = std::dynamic_pointer_cast<PositiveReviews>(new_review);
                if (positive_rev == nullptr)
                    throw std::runtime_error("Error in converting ptr");

                bool bfoundRevID;
                std::getline(filein, line); // - aici
                if(line.find("ReviewID--> ") != std::string::npos)
                    bfoundRevID = true;
                else
                    bfoundRevID = false;
                if (bfoundRevID)
                {
                    string::size_type foundRevID = line.find("ReviewID--> ");
                    string REVID = line.substr(foundRevID + 12);
                    RevID = stoi(REVID);
                }

                bool bfoundHotelName;
                std::getline(filein, line); // - aici
                if(line.find("Hotel-Name--> ") != std::string::npos)
                    bfoundHotelName = true;
                else
                    bfoundHotelName = false;
                if (bfoundHotelName)
                {
                    string::size_type foundHotelName = line.find("Hotel-Name--> ");
                    string strHotelName = line.substr(foundHotelName + 14);
                    RevHotelName = strHotelName;
                }

                bool bfoundCustomer;
                std::getline(filein, line); // - aici
                if(line.find("CustomerID--> ") != std::string::npos)
                    bfoundCustomer = true;
                else
                    bfoundCustomer = false;
                if (bfoundCustomer)
                {
                    string::size_type foundCustomerID = line.find("CustomerID--> ");
                    string strCustomerID = line.substr(foundCustomerID + 14);
                    RevCustomerID = strCustomerID;
                }

                bool bfoundRating;
                std::getline(filein, line); // - aici
                if(line.find("Rating--> ") != std::string::npos)
                    bfoundRating = true;
                else
                    bfoundRating = false;
                if (bfoundRating)
                {
                    string::size_type foundRating = line.find("Rating--> ");
                    string strRating = line.substr(foundRating + 10);
                    RevStars = stoi(strRating);
                }

                bool bfoundReviewText;
                std::getline(filein, line); // - aici
                if(line.find("Review--> ") != std::string::npos)
                    bfoundReviewText = true;
                else
                    bfoundReviewText = false;
                if (bfoundReviewText)
                {
                    string::size_type foundRating = line.find("Review--> ");
                    string strRating = line.substr(foundRating + 10);
                    RevText = strRating;
                }

                bool bfoundRecommended;
                std::getline(filein, line); // - aici
                if(line.find("Recommended--> ") != std::string::npos)
                    bfoundRecommended = true;
                else
                    bfoundRecommended = false;
                if ( bfoundRecommended)
                {
                    string::size_type foundRecommended = line.find("Recommended--> ");
                    string strReviewText = line.substr(foundRecommended + 15);
                    RecommendedOrNot = (bool) stoi(strReviewText);
                }

                auto current_account = std::make_shared<Customer>();
                for(auto& customer_it : customer){
                    if(customer_it.getID() == RevCustomerID){
                        current_account = std::make_shared<Customer>(customer_it);
                        break;
                    }
                }
                auto hotel_iterator = std::find_if(hotel.begin(), hotel.end(), [&](const Hotel& h) {
                    return h.gethName() == RevHotelName;
                });
                if(hotel_iterator != hotel.end()){
                    auto& curr_hotel_vec = hotel_iterator->getVectorReviewPtr();
                    positive_rev->setCustomer(current_account);
                    positive_rev->setRecomended(RecommendedOrNot);
                    positive_rev->getCustomer()->setID(RevCustomerID);
                    positive_rev->setStars(RevStars);
                    positive_rev->setReview(RevText);
                    curr_hotel_vec.push_back(positive_rev);
                }else
                    std::cout << "NOT FOUND !" << std::endl;
            } catch (std::exception &e) {
                setRed;
                std::cout << "Error -> " << e.what() << std::endl;
            }
        }
        else if (dummy1 == "***Negative***") {
            std::shared_ptr<Review> new_review = std::make_shared<NegativeReviews>();
            try {
                auto negative_rev = std::dynamic_pointer_cast<NegativeReviews>(new_review);
                if (negative_rev == nullptr)
                    throw std::runtime_error("Error in converting ptr");

                bool bfoundRevID;
                std::getline(filein, line); // - aici
                if(line.find("ReviewID--> ") != std::string::npos)
                    bfoundRevID = true;
                else
                    bfoundRevID = false;
                if (bfoundRevID)
                {
                    string::size_type foundRevID = line.find("ReviewID--> ");
                    string REVID = line.substr(foundRevID + 12);
                    RevID = stoi(REVID);
                }

                bool bfoundHotelName;
                std::getline(filein, line); // - aici
                if(line.find("Hotel-Name--> ") != std::string::npos)
                    bfoundHotelName = true;
                else
                    bfoundHotelName = false;
                if (bfoundHotelName)
                {
                    string::size_type foundHotelName = line.find("Hotel-Name--> ");
                    string strHotelName = line.substr(foundHotelName + 14);
                    RevHotelName = strHotelName;
                }

                bool bfoundCustomer;
                std::getline(filein, line); // - aici
                if(line.find("CustomerID--> ") != std::string::npos)
                    bfoundCustomer = true;
                else
                    bfoundCustomer = false;
                if (bfoundCustomer)
                {
                    string::size_type foundCustomerID = line.find("CustomerID--> ");
                    string strCustomerID = line.substr(foundCustomerID + 14);
                    RevCustomerID = strCustomerID;
                }

                bool bfoundRating;
                std::getline(filein, line); // - aici
                if(line.find("Rating--> ") != std::string::npos)
                    bfoundRating = true;
                else
                    bfoundRating = false;
                if (bfoundRating)
                {
                    string::size_type foundRating = line.find("Rating--> ");
                    string strRating = line.substr(foundRating + 10);
                    RevStars = stoi(strRating);
                }

                bool bfoundReviewText;
                std::getline(filein, line); // - aici
                if(line.find("Review--> ") != std::string::npos)
                    bfoundReviewText = true;
                else
                    bfoundReviewText = false;
                if (bfoundReviewText)
                {
                    string::size_type foundRating = line.find("Review--> ");
                    string strRating = line.substr(foundRating + 10);
                    RevText = strRating;
                }

                bool bfoundRecommended;
                std::getline(filein, line); // - aici
                if(line.find("Recommended--> ") != std::string::npos)
                    bfoundRecommended = true;
                else
                    bfoundRecommended = false;
                if ( bfoundRecommended)
                {
                    string::size_type foundRecommended = line.find("Not-Recommended--> ");
                    string strReviewText = line.substr(foundRecommended + 19);
                    RecommendedOrNot = (bool) stoi(strReviewText);
                }
                auto current_account = std::make_shared<Customer>();
                for(auto& customer_it : customer){
                    if(customer_it.getID() == RevCustomerID){
                        current_account = std::make_shared<Customer>(customer_it);
                        break;
                    }
                }
                auto hotel_iterator = std::find_if(hotel.begin(), hotel.end(), [&](const Hotel& h) {
                    return h.gethName() == RevHotelName;
                });
                if(hotel_iterator != hotel.end()){
                    auto& curr_hotel_vec = hotel_iterator->getVectorReviewPtr();
                    negative_rev->setCustomer(current_account);
                    negative_rev->setNOTrecomended(RecommendedOrNot);
                    negative_rev->getCustomer()->setID(RevCustomerID);
                    negative_rev->setStars(RevStars);
                    negative_rev->setReview(RevText);
                    curr_hotel_vec.push_back(negative_rev);
                }else
                    std::cout << "NOT FOUND !" << std::endl;
            } catch (std::exception &e) {
                setRed;
                std::cout << "Error -> " << e.what() << std::endl;
            }
        }
    }
    filein.close();
}

void Hotel::ReadFromFile(const char *FILENAME,std::vector<Hotel> &hotel)
{
    std::ifstream filein;
    filein.open(FILENAME);
    if (!filein.is_open())
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