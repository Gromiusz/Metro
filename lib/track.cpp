#include "track.hpp"
#include <memory>
#include <algorithm>
#include <iomanip>
#include "non_unique_identifier_exception.hpp"
#include "object_initialized_too_close_exception.hpp"
#include "occupied_track_space_exception.hpp"
#include "position_extends_beyond_the_track_bounds.hpp"
#include "../lib/not_positive_number_exception.hpp"

void Track::designate_lastStationPosition()
{
    unsigned auxLastPos = 0;
    for (auto &station : stationsOnTheTrack)
    {
        if (station != nullptr)
        {
            if (station->get_position() >= auxLastPos)
            {
                auxLastPos = station->get_position();
            }
        }
    }
    if (auxLastPos >= lastStationPosition)
    {
        lastStationPosition = auxLastPos;
    }
}

Track::Track(unsigned _ID, unsigned _length) : ID(_ID), length(_length)
{
    trainsOnTheTrack.reserve(_length);
    stationsOnTheTrack.reserve(_length);

    for (int i = 0; i < _length; ++i)
    {
        trainsOnTheTrack.push_back(nullptr); // Dodawanie pustych shared_ptr (nullptr) do wektora
        stationsOnTheTrack.push_back(nullptr);
    }
    lastStationPosition = 0;
}

void Track::set_train(std::shared_ptr<Train> train, unsigned position)
{
    if (position >= length)
        throw PositionExtendsBeyondTheTrackBounds(position, length);
    if (position < length && trainsOnTheTrack[position] != nullptr)
        throw OccupiedTrackSpaceException(position);
    for (const auto &checkedTrain : trainsOnTheTrack)
    {
        if (checkedTrain != nullptr)
        {
            if (checkedTrain->get_ID() == train->get_ID())
                throw NonUniqueIdentifierException(train->get_ID());
        }
    }
    for (int i = 1; i < 5; i++)
    {
        int position2;
        if (position > 0)
        {
            position2 = static_cast<int>(position);
        }
        else
        {
            position2 = 0;
        }
        if (trainsOnTheTrack[std::max(position2 - i, 0)] != nullptr || trainsOnTheTrack[position2 + i, length - 1] != nullptr)
        {
            throw ObjectInitializedTooCloseException(position, i);
        }
    }

    trainsOnTheTrack[position] = train;
    train->set_destination_station(lastStation);
    
}

void Track::set_station(std::shared_ptr<Station> station, unsigned position)
{
    if (stationsOnTheTrack[position] != nullptr && position < length)
        throw OccupiedTrackSpaceException(position);
    if (position >= length)
        throw PositionExtendsBeyondTheTrackBounds(position, length);
    for (const auto &checkedStation : stationsOnTheTrack)
    {
        if (checkedStation != nullptr)
        {
            if (checkedStation->get_ID() == station->get_ID())
                throw NonUniqueIdentifierException(station->get_ID());
        }
    }
    for (int i = 1; i < 3; i++)
    {
        int position2;
        if (position > 0)
        {
            position2 = static_cast<int>(position);
        }
        else
        {
            position2 = 0;
        }
        if (trainsOnTheTrack[std::max(position2 - i, 0)] != nullptr || trainsOnTheTrack[position2 + i, length - 1] != nullptr)
        {
            throw ObjectInitializedTooCloseException(position, i);
        }
    }

    stationsOnTheTrack[position] = station;
    station->set_position(position);
    designate_lastStationPosition();
    lastStation = stationsOnTheTrack[lastStationPosition];
    // find_station_with_last_position();
}

std::vector<std::shared_ptr<Station>> Track::get_stations() const
{
    std::vector<std::shared_ptr<Station>> stationsCopy;
    for (auto station : stationsOnTheTrack)
    {
        if (station != nullptr)
        {
            stationsCopy.push_back(station);
        }
    }
    return stationsCopy;
}

void Track::move_trains()
{
    for (int i = length - 2; i >= 0; i--)
    {
        if (trainsOnTheTrack[i] != nullptr && trainsOnTheTrack[i]->get_status() == go)
        {
            if (trainsOnTheTrack[i + 1] == nullptr)
            {
                trainsOnTheTrack[i + 1] = std::move(trainsOnTheTrack[i]);
            }
        }
        if (trainsOnTheTrack[length - 1] != nullptr)
        {
            reverseTrack->set_train(std::move(trainsOnTheTrack[length - 1]), 0);
        }
    }
}

