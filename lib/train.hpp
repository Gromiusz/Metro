#pragma once
#include <string>
#include <list>
#include <memory>
#include "station.hpp"
#include "passenger.hpp"

class Station;
class Passenger;

enum MoveStatus
{
    stop,
    go
};

enum OnStation
{
    yes,
    no
};
// nie wiem czy nie lepiej zrobić bool OnStation i w sumie można też zrobić bool MoveStatus. Albo je połączyć i będzie enum: stop, inMotion, onStation

class Train
{
protected:
    unsigned ID;
    std::string name;
    unsigned capacity; // maksymalna pojemność pasażerów
    unsigned numberOfDoors;
    MoveStatus status; // stoi lub jedzie
    OnStation onStat;  // jest na stacji lub jedzie
    std::shared_ptr<Station> currentStation;
    std::shared_ptr<Station> destinationStation;
    std::list<std::unique_ptr<Passenger>> passengers_on_the_train;
    // std::unique_ptr<Passenger> find_outgoing_passenger(unsigned _ID); // wysiadający pasażerowie, narazie niepotrzebne

public:
    Train(unsigned _ID, std::string _name, unsigned _capacity, unsigned _numberOfDoors) : ID(_ID), name(_name), capacity(_capacity), numberOfDoors(_numberOfDoors), status(go), onStat(no){};

    // gettery
    std::string get_name() { return name; }
    MoveStatus get_status() { return status; }
    OnStation is_on_station() { return onStat; }
    std::shared_ptr<Station> get_destination() { return destinationStation; }
    std::shared_ptr<Station> get_currentStation() { return currentStation; }
    unsigned get_ID() {return ID;}
    unsigned get_destination_ID();
    unsigned get_passengers_on_the_train_quantity() {return passengers_on_the_train.size();} // głownie do testow

    // settery
    void set_status(MoveStatus _status) { status = _status; }    // czy jedzie czy stoi
    void set_on_station(OnStation _onStat) { onStat = _onStat; } // jest na stacji czy poza
    void set_destination_station(std::shared_ptr<Station> _station) { destinationStation = _station; }

    // obsługa pasazerow
    void arrive_at_the_station(std::shared_ptr<Station> _visitedStation) { currentStation = _visitedStation; }
    void depart_from_the_station() { currentStation = nullptr; }
    std::list<std::unique_ptr<Passenger>> disembark_passengers();                // przekazanie listy wysiadających pasażerów
    void board_passengers(std::list<std::unique_ptr<Passenger>> passenger_list); // przyjęcie pasażerów na pokład

    // boole
    bool is_passengers_on_the_train_list_empty() {return passengers_on_the_train.empty();} // potrzebne do testow

    
    // friends
    friend std::ostream &operator<<(std::ostream &os, Train &_train);
};

std::ostream &operator<<(std::ostream &os, Train &_train);
