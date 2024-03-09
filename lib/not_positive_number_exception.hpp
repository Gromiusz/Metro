#ifndef NOT_POSITIVE_NUMBER_EXCEPTION_HPP
#define NOT_POSITIVE_NUMBER_EXCEPTION_HPP

#include <stdexcept>
#include <string>


class NotPositiveNumberException : public std::invalid_argument
{
    private:
        int number;
    public:
        NotPositiveNumberException(int wrong_number);
        int get_number() const;
};

#endif