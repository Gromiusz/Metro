#include "object_initialized_too_close_exception.hpp"

ObjectInitializedTooCloseException::ObjectInitializedTooCloseException(int wrong_position, int _distance):
    std::invalid_argument("The object initialized on position: " + std::to_string(wrong_position) + " is too close to an object" + std::to_string(_distance) + "cells away"), position(wrong_position), distance(_distance){}

