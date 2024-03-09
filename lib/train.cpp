#include "train.hpp"

// std::list<std::unique_ptr<Passenger>> disembark_passengers()
// {
//     std::list<std::unique_ptr<Passenger>> disambark;
//     do
//     {
//         /* code */
//     } while (find_);

// }

std::list<std::unique_ptr<Passenger>> Train::disembark_passengers()
{
    std::list<std::unique_ptr<Passenger>> disambark;
    for (auto &disambarking_passenger : passengers_on_the_train)
    {
        if(disambarking_passenger!=nullptr && disambarking_passenger->get_destination_station_ID() == currentStation->get_ID())
        {
            disambark.push_back(std::move(disambarking_passenger));
        }
        
    }
    //passengers_on_the_train.remove_if([](const std::unique_ptr<Passenger>& ptr) { return !ptr; });
    passengers_on_the_train.remove_if([](const std::unique_ptr<Passenger>& ptr) { return ptr==nullptr; });
    int a=1;
    return disambark;
}

void Train::board_passengers(std::list<std::unique_ptr<Passenger>> passenger_list)
{
    for (auto &board_passenger : passenger_list)
    {
        passengers_on_the_train.push_back(std::move(board_passenger));
    }
}

unsigned Train::get_destination_ID() 
{
    return destinationStation->get_ID();
}

std::ostream &operator<<(std::ostream &os, Train &_train) 
{
    std::string trainstr;
    trainstr = _train.get_name() + "[" + std::to_string(_train.passengers_on_the_train.size()) + "]";
    os << trainstr;
    return os;
}