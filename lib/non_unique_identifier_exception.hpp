#pragma once

#include <stdexcept>
#include <string>


class NonUniqueIdentifierException : public std::invalid_argument
{
    private:
        int number;
    public:
        NonUniqueIdentifierException(int wrong_number);
        int get_number() const;
};
