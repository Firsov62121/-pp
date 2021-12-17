#include "passenger_vessel.h"

namespace SolvingProblems{
PassengerVessel::PassengerVessel(int id, const Destination& dest, int ETA, const ShipProperties& 
    props, int maxpax, int curpax, const std::vector<CabinType> cabContent) :
    Vessel(id, ETA, dest, props), maxpax(maxpax), curpax(curpax), 
    cabin_num(cabContent.size()), cabincontent(new CabinType[cabin_num])
{
    std::copy(cabContent.begin(), cabContent.end(), cabincontent);
}

PassengerVessel::PassengerVessel(const PassengerVessel& other) : Vessel(other.id, other.ETA,
    *other.destination, *other.props), maxpax(other.maxpax), curpax(other.curpax),
    cabin_num(other.cabin_num), cabincontent(new CabinType[cabin_num])
{
    std::copy(other.cabincontent, other.cabincontent + other.cabin_num, cabincontent);
}

PassengerVessel& PassengerVessel::operator=(const PassengerVessel& other)
{
    if(this != &other)
    {
        this->id = other.id;
        this->ETA = other.ETA;
        *(this->destination) = *other.destination;
        *(this->props) = *other.props;
        maxpax = other.maxpax;
        curpax = other.curpax;
        cabin_num = other.cabin_num;
        delete[] cabincontent;
        cabincontent = new CabinType[cabin_num];
        std::copy(other.cabincontent, other.cabincontent + other.cabin_num, cabincontent);
    }
    return *this;
}

PassengerVessel* PassengerVessel::clone() const
{
    return new PassengerVessel(*this);
}

PassengerVessel::~PassengerVessel()
{
    delete[] this->cabincontent;
}

void PassengerVessel::printInOs(std::ostream& os) const
{
    os << *this;
}

std::ostream& operator<<(std::ostream& os, const PassengerVessel& v)
{
    os << "PassengerVessel:" << std::endl;
    os << dynamic_cast<const Vessel&>(v);
    os << "maxpax = " << v.maxpax << std::endl;
    os << "curpax = " << v.curpax << std::endl;
    os << "cabin_num = " << v.cabin_num << std::endl;
    os << "cabincontent = " << std::endl;
    for(int i = 0; i < v.cabin_num; ++i)
    {
        switch (v.cabincontent[i])
        {
        case PassengerVessel::CabinType::LUX:
            os << "LUX";
            break;
        case PassengerVessel::CabinType::FIRSTCLASS:
            os << "FIRSTCLASS";
            break;
        case PassengerVessel::CabinType::SECONDCLASS:
            os << "SECONDCLASS";
            break;
        default:
            break;
        }
        os << std::endl;
    }
    return os;
}
}