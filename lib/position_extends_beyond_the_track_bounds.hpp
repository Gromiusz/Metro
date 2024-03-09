#pragma once

#include <stdexcept>
#include <string>


class PositionExtendsBeyondTheTrackBounds : public std::invalid_argument
{
    private:
        int position;
        int length;
    public:
        PositionExtendsBeyondTheTrackBounds(int _position, int _length);
        int get_position() const {return position;}
        int get_length() const {return length;}
};
