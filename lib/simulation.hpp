#include <random>
#include <chrono>
#include <vector>
#include <list>
#include <thread>
#include <iomanip>
#include "passenger.hpp"
#include "station.hpp"
#include "track.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

class Simulation
{
private:
    std::shared_ptr<Track> primalTrack;
    std::shared_ptr<Track> reverseTrack;
    std::vector<std::shared_ptr<Station>> stations;
    std::list<std::unique_ptr<Passenger>> passengers; // lista lepsza przy usuwaniu nieprzewidywalnych elementów, dodatkowa ich liczba sie zmienia cały czas
    int lastID = 0;
    int time;

    std::mt19937 generator; // Generator liczb pseudolosowych

    void load_stations_from_primalTrack() { stations = primalTrack->get_stations(); } // kopiuje zawartosc stacji z toru

    void log_to_console_and_file(const std::string& message);

    std::ofstream log_file;

public:
    Simulation(std::shared_ptr<Track> _primalTrack, int _time);
    void generate_passengers();
    void start_simulation(int simLength);
};