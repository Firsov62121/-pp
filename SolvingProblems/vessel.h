#pragma once
#include "destination.h"
#include "ship_properties.h"

namespace SolvingProblems{
class Vessel {
protected:
    // пункт назначения
    Destination* destination;
    // свойства корабля
    ShipProperties* props;
public:
    // уникальный идентификатор
    int id;
    // сколько дней осталось время до прибытия
    int ETA;

    Vessel(int id, int ETA = 0, const Destination& dest = Destination(), 
        const ShipProperties& props = ShipProperties());
    Vessel(const Vessel& other);
    virtual ~Vessel();
    Vessel& operator=(const Vessel& other);
    
    // операция клонирования, должна присутствовать во всех наследуемых классах
    virtual Vessel* clone() const;
    virtual void printInOs(std::ostream& os) const;
    // Печать судна
    friend std::ostream& operator<<(std::ostream& os, const Vessel& v);

    void setDestination(const Destination& value);
    void setProps(const ShipProperties& value);
    
    const Destination& getDestination() const;
    const ShipProperties& getProps() const;

    Destination& getDestination();
    ShipProperties& getProps();
};
}