#pragma once
#include "NavalFreightCompany.h"

namespace SolvingProblems{
class Audit {//static, namespace, const
public:
    // Узнать есть ли в порту данной компании дежурящие пассажирские суда (у которых destination совпадает с location) //у которых ETA = 0
    static bool isPassengerVesselsInPort(const NavalFreightCompany& nfc);
    static uint getSize(const NavalFreightCompany& nfc);
    static uint getInsecurity(const NavalFreightCompany& nfc);
    // Сравнить две компании, вывести более крупную (считается суммарно), сигнатуру придумать самостоятельно
    static bool secondIsBetter(const NavalFreightCompany& nfc1, const NavalFreightCompany& nfc2);
    // Сравнить две компании, вывести более надежную (меньше когда-либо ремонтировавшихся судов), сигнатуру придумать самостоятельно
    static bool secondIsMoreReiable(const NavalFreightCompany& nfc1, const NavalFreightCompany& nfc2);
    // проинспектировать пассажирский корабль на предмет наличия большего количества людей чем положено по нормативу
    static bool inspectPassengerVessel(const PassengerVessel& v);
    // проинспектировать пассажирский корабль на предмет наличия большего количества контейнеров чем положено по нормативу
    static bool inspectCargoVessel(const CargoVessel& v);
};

}