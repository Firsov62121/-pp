#include "cargo_vessel.h"

#include <cassert>

namespace SolvingProblems{
CargoVessel::CargoVessel(int id, const Destination& dest, int eta, const ShipProperties& props,
    int maxcargo, int curcargo, const std::vector<CargoType> contContent):
    Vessel(id, eta, dest, props), maxcargo(maxcargo), curcargo(curcargo),
    container_num(contContent.size()), containercontent(new CargoType[container_num])
{
    std::copy(contContent.begin(), contContent.end(), containercontent);
}

CargoVessel::~CargoVessel()
{
    delete[] containercontent;
}

CargoVessel::CargoVessel(const CargoVessel& other) : Vessel(other.id, other.ETA, *other.destination,
    *other.props), maxcargo(other.maxcargo), curcargo(other.curcargo), container_num(
    other.container_num), containercontent(new CargoType[container_num])
{
    std::copy(other.containercontent, other.containercontent + container_num, containercontent);
}

CargoVessel& CargoVessel::operator=(const CargoVessel& other)
{
    if(this != &other)
    {
        this->id = other.id;
        this->ETA = other.ETA;
        *(this->destination) = *other.destination;
        *(this->props) = *other.props;
        maxcargo = other.maxcargo;
        curcargo = other.curcargo;
        container_num = other.container_num;
        delete[] containercontent;
        containercontent = new CargoType[maxcargo];
        std::copy(other.containercontent, other.containercontent + container_num + 1, containercontent);
    }
    return *this;
}

CargoVessel* CargoVessel::clone() const{
    return new CargoVessel(*this);
}

void CargoVessel::printInOs(std::ostream& os) const
{
    os << *this;
}

std::ostream& operator<<(std::ostream& os, const CargoVessel& v)
{
    os << "CargoVessel:" << std::endl;
    os << dynamic_cast<const Vessel&>(v);
    os << "maxcargo = " << v.maxcargo << std::endl;
    os << "curcargo = " << v.curcargo << std::endl;
    os << "container_num = " << v.container_num << std::endl;
    os << "containercontent = " << std::endl;
    for(int i = 0; i < v.container_num; ++i)
    {
        switch (v.containercontent[i])
        {
        case CargoVessel::CargoType::GOOD:
            os << "GOOD";
            break;
        case CargoVessel::CargoType::FOOD:
            os << "FOOD";
            break;
        case CargoVessel::CargoType::WOOD:
            os << "WOOD";
        default:
            assert(0);
            break;
        }
        os << std::endl;
    }
    return os;
}
}