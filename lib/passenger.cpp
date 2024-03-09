#include "passenger.hpp"
#include <iostream>
#include <memory>

Passenger::Passenger(int _ID, std::shared_ptr<Station> _origin, std::shared_ptr<Station> _destination, std::shared_ptr<Station> _direction) : ID(_ID), origin(_origin), destination(_destination), direction(_direction)
{
    _origin->receive_passengers_to_station(std::make_unique<Passenger> (*this));    //do stacji początkowej automatycznie zostanie przypisany pasażer
    
}

unsigned Passenger::get_origin_station_ID()
{
    return origin->get_ID();
}

unsigned Passenger::get_destination_station_ID() 
{
    auto temp = destination->get_ID();
    return temp;
}

unsigned Passenger::get_direction_station_ID() 
{
    return direction->get_ID();
}

// void Passenger::set_direction()
// {
//     if(destination->get_ID() > origin->get_ID())
//     {
//         direction = std::make_shared<Station> kabaty;
//     }
// }