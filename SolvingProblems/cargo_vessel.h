#include "vessel.h"
#include <vector>

namespace SolvingProblems{
class CargoVessel : public Vessel {
public:
    // Типы  груза
    enum class CargoType {FOOD, WOOD, GOOD};
    // максимальная грузоподъемность
    int maxcargo;
    // сколько сейчас загружено
    int curcargo;
    // массив контейнеров
    int container_num;
    CargoType* containercontent;
    // Конструктор
    CargoVessel(int id, const Destination& dest, int eta, const ShipProperties& props,
        int maxcargo, int curcargo, const std::vector<CargoType> contContent);
    CargoVessel(const CargoVessel& other);
    virtual ~CargoVessel() override;
    
    CargoVessel& operator=(const CargoVessel& other);
    CargoVessel* clone() const override;
    void printInOs(std::ostream& os) const override;

    // Печать грузового судна
    friend std::ostream& operator<<(std::ostream& os, const CargoVessel& v);

};
}