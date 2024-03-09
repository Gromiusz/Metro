#pragma once

#include <stdexcept>
#include <string>


class ObjectInitializedTooCloseException : public std::invalid_argument
{
    private:
        int position;
        int distance;
    public:
        ObjectInitializedTooCloseException(int wrong_position, int _distance);
        int get_position() const {return position;}
        int get_distance() const {return distance;}
};