void Track::check_visit()
{
    for (int i = 0; i <= length - 1; i++)
    {
        if (trainsOnTheTrack[i] != nullptr && stationsOnTheTrack[i] != nullptr)
        {
            if (trainsOnTheTrack[i]->get_status() == go && trainsOnTheTrack[i]->is_on_station() == no)
            {
                trainsOnTheTrack[i]->set_status(stop);
                trainsOnTheTrack[i]->set_on_station(yes);
                trainsOnTheTrack[i]->arrive_at_the_station(stationsOnTheTrack[i]);
                std::cout << "Pociąg " << *trainsOnTheTrack[i] << " wjeżdża na stację " << *stationsOnTheTrack[i] << "." << std::endl;
            }
            else if (trainsOnTheTrack[i]->get_status() == stop && trainsOnTheTrack[i]->is_on_station() == yes)
            {
                // trainsOnTheTrack[i]->set_status(stop);
                // trainsOnTheTrack[i]->set_on_station(yes);
                exchange_passengers(trainsOnTheTrack[i], stationsOnTheTrack[i]);
                trainsOnTheTrack[i]->set_on_station(no);
                std::cout << "Wymiana pasażerów" << std::endl;
            }
            else if (trainsOnTheTrack[i]->get_status() == stop && trainsOnTheTrack[i]->is_on_station() == no)
            {
                std::cout << "Pociąg " << *trainsOnTheTrack[i] << " odjeżdża ze stacji " << *stationsOnTheTrack[i] << "." << std::endl;
                trainsOnTheTrack[i]->set_status(go);
            }
        }
    }
}

void Track::exchange_passengers(std::shared_ptr<Train> train, std::shared_ptr<Station> station)
{
    // std::list<std::unique_ptr<Passenger> alightingPassengers;
    station->accept_passengers_from_train(std::move(train->disembark_passengers()));
    train->board_passengers(std::move(station->dispatch_passengers_to_train(train)));
}

// std::unique_ptr<Passenger> Track::find_passenger(unsigned _ID)
// {
//     auto passenger_iterator = std::find_if(waitingPassengers.begin(), waitingPassengers.end(),
//                                 [&](const auto& passenger_ptr){return (passenger_ptr->get_destination_ID() == ...)});
//     if(passenger_iterator != ... .end())
//     {
//         return *passenger_iterator;
//     }
// }

// std::unique_ptr<Track> Track::make_reverse_track(unsigned ID)
std::shared_ptr<Track> Track::make_reverse_track(unsigned ID)
{
    // std::unique_ptr<Track> track = std::make_unique<Track>(ID, this->length);
    std::shared_ptr<Track> track = std::make_shared<Track>(ID, this->length);
    for (auto &station : stationsOnTheTrack)
    {
        if (station != nullptr)
        {
            track->set_station(station, track->get_length() - station->get_position() - 1);
        }
    }
    return track;
}

std::ostream &operator<<(std::ostream &os, Track &track)
{
    std::shared_ptr<Track> reverseTrack = track.get_reverseTrack();
    for (int i = 0; i < track.length; i++)
    {
        os << std::setw(2) << std::right << i << ".";
        if (track.trainsOnTheTrack[i] != nullptr)
        {
            os << std::setw(16) << std::right << *(track.trainsOnTheTrack[i]) << " || ";
        }
        else
        {
            os << std::setw(16) << std::right << " " << " || ";
        }
        if (track.stationsOnTheTrack[i] != nullptr)
        {
            os << std::setw(30) << std::right << *(track.stationsOnTheTrack[i]) << " || ";
        }
        else
        {
            os << std::setw(30) << std::right << " " << " || ";
        }

        if (reverseTrack->trainsOnTheTrack[track.length - i - 1] != nullptr)
        {
            os << std::setw(16) << std::left << *(reverseTrack->trainsOnTheTrack[track.length - i - 1]);

        }
        else
        {
            os << std::setw(16) << std::left << " ";

        }

        os << std::endl;
    }
    return os;
}