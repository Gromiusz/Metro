#include "station.hpp"
#include <iostream>

std::list<std::unique_ptr<Passenger>> Station::dispatch_passengers_to_train(std::shared_ptr<Train> train)
{
    std::list<std::unique_ptr<Passenger>> passengers_to_dispatch;
    for (auto &dispatching_passenger : waitingPassengers)
    {
        if(dispatching_passenger->get_direction_station_ID() == train->get_destination_ID())
        {
            passengers_to_dispatch.push_back(std::move(dispatching_passenger));
        }
    }
    waitingPassengers.remove_if([](const std::unique_ptr<Passenger>& ptr) { return !ptr; });
    return passengers_to_dispatch;
}

void Station::receive_passengers_to_station(std::unique_ptr<Passenger> _name)
{
    waitingPassengers.push_front(std::move(_name));
}

void Station::accept_passengers_from_train(std::list<std::unique_ptr<Passenger>> passengers_from_train)
{
    for(auto& passenger : passengers_from_train)
    {
        passengersLeaveingTheStation.push_back(std::move(passenger));
    }
}

void Station::depart_passengers_from_station()
{
    passengersLeaveingCounter += passengersLeaveingTheStation.size();
    passengersLeaveingTheStation.clear();
}

std::ostream &operator<<(std::ostream &os, Station &_station) 
{
    std::string stationstr;
    stationstr = _station.get_name() + "[" + std::to_string(_station.waitingPassengers.size()) + "] -" + std::to_string(_station.passengersLeaveingTheStation.size());
    os << stationstr;
    return os;
}