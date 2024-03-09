//dokumentacja biblioteki Catch2 znajduje się pod adresem: https://github.com/catchorg/Catch2

#include "catch_amalgamated.hpp"
#include "../lib/passenger.hpp"
#include "../lib/simulation.hpp"
#include "../lib/station.hpp"
#include "../lib/track.hpp"
#include "../lib/train.hpp"
#include "../lib/non_unique_identifier_exception.hpp"
#include "../lib/not_positive_number_exception.hpp"
#include "../lib/object_initialized_too_close_exception.hpp"
#include "../lib/occupied_track_space_exception.hpp"
#include "../lib/position_extends_beyond_the_track_bounds.hpp"
#include "../lib/data_loader.hpp"
#include <sstream>
#include <memory>

TEST_CASE("metro simulation tests", "[metro simulation]") 
{
    std::shared_ptr<Train> train1 = std::make_shared<Train>(1, "train1", 100, 10);
    std::shared_ptr<Train> train2 = std::make_shared<Train>(2, "train2", 100, 10);
    std::shared_ptr<Train> train3 = std::make_shared<Train>(2, "train3", 100, 10);

    std::shared_ptr<Station> station1 = std::make_shared<Station>(1, "station1");
    std::shared_ptr<Station> station2 = std::make_shared<Station>(2, "station2");
    std::shared_ptr<Station> station3 = std::make_shared<Station>(3, "station3");
    std::shared_ptr<Station> station4 = std::make_shared<Station>(3, "station4");

    std::shared_ptr<Track> track1 = std::make_shared<Track>(1, 10);

    std::unique_ptr<Passenger> passenger = std::make_unique<Passenger>(3, station1, station2, station3);
    
    track1->set_station(station1, 2);
    track1->set_station(station2, 5);
    

    // Simulation simulation(track1, 10);


    SECTION("passenger tests of constructors, getters and setters")
    {
        CHECK(passenger->get_direction_station_ID() == 3);
        CHECK(passenger->get_destination_station_ID() == 2);
        CHECK(passenger->get_origin_station_ID() == 1);
    }

    SECTION("station tests")
    {
        CHECK(station1->get_name() == "station1");
        CHECK(station1->get_ID() == 1);
        CHECK(station1->get_position() == 2);
        CHECK(station1->get_waitingPassengers_quantity() == 1);
        CHECK(station1->get_passengersLeavingTheStation_quantity() == 0);
        CHECK(station2->get_waitingPassengers_quantity() == 0);
        station1->set_position(9);
        CHECK(station1->get_position() == 9);
    }
    
    SECTION("train tests")
    {
        CHECK(train1->get_ID() == 1);
        CHECK(train1->get_name() == "train1");
        CHECK(train1->get_status() == go);        
        CHECK(train1->get_passengers_on_the_train_quantity() == 0);
    }

    SECTION("track tests")
    {
        CHECK(track1->get_stations()[0] == station1);
        CHECK(track1->get_stations()[1] == station2);
        CHECK(track1->get_stations().size() == 2);
        CHECK(track1->get_length() == 10);
        CHECK(track1->get_lastStation() == station2);

        std::shared_ptr<Track> track2 = track1->make_reverse_track(2);
        track1->set_reverse_track(track2);
        CHECK(track1->get_reverseTrack() == track2);
        CHECK(track2->get_length() == track1->get_length());
        CHECK(track2->get_stations_on_the_track()[7] == station1);
        CHECK(track2->get_stations_on_the_track()[4] == station2);

        CHECK_THROWS_AS(track1->set_station(station3, 15), PositionExtendsBeyondTheTrackBounds);
        CHECK_THROWS_AS(track1->set_station(station3, 5), OccupiedTrackSpaceException);

        track1->set_station(station3, 9);
        CHECK_THROWS_AS(track1->set_station(station4, 7), NonUniqueIdentifierException);
        CHECK_THROWS_AS(track1->set_train(train1, 15), PositionExtendsBeyondTheTrackBounds);

        track1->set_train(train2, 1);
        CHECK_THROWS_AS(track1->set_train(train2, 1), OccupiedTrackSpaceException);
        CHECK_THROWS_AS(track1->set_train(train3, 2), NonUniqueIdentifierException);
    }
}
