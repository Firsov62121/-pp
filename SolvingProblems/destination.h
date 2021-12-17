#pragma once
#include <string>
#include <iostream>

namespace SolvingProblems{
// Место назначения
class Destination {
public:
    // название порта назначения
    std::string description;
    // координаты места назначения
    int x,y;

    Destination (int x = 0, int y = 0, std::string description = "");
    Destination(const Destination& other);
    
    Destination& operator=(const Destination& other);
    bool operator==(const Destination& other) const;
    
    friend std::ostream& operator<<(std::ostream& os, const Destination& v);
};
}