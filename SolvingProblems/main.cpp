// Vessels v1, Георгий Чернышев, 16.11.2013
#include "audit.h"

// Необходимо реализовать функциональность, где надо исправить ошибки и недописанные куски.
// Интерфейс можно менять в целях исправления, при этом надо быть готовым обосновать.
// Интерфейс можно расширять в целях улучшения, тоже необходимо обосновать. Расставить const-ы.
// Типы данных менять нельзя, то есть если храним где-то указатель, нельзя начать хранить по значению.
// Кроме того, в конце будет необходимо модуляризовать код и написать вызовы демонстрирующие работу.

// Обратите внимание, сейчас код компилируется!

// класс аудитор компании, делает различные проверки
//namespace
namespace SolvingProblems{
void test1()
{
    NavalFreightCompany nfc(Destination(0, 0, "Center"));
    std::vector<PassengerVessel::CabinType> t{PassengerVessel::CabinType::LUX};
    std::vector<CargoVessel::CargoType> t2({CargoVessel::CargoType::FOOD});
    nfc.add(new PassengerVessel(0, Destination(1, 2, "Moscow"), 0, ShipProperties("", "01.03.2009"), 100, 90, t));
    std::cout << nfc;
    if(Audit::isPassengerVesselsInPort(nfc))
    {
        std::cout << "wrong1" << std::endl;
        return;
    }
    nfc.changeDestination(0, Destination(0, 0, "Center"));
    if(!Audit::isPassengerVesselsInPort(nfc))
    {
        std::cout << "wrong2" << std::endl;
        return;
    }
    nfc.draft();
    if(Audit::isPassengerVesselsInPort(nfc))
    {
        std::cout << "wrong3" << std::endl;
        return;
    }
    nfc.add(new CargoVessel(1, Destination(0, 0, "Center"), 10, ShipProperties("10.03.2020", "11.03.2020"), 120, 130, t2));
    t2.push_back(CargoVessel::CargoType::GOOD);
    nfc.add(new CargoVessel(2, Destination(1, 3, "Syktyvkar"), 15, ShipProperties("15.03.2020", ""), 120, 140, t2));
    //std::cout << nfc;

    NavalFreightCompany nfc2(Destination(1, 3, "Syktyvkar"));
    nfc2.add(new CargoVessel(1, Destination(0, 0, "Center"), 10, ShipProperties("10.03.2020", ""), 1250, 130, t2));
    t2.push_back(CargoVessel::CargoType::GOOD);
    nfc2.add(new CargoVessel(2, Destination(1, 3, "Syktyvkar"), 15, ShipProperties("15.03.2020", ""), 145, 140, t2));
    if(Audit::inspectCargoVessel(CargoVessel(1, Destination(0, 0, "Center"), 10, 
        ShipProperties("10.03.2020", "11.03.2020"), 1250, 1330, t2)))//есть перегрузка
    {
        std::cout << "wrong4" << std::endl;
        return;
    }
    if(!Audit::inspectPassengerVessel(PassengerVessel(0, Destination(1, 2, "Moscow"), 0, 
        ShipProperties("", "01.03.2009"), 100, 90, t)))//нет перегрузки
    {
        std::cout << "wrong5" << std::endl;
        return;
    }
    if(!Audit::secondIsBetter(nfc, nfc2))
    {
        std::cout << "wrong6" << std::endl;
        return;
    }
    if(!Audit::secondIsMoreReiable(nfc, nfc2))
    {
        std::cout << "wrong7" << std::endl;
        return;
    }

    nfc.remove(1);
    std::cout << nfc; //no vessel with id = 1;

    nfc.add(new PassengerVessel(3, Destination(1, 2, "Moscow"), 15, ShipProperties("01.03.2009", ""), 100, 90, t));
    nfc.printStats(std::cout);

    nfc.add(new CargoVessel(4, Destination(1, 2, "Moscow"), 15, ShipProperties("15.03.2020", ""), 120, 140, t2));
    nfc.printHeadingTo(std::cout, "Moscow");

    std::cout << nfc;
    nfc.markDamaged(3, "12.03.2002");
    nfc.markRepaired(4, "30.05.2022");
    std::cout << nfc;

    std::cout << "correct" << std::endl;
}
}

int main(){
    SolvingProblems::test1();
    return 0;
}