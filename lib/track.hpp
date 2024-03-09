#pragma once
#include <memory>
#include <list>
#include <vector>
#include "train.hpp"
// #include "passenger_train.hpp"
#include "station.hpp"
#include <iostream>
#include <vector>
#include <algorithm>


class Track
{
    unsigned ID;
    unsigned length;
    unsigned lastStationPosition;
    std::shared_ptr<Station> lastStation;
    std::shared_ptr<Track> reverseTrack;

    std::vector<std::shared_ptr<Train>> trainsOnTheTrack;
    std::vector<std::shared_ptr<Station>> stationsOnTheTrack;

    // void find_station_with_last_position();
    void designate_lastStationPosition();

public:
    Track(unsigned _ID, unsigned _length);
    void set_train(std::shared_ptr<Train> train, unsigned position);
    void set_station(std::shared_ptr<Station> station, unsigned position);
    void set_reverse_track(std::shared_ptr<Track> _reverse) {reverseTrack = _reverse;}

    unsigned get_length() const { return length; }
    std::vector<std::shared_ptr<Station>> get_stations() const;
    std::vector<std::shared_ptr<Station>> get_stations_on_the_track() const {return stationsOnTheTrack; } //na potrzeby testów
    std::shared_ptr<Station> get_lastStation() const {return lastStation;}
    std::shared_ptr<Track> get_reverseTrack() const {return reverseTrack;}


    void move_trains(); // symulacja ruchu pociągu jako przemieszczenie o jeden ideks w wektorze obrazującym tor
    void check_visit(); // sprawdzenie czy pozycja pociągu jest taka jak pozycja stacji
    void exchange_passengers(std::shared_ptr<Train> train, std::shared_ptr<Station> station); // wymiana pasażerów
    std::shared_ptr<Passenger> find_passenger(unsigned _ID);

    std::shared_ptr<Track> make_reverse_track(unsigned ID); //tworzy tor w przeciwną stronę

    friend std::ostream &operator<<(std::ostream &os, Track &track);
};

std::ostream &operator<<(std::ostream &os, Track &track);