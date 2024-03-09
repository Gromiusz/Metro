#include "simulation.hpp"
#include "not_positive_number_exception.hpp"
#include <cmath>

Simulation::Simulation(std::shared_ptr<Track> _primalTrack, int _time)
    : primalTrack(_primalTrack), time(_time)
{
    if(time<=0)
        throw NotPositiveNumberException(time);
    reverseTrack = primalTrack->get_reverseTrack();
    load_stations_from_primalTrack();
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    generator.seed(seed);
}

void Simulation::generate_passengers()
{
    std::uniform_int_distribution<int> passenger_distribution(0, 5);
    std::uniform_int_distribution<int> station_distribution(0, stations.size() - 1);

    int num_passengers = passenger_distribution(generator);

    for (int i = 0; i < num_passengers; ++i)
    {
        auto origin = stations[station_distribution(generator)];
        auto destination = stations[station_distribution(generator)];
       
        while(origin->get_position() == destination->get_position())
            {
                destination = stations[station_distribution(generator)];
            }
        
        std::shared_ptr<Station> direction;
        if (origin->get_position() > destination->get_position())
        {
            direction = primalTrack->get_lastStation();
        }
        else// if (origin->get_position() > destination->get_position())
        {
            direction = reverseTrack->get_lastStation();
        }
        // else // origin i destination takie same
        // {
        //     if((origin->get_position()+2) > (primalTrack->get_length()-3))
        //     {
        //         destination = stations[origin->get_position()+2]; // 3 stacje dalej
        //         direction = primalTrack->get_lastStation();
        //     }
        //     else
        //     {
        //         destination = stations[origin->get_position()-2]; // 3 stacje dalej
        //         direction = reverseTrack->get_lastStation();
        //     }
        // }

        passengers.emplace_back(std::make_unique<Passenger>(lastID++, origin, destination, direction));
    }
}

// void Simulation::start_simulation(int simLength)
// {
//     if(simLength<=0)
//         throw NotPositiveNumberException(simLength);
//     for (int i = 0; i < simLength; i++) // wyświetlenie poruszającego się pociągu
//     {
//         generate_passengers();

//         primalTrack->move_trains();
//         primalTrack->check_visit();

//         std::cout << std::setprecision(2) << std::fixed
//                   << static_cast<double>(i) * 15.0 / 60.0 << " min: \n"
//                   << *primalTrack << std::endl;

//         reverseTrack->move_trains();
//         reverseTrack->check_visit();

//         std::cout << std::setprecision(2) << std::fixed
//                   << static_cast<double>(i) * 15.0 / 60.0 << " min: \n"
//                   << *reverseTrack << std::endl;

//         std::this_thread::sleep_for(std::chrono::milliseconds(time));
//     }
// }
void Simulation::log_to_console_and_file(const std::string& message) {
    std::cout << message;
    log_file << message;
}

void Simulation::start_simulation(int simLength) {
    log_file.open("simulation_log.txt", std::ios::out | std::ios::trunc);

    if(simLength<=0)
        throw NotPositiveNumberException(simLength);

    for (int i = 0; i < simLength; i++) {
        generate_passengers();

        primalTrack->move_trains();
        primalTrack->check_visit();
        reverseTrack->move_trains();
        reverseTrack->check_visit();

        double hour = static_cast<double>(i) * 15.0 / 360;

        std::stringstream log_stream;
        log_stream << std::setprecision(2) << std::fixed
                   << static_cast<int>(static_cast<double>(i) * 15.0 / 3600) << ":" << std::setw(5) << std::setfill('0') << fmod(static_cast<double>(i) * 15.0/60, 60) << std::setfill(' ') << std::endl
                   << *primalTrack << std::endl;
        
        log_to_console_and_file(log_stream.str());


        // log_stream.str(""); // Czyszczenie strumienia
        // log_stream << std::setprecision(2) << std::fixed
        //            << static_cast<double>(i) * 15.0 / 60.0 << " min: \n"
        //            << *reverseTrack << std::endl;

        // log_to_console_and_file(log_stream.str());

        std::this_thread::sleep_for(std::chrono::milliseconds(time));
    }

    log_file.close(); // Zamknięcie pliku po zakończeniu symulacji
}