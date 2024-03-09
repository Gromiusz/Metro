#include "not_positive_number_exception.hpp"

NotPositiveNumberException::NotPositiveNumberException(int wrong_number):
    std::invalid_argument("Number should be greater than zero: " + std::to_string(wrong_number)), number(wrong_number){}

int NotPositiveNumberException::get_number() const
{
    return number;
}
