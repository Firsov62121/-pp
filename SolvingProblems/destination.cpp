#include <string>
#include "destination.h"

namespace SolvingProblems{
Destination::Destination (int x, int y, std::string description) :
    description(std::move(description)), x(x), y(y) {}

Destination::Destination(const Destination& other) : description(other.description), 
    x(other.x), y(other.y){}

Destination& Destination::operator=(const Destination& other)
{
    if(this != &other)
    {
        description = other.description;
        x = other.x;
        y = other.y;
    }
    return *this;
}

bool Destination::operator==(const Destination& other) const
{
    return other.x == x && other.y == y && other.description == description;
}

std::ostream& operator<<(std::ostream& os, const Destination& v)
{
    os << "Destination:" << std::endl;
    os << "position = (" << v.x << ", " << v.y << ")" << std::endl;
    os << "description = " << v.description << std::endl;
    return os;
}
}