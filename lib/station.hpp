#pragma once
#include <string>
#include <list>
#include <memory>
#include "passenger.hpp"
#include "train.hpp"
#include <iostream>

class Passenger;
class Train;

class Station
{
    unsigned ID;
    std::string name;
    std::list<std::unique_ptr<Passenger>> waitingPassengers;
    std::list<std::unique_ptr<Passenger>> passengersLeaveingTheStation;
    unsigned passengersLeaveingCounter = 0;
    unsigned positionOnTrack;

public:
    Station(unsigned _ID, std::string _name) : ID(_ID), name(_name), positionOnTrack(0) {};

    // gettery
    std::string get_name() { return name; }
    unsigned get_ID() { return ID; }
    unsigned get_position() {return positionOnTrack;}
    unsigned get_waitingPassengers_quantity() {return waitingPassengers.size();} // głownie do testow
    unsigned get_passengersLeavingTheStation_quantity() {return passengersLeaveingTheStation.size();} // głownie do testow

    // settery
    void set_position(int position) {this -> positionOnTrack = position;}
    
    // obsługa pasaer
    std::list<std::unique_ptr<Passenger>> dispatch_passengers_to_train(std::shared_ptr<Train> train);   // wsiadanie do pociągu
    void receive_passengers_to_station(std::unique_ptr<Passenger> _name);   // przychodzenie pasażerów na stacje
    void accept_passengers_from_train(std::list<std::unique_ptr<Passenger>> passengers_from_train);   // przyjmowanie pasażerów z pociągu
    void depart_passengers_from_station(); // opuszczanie stacji

    //std::unique_ptr<Passenger> find_dispatch();
    // bools
    bool is_waitingPassengers_list_empty() {return waitingPassengers.empty();} // potrzebne do testow
    bool is_passengersLeaveingTheStation_list_empty() {return passengersLeaveingTheStation.empty();} // do testow (nie mozna bezpośrednio, bo pole prywatne)

    // friends
    friend std::ostream &operator<<(std::ostream &os, Station &_station);
};

std::ostream &operator<<(std::ostream &os, Station &_station);  //wyświetla nazwę stacji wraz z liczbą oczekujących pasażerów