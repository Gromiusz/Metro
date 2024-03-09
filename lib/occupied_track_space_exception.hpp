#pragma once

#include <stdexcept>
#include <string>


class OccupiedTrackSpaceException : public std::invalid_argument
{
    private:
        int position;
    public:
        OccupiedTrackSpaceException(int wrong_position);
        int get_position() const {return position;};
};
