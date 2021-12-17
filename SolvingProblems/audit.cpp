#include "audit.h"

namespace SolvingProblems{//change namespaces
// Узнать есть ли в порту данной компании дежурящие пассажирские суда (у которых destination совпадает с location) //у которых ETA = 0
bool Audit::isPassengerVesselsInPort(const NavalFreightCompany& nfc)
{
    auto location = nfc.getLocation();
    bool res = false;
    nfc.invokeForAll([&location, &res](const Vessel *v){
        if(v->ETA == 0 && location == v->getDestination())
            res = true;
    });
    return res;
}

uint Audit::getSize(const NavalFreightCompany& nfc)
{
    uint res = 0;
    nfc.invokeForAll([&res](const Vessel *v){
        if(v != nullptr)
        {
            if(auto v2 = dynamic_cast<const PassengerVessel* >(v))
            {
                res += v2->maxpax;
            }
            else if(auto v2 = dynamic_cast<const CargoVessel* >(v))
            {
                res += v2->maxcargo;
            }
        }
    });
    return res;
}

uint Audit::getInsecurity(const NavalFreightCompany& nfc)
{
    uint res = 0;
    nfc.invokeForAll([&res](const Vessel *v){
        if(v != nullptr)
            res += (v->getProps().GetRepaired() != "" ? 1 : 0);
    });
    return res;
}

// Сравнить две компании, вывести более крупную (считается суммарно), сигнатуру придумать самостоятельно
bool Audit::secondIsBetter(const NavalFreightCompany& nfc1, const NavalFreightCompany& nfc2)
{
    return getSize(nfc1) < getSize(nfc2);

}
// Сравнить две компании, вывести более надежную (меньше когда-либо ремонтировавшихся судов), сигнатуру придумать самостоятельно
bool Audit::secondIsMoreReiable(const NavalFreightCompany& nfc1, const NavalFreightCompany& nfc2)
{
    return getInsecurity(nfc1) > getInsecurity(nfc2);
}
// проинспектировать пассажирский корабль на предмет наличия большего количества людей чем положено по нормативу
bool Audit::inspectPassengerVessel(const PassengerVessel& v)
{
    return v.maxpax >= v.curpax;
}
// проинспектировать пассажирский корабль на предмет наличия большего количества контейнеров чем положено по нормативу
bool Audit::inspectCargoVessel(const CargoVessel& v)
{
    return v.maxcargo >= v.curcargo;
}

}