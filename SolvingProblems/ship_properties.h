#pragma once
#include <string>
// Свойства корабля: был ли корабль поврежден и отремонтирован; дата соответствующих событий.
// Если не был поврежден, то пустая строка.
namespace SolvingProblems{
struct ShipProperties {
private:
    // дата повреждения
    std::string* damaged;
    // дата ремонта
    std::string* repaired;
public:
    ShipProperties(const std::string& damaged = "", const std::string& repaired = "");
    ShipProperties(const ShipProperties& other);
    ~ShipProperties();
    ShipProperties& operator=(const ShipProperties& other);
    
    void SetRepaired(const std::string& value);
    void SetDamaged(const std::string& value);
    
    const std::string& GetRepaired() const;
    const std::string& GetDamaged() const;
    
    void AddRepaired(const std::string& time);
    void AddDamaged(const std::string& time);

    friend std::ostream& operator<<(std::ostream& os, const ShipProperties& v);
};
}