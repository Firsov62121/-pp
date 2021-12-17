#include "vessel.h"

namespace SolvingProblems{
Vessel::Vessel(int id, int ETA, const Destination& dest, 
    const ShipProperties& props) : destination(new Destination(dest)),
    props(new ShipProperties(props)), id(id), ETA(ETA){}

Vessel::Vessel(const Vessel& other): destination(new Destination(*other.destination)), props(new ShipProperties(*other.props)),
    id(other.id), ETA(other.ETA){}

Vessel& Vessel::operator=(const Vessel& other)
{
    if(this != &other)
    {
        id = other.id;
        ETA = other.ETA;
        *destination = *other.destination;
        *props = *other.props;
    }
    return *this;
}

Vessel::~Vessel()
{
    delete destination;
    delete props;
}
// операция клонирования, должна присутствовать во всех наследуемых классах
Vessel* Vessel::clone() const
{
    return new Vessel(*this);
}

void Vessel::setDestination(const Destination& value)
{
    *destination = value;
}

void Vessel::setProps(const ShipProperties& value)
{
    *props = value;
}

const Destination& Vessel::getDestination() const
{
    return *destination;
}

const ShipProperties& Vessel::getProps() const
{
    return *props;
}

Destination& Vessel::getDestination()
{
    return *destination;
}

ShipProperties& Vessel::getProps()
{
    return *props;
}

std::ostream& operator<<(std::ostream& os, const Vessel& v)
{
    os << "Vessel:" << std::endl;
    os << "id = " << v.id << std::endl;
    os << *v.destination;
    os << *v.props;
    os << "ETA = " << v.ETA << std::endl;
    return os;
}

void Vessel::printInOs(std::ostream& os) const
{
    os << *this;
}
}