#pragma once
#include <list>
#include "cargo_vessel.h"
#include "passenger_vessel.h"
#include <functional>
#include <algorithm>
#include <string.h>
#include <typeinfo>

namespace SolvingProblems{
class NavalFreightCompany {
private:
    // имеющиеся корабли
    std::list<Vessel*> ships;
    Destination* location;
public:

    void invokeForAll(std::function<void(const Vessel *)> f) const;//template callable (погугли)
    const Destination getLocation() const;
    // добавление корабля
    void add(Vessel* v, Destination* d);
    void add(Vessel* v);
    // удаление корабля
    int remove(Vessel* v);
    int remove(int id);
    // место где порт расположен
    
    // списать весь хлам - когда-либо ремонтировавшиеся суда
    void draft();
    // напечатать статистику: сколько пассажирских, сколько грузовых, из них когда-либо ломавшихся
    void printStats(std::ostream& os) const;
    // внести запись о ремонте корабля по id
    void markRepaired(int id, const std::string& date_repaired);
    // внести запись о повреждении корабля по id
    void markDamaged(int id, const std::string& date_damaged);
    // поменять пункт назначения корабля
    int changeDestination(int id, const Destination& dest);
    // напечатать сколько кораблей идут в пункт назначения X
    void printHeadingTo(std::ostream& os, std::string s) const;
    // Печать всех данных о компании
    friend std::ostream& operator<<(std::ostream& os, const NavalFreightCompany& v);

    NavalFreightCompany() = default;
    NavalFreightCompany(const Destination& location);
    ~NavalFreightCompany();
};
}