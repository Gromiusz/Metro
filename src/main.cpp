#include <iostream>
#include <list>
#include <memory>
#include "../lib/train.hpp"
#include "../lib/track.hpp"
#include "../lib/station.hpp"
#include "../lib/simulation.hpp"
#include <chrono>
#include <thread>
#include <iomanip>
#include <windows.h>
#include "../lib/non_unique_identifier_exception.hpp"
#include "../lib/not_positive_number_exception.hpp"
#include "../lib/object_initialized_too_close_exception.hpp"
#include "../lib/occupied_track_space_exception.hpp"
#include "../lib/position_extends_beyond_the_track_bounds.hpp"
#include "../lib/data_loader.hpp"



int main(int argc, char* argv[])
{
    std::cout << argv[0] << std::endl << argv[1] << std::endl;
    if (argc < 2) {
        std::cerr << "Użycie: " << argv[0] << " [ścieżka_do_pliku_danych]" << std::endl;
        return 1;
    }

    SetConsoleCP(65001);         // Ustawia kodowanie wejściowe konsoli na UTF-8
    SetConsoleOutputCP(65001);   // Ustawia kodowanie wyjściowe konsoli na UTF-8

    try
    {
        // int time = 10; //ustawianie prędkości symulacji
        // int simulationLength = 80;

        // std::cout << "Witamy w symulatorze metra\n";

        // std::shared_ptr<Train> chrobry = std::make_shared<Train>(1, "Chrobry", 100, 10);
        // std::shared_ptr<Train> sobieski = std::make_shared<Train>(2, "Sobieski", 100, 10);
        // std::shared_ptr<Train> kazimierz = std::make_shared<Train>(3, "Kazimierz", 100, 10);
        // std::shared_ptr<Train> lokietek = std::make_shared<Train>(4, "Łokietek", 100, 10);

        // std::shared_ptr<Station> kabaty = std::make_shared<Station>(1, "Kabaty");
        // // std::shared_ptr<Station> natolin = std::make_shared<Station>(2, "Natolin");
        // // std::shared_ptr<Station> imielin = std::make_shared<Station>(3, "Imielin");
        // // std::shared_ptr<Station> stoklosy = std::make_shared<Station>(4, "Stokłosy");
        // std::shared_ptr<Station> ursynow = std::make_shared<Station>(5, "Ursynów");
        // // std::shared_ptr<Station> sluzew = std::make_shared<Station>(6, "Służew");
        // // std::shared_ptr<Station> wilanowska = std::make_shared<Station>(7, "Wilanowska");
        // std::shared_ptr<Station> wierzbno = std::make_shared<Station>(8, "Wierzbno");
        // // std::shared_ptr<Station> raclawicka = std::make_shared<Station>(9, "Racławicka");
        // // std::shared_ptr<Station> poleMokotowskie = std::make_shared<Station>(10, "Pole Mokotowskie");
        // std::shared_ptr<Station> politechnika = std::make_shared<Station>(11, "Politechnika");
        // std::shared_ptr<Station> centrum = std::make_shared<Station>(13, "Centrum");
        // // std::shared_ptr<Station> swietokrzyska = std::make_shared<Station>(14, "Świętokrzyska");
        // // std::shared_ptr<Station> ratuszArsenal = std::make_shared<Station>(15, "Ratusz Arsenał");
        // std::shared_ptr<Station> dworzecGdanski = std::make_shared<Station>(16, "Dworzec Gdański");
        // // std::shared_ptr<Station> placWilsona = std::make_shared<Station>(17, "Plac Wilsona");
        // // std::shared_ptr<Station> marymont = std::make_shared<Station>(18, "Marymont");
        // std::shared_ptr<Station> slodowiec = std::make_shared<Station>(19, "Słodowiec");
        // // std::shared_ptr<Station> stareBielany = std::make_shared<Station>(20, "Stare Bielany");
        // // std::shared_ptr<Station> wawrzyszew = std::make_shared<Station>(21, "Wawrzyszew");
        // std::shared_ptr<Station> mlociny = std::make_shared<Station>(22, "Młociny");

        // // std::unique_ptr<Passenger> Karol = std::make_unique<Passenger>(1, kabaty, politechnika, mlociny);
        // // std::unique_ptr<Passenger> Kacper = std::make_unique<Passenger>(2, kabaty, politechnika, mlociny);
        // // std::unique_ptr<Passenger> random1 = std::make_unique<Passenger>(3, wierzbno, dworzecGdanski, mlociny);
        // // std::unique_ptr<Passenger> random2 = std::make_unique<Passenger>(4, politechnika, slodowiec, mlociny);
        // // std::unique_ptr<Passenger> random3 = std::make_unique<Passenger>(5, ursynow, mlociny, mlociny);
        // // std::unique_ptr<Passenger> random4 = std::make_unique<Passenger>(6, dworzecGdanski, mlociny, mlociny);
        // // std::unique_ptr<Passenger> random5 = std::make_unique<Passenger>(7, slodowiec, wierzbno, kabaty);
        
        // std::shared_ptr<Track> track1 = std::make_shared<Track>(1, 42);

        // track1->set_station(kabaty, 3);
        // track1->set_station(ursynow, 7);
        // track1->set_station(wierzbno, 13);
        // track1->set_station(politechnika, 18);
        // track1->set_station(centrum, 23);
        // track1->set_station(dworzecGdanski, 28);
        // track1->set_station(slodowiec, 33);
        // track1->set_station(mlociny, 38);


        // std::shared_ptr<Track> track2 = track1->make_reverse_track(2);
        // track1->set_reverse_track(track2);
        // track2->set_reverse_track(track1);

        // track1->set_train(chrobry, 1);
        // track1->set_train(sobieski, 10);
        // track2->set_train(kazimierz, 21);
        // track2->set_train(lokietek, 6);

        // Simulation simulation(track1, time);
        // simulation.start_simulation(simulationLength);
        std::string filename = argv[1];
        DataLoader loader;
        
        int time, simulationLength, trackLength;
        std::vector<std::pair<std::shared_ptr<Train>, int>> trainPositions;
        std::vector<std::pair<std::shared_ptr<Station>, int>> stationPositions;
        std::vector<bool> reverseFlags; 

        loader.load(filename, time, simulationLength, trackLength, trainPositions, stationPositions, reverseFlags);
        auto track = std::make_shared<Track>(1, trackLength);


        for (const auto& [station, position] : stationPositions) {
            track->set_station(station, position);
        }

        auto reverseTrack = track->make_reverse_track(2);
        track->set_reverse_track(reverseTrack);
        reverseTrack->set_reverse_track(track);

        for (size_t i = 0; i < trainPositions.size(); ++i) {
            const auto& [train, position] = trainPositions[i];
            if (reverseFlags[i]) {
                reverseTrack->set_train(train, position); // Ustawienie pociągu na torze odwrotnym
            } else {
                track->set_train(train, position); // Ustawienie pociągu na głównym torze
            }
        }

        Simulation simulation(track, time);
        simulation.start_simulation(simulationLength);
    }
    catch(const NotPositiveNumberException& npne)
    {
        std::cerr << npne.what() << std::endl;
    }
    catch(const NonUniqueIdentifierException& nuid)
    {
        std::cerr << nuid.what() << std::endl;
    }
    catch(const ObjectInitializedTooCloseException& oitce)
    {
        std::cerr << oitce.what() << std::endl;
    }
    catch(const OccupiedTrackSpaceException& otse)
    {
        std::cerr << otse.what() << std::endl;
    }
    catch(const PositionExtendsBeyondTheTrackBounds& pebtb)
    {
        std::cerr << pebtb.what() << std::endl;
    }
    catch (const std::exception& e) 
    {
        std::cerr << "Wystąpił błąd: " << e.what() << std::endl;
        return 1;
    }

   

    

    // for (int i = 0; i < 80; i++) // wyświetlenie poruszającego się pociągu
    // {
    //     track1->move_trains();
    //     track1->check_visit();

    //     std::cout << std::setprecision(2) << std::fixed
    //               << static_cast<double>(i) * 15.0 / 60.0 << " min: \n"
    //               << *track1 << std::endl;

    //     track2->move_trains();
    //     track2->check_visit();
        
    //     std::cout << std::setprecision(2) << std::fixed
    //               << static_cast<double>(i) * 15.0 / 60.0 << " min: \n"
    //               << *track2 << std::endl;

    //     std::this_thread::sleep_for(std::chrono::milliseconds(time));
    // }
}