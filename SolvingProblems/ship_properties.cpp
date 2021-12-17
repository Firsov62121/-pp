#include "ship_properties.h"
#include <iostream>

namespace SolvingProblems{
ShipProperties::ShipProperties(const std::string& damaged, const std::string& repaired) :
    damaged(new std::string(damaged)), repaired(new std::string(repaired)) {}

ShipProperties::ShipProperties(const ShipProperties& other) :
    damaged(new std::string(*other.damaged)), repaired(new std::string(*other.repaired)) {}

ShipProperties& ShipProperties::operator=(const ShipProperties& other)
{
    if(this != &other)
    {
        *repaired = *other.repaired;
        *damaged = *other.damaged;
    }
    return *this;
}

ShipProperties::~ShipProperties()
{
    delete damaged;
    delete repaired;
}

void ShipProperties::SetRepaired(const std::string& value)
{
    *repaired = value;
}

void ShipProperties::SetDamaged(const std::string& value)
{
    *damaged = value;
}

const std::string& ShipProperties::GetRepaired() const
{
    return *repaired;
}

const std::string& ShipProperties::GetDamaged() const
{
    return *damaged;
}

void ShipProperties::AddRepaired(const std::string& time)
{
    *repaired += (*repaired == "" ? "" : " ") + time;
}

void ShipProperties::AddDamaged(const std::string& time)
{
    *damaged += (*damaged == "" ? "" : " ") + time;
}

std::ostream& operator<<(std::ostream& os, const ShipProperties& v)
{
    os << "ShipProperties:\n";
    os << "damaged = " << *v.damaged << std::endl;
    os << "repaired = " << *v.repaired << std::endl;
    return os;
}
}