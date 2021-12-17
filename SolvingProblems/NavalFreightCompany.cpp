#include "NavalFreightCompany.h"

namespace SolvingProblems{
void NavalFreightCompany::invokeForAll(std::function<void(const Vessel *)> f) const
{
    std::for_each(ships.begin(), ships.end(), f);
}

const Destination NavalFreightCompany::getLocation() const
{
    if(location == nullptr)
        return Destination();
    return *location;
}

// добавление корабля
void NavalFreightCompany::add(Vessel* v, Destination* d)
{
    if(v == nullptr)
        return;
    v->setDestination(*d);
    ships.insert(ships.begin(), v);
}

void NavalFreightCompany::add(Vessel* v)
{
    ships.insert(ships.begin(), v);
}
// удаление корабля
int NavalFreightCompany::remove(Vessel* v)
{
    if(v == nullptr)
        return -1;
    remove(v->id);
    return 0;
}

int NavalFreightCompany::remove(int id)
{
    int res = -1;
    ships.remove_if([&res, id](const Vessel* v){
        bool tmp = (v != nullptr && v->id == id);
        if(tmp)
        {
            res = 0;
            delete v;
        }
        return tmp;
    });
    return res;
}
// место где порт расположен

// списать весь хлам - когда-либо ремонтировавшиеся суда
void NavalFreightCompany::draft()
{
    ships.remove_if([](Vessel* v){
        if(v == nullptr)
            return true;
        bool res = (v->getProps().GetDamaged() == "" &&
            v->getProps().GetRepaired() != "");
        if(res)
            delete v;
        return res;
    });
}
// напечатать статистику: сколько пассажирских, сколько грузовых, из них когда-либо ломавшихся
void NavalFreightCompany::printStats(std::ostream& os) const
{
    uint dCargo = 0;
    uint dPassenger = 0;
    std::for_each(ships.begin(), ships.end(), [&os, &dPassenger, &dCargo](Vessel* v){
        if(v == nullptr)
            return;
        if(dynamic_cast<PassengerVessel*>(v))
        {
            if(v->getProps().GetDamaged() != "")
                ++dPassenger;
        }
        else if(dynamic_cast<CargoVessel*>(v))
        {
            if(v->getProps().GetDamaged() != "")
                ++dCargo;
        }
    });
    os << "amount of damaged CargoVessels = " << dCargo << std::endl;
    os << "amount of damaged PassengerVessels = " << dPassenger << std::endl;
}
// внести запись о ремонте корабля по id
void NavalFreightCompany::markRepaired(int id, const std::string& date_repaired)
{
    std::for_each(ships.begin(), ships.end(), [id, &date_repaired](Vessel* v){
        if(v == nullptr)
            return;
        if(v->id == id)
        {
            v->getProps().AddRepaired(date_repaired);
        }
    });
}
// внести запись о повреждении корабля по id
void NavalFreightCompany::markDamaged(int id, const std::string& date_damaged)
{
    std::for_each(ships.begin(), ships.end(), [id, &date_damaged](Vessel* v){
        if(v == nullptr)
            return;
        if(v->id == id)
        {
            v->getProps().AddDamaged(date_damaged);
        }
    });
}
// поменять пункт назначения корабля
int NavalFreightCompany::changeDestination(int id, const Destination& dest)
{
    int res = -1;
    std::for_each(ships.begin(), ships.end(), [id, &res, &dest](Vessel* v){
        if(v == nullptr)
            return;
        if(v->id == id)
        {
            res = 0;
            v->setDestination(dest);
        }
    });
    return res;
}
// напечатать сколько кораблей идут в пункт назначения X
void NavalFreightCompany::printHeadingTo(std::ostream& os, std::string s) const
{
    uint count = 0;
    std::for_each(ships.begin(), ships.end(), [&os, &s, &count](Vessel* v){
        if(v == nullptr)
            return;
        if(v->getDestination().description == s)
            ++count;
    });
    os << "number of vessels going to " << s << " = " << count << std::endl;
}

NavalFreightCompany::NavalFreightCompany(const Destination& location) : location(new Destination(location)){}

NavalFreightCompany::~NavalFreightCompany()
{
    delete location;
    for(Vessel* v : ships)
        delete v;
    ships.clear();
}

std::ostream& operator<<(std::ostream& os, const NavalFreightCompany& n)
{
    n.invokeForAll([&os](const Vessel *v){
        if(v != nullptr)
            v->printInOs(os);
    });
    os << std::endl;
    return os;
}
}