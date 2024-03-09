#include "position_extends_beyond_the_track_bounds.hpp"

PositionExtendsBeyondTheTrackBounds::PositionExtendsBeyondTheTrackBounds(int _position, int _length):
    std::invalid_argument("The selected position: " + std::to_string(_position) + " exceeds the track length: "), position(_position), length(_length) {}
