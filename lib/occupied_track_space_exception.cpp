#include "occupied_track_space_exception.hpp"

OccupiedTrackSpaceException::OccupiedTrackSpaceException(int wrong_position):
    std::invalid_argument("Position is taken: " + std::to_string(wrong_position)), position(wrong_position){}

