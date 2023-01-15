#include "globals.h"
#include "response.h"

void Response::setStatus(int status)
{
    _status = status;
}

void Response::outputTo(std::ostream& stream)
{
    stream << format("Status: %d\n") % _status
           << format("Content-Type: %s\n") % _contentType << '\n'
           << this->str();
}
