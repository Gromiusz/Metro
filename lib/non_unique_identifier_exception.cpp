#include "non_unique_identifier_exception.hpp"

NonUniqueIdentifierException::NonUniqueIdentifierException(int wrong_number):
    std::invalid_argument("The identifier is repeated: " + std::to_string(wrong_number)), number(wrong_number){}

int NonUniqueIdentifierException::get_number() const
{
    return number;
}
