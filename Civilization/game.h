#pragma once
#include "helpful_objs.h"
#include <vector>
#include <ncurses.h> 

namespace Civilization{

struct Game
{
private:
    uint n, m, playersNum;
    Field field;
    std::vector<Player> players;
    std::vector<std::vector<WINDOW *>> windows;
    Pos curPos = Pos(0, 0);
    Pos activatePos = Pos(0, 0);
    std::set<Pos> activePoss{};
    bool isActive = false;
    uint curPlayerId = 1;

    void printPos(const Pos& p) const; // const 
    void printCurPlayer(WINDOW *place) const;
    bool activate();
    bool activeActivate();
    bool passiveActivate();
    void printActiveWithDelete();
    void removeFromPlayer(const std::shared_ptr<FieldObject>& object); //const&
    uint countAlivePlayers() const;

public:
    //Game(uint n, uint m, uint playersNum, double power = 100);
    Game(const std::string& mapName, double power = 100);
    void mainLoop();
};

void start();

}

