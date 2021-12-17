#pragma once
#include "vessel.h"
#include <vector>

namespace SolvingProblems{
class PassengerVessel : public Vessel {
public:
    // максимальная вместимость пассажиров
    int maxpax;
    // сколько сейчас пассажиров
    int curpax;
    // типы кают
    enum class CabinType {LUX, FIRSTCLASS, SECONDCLASS};
    // сколько кают на данном корабле
    int cabin_num;
    // список кают с типом
    CabinType* cabincontent;
    // конструктор
    PassengerVessel(int id, const Destination& dest, int ETA, const ShipProperties& 
        props, int maxpax, int curpax, const std::vector<CabinType> cabContent);
    PassengerVessel(const PassengerVessel& other);
    virtual ~PassengerVessel() override;
    void printInOs(std::ostream& os) const override;
    
    PassengerVessel& operator=(const PassengerVessel& other);
    PassengerVessel* clone() const override;

private:
    // Печать пассажирского судна
    friend std::ostream& operator<<(std::ostream& os, const PassengerVessel& v);
};
}