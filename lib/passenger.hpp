#pragma once
#include <string>
#include <memory>
#include "station.hpp"

class Station;

class Passenger
{
private:
    int ID;
    // std::string name; to może później
    std::shared_ptr<Station> origin;
    std::shared_ptr<Station> destination;
    std::shared_ptr<Station> direction; // stacja końcowa na danym kierunku; pociągu przez daną stację przejeżdzają z dwóch różnych kierunków. Direction pomoże określić do którego pociągu psażer ma wsiąść
    
    // void set_direction();

public:
    Passenger(int _ID, std::shared_ptr<Station> _origin, std::shared_ptr<Station> _destination, std::shared_ptr<Station> _direction);
    unsigned get_origin_station_ID();
    unsigned get_destination_station_ID();
    unsigned get_direction_station_ID();
    // unsigned get_origin_station_ID() {return origin->get_ID();}
    // unsigned get_destination_station_ID() {return destination->get_ID();}
    // unsigned get_direction_station_ID() {return direction->get_ID();}

    // void designate_direction();

    ~Passenger() = default;
};
