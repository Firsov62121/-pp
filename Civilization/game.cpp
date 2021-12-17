#include "game.h"
#include <fstream>
#include <iostream>
#include <utility>
#include <ctime>
#include <filesystem>

namespace Civilization{

static inline Pos getNM(const std::string& mapName)
{
    size_t n, m;
    std::ifstream map(mapName);
    map >> n;
    map >> m;
    map.close();
    return Pos(n, m);
}

Game::Game(const std::string& mapName, double power) : field(getNM(mapName))
{
    std::ifstream map(mapName);
    map >> n;
    map >> m;
    map >> playersNum;
    players.reserve(playersNum);
    for(uint i = 0; i < playersNum; ++i)
    {
        players.emplace_back(i);
    }

    windows.reserve(n);
    for(size_t i = 0; i < n; ++i)
    {
        windows.push_back(std::vector<WINDOW *>());
        windows[i].reserve(m);
        for(size_t j = 0; j < m; ++j)
        {
            windows[i].push_back(newwin(4, 5, i * 4, j * 5));
            int tmp;
            map >> tmp;
            switch(tmp)
            {
            case -1:
                break;
            case 0:
                field.set(Pos(i, j), std::make_shared<FieldObject>(0, FieldType::BadPlace, 0, (Pos(i, j))));
                break;
            default:
                field.set(Pos(i, j), std::make_shared<FieldObject>(tmp, FieldType::CityCell, 
                    get_rand(power / 2, power), Pos(i, j)));
                players[tmp - 1].addObject(field.get(Pos(i, j)));
                break;
            }
            printPos(Pos(i, j));
        }
        std::cout << std::endl;
    }
    map.close();
}

//remove ~Game();

static std::vector<std::string> getMaps()
{
    std::vector<std::string> res;
    std::string path = "maps";
    setlocale(LC_CTYPE,"");
    for (const auto & entry : std::filesystem::directory_iterator(path))
        res.push_back(entry.path());
    return res;
}


void Game::printPos(const Pos& p) const
{
    const std::shared_ptr<const FieldObject> curFieldCell = field.get(p);
    if(activePoss.count(p) != 0)
        wattron(windows[p.x][p.y], COLOR_PAIR(8));
    else
    {
        switch (curFieldCell->getType())
        {
        case FieldType::BadPlace:
            wattron(windows[p.x][p.y], COLOR_PAIR(9));
            break;
        case FieldType::Free:
            wattron(windows[p.x][p.y], COLOR_PAIR(7));
            break;
        default:
            wattron(windows[p.x][p.y], COLOR_PAIR((curFieldCell->getPlayerId() - 1) % 6 + 1));
            break;
        }
    }
    if(p == curPos)
        wattron(windows[p.x][p.y], A_REVERSE);
    else
        wattroff(windows[p.x][p.y], A_REVERSE);
    
    box(windows[p.x][p.y], 0, 0);
    switch (curFieldCell->getType())
    {
    case FieldType::BadPlace:
        box(windows[p.x][p.y], 0, 0);
        for(uint i = 0; i < 4; ++i)
            mvwprintw(windows[p.x][p.y], i, 0, "     ");
        break;
    case FieldType::Free:
        mvwprintw(windows[p.x][p.y], 1, 1, "   ");
        mvwprintw(windows[p.x][p.y], 2, 1, "   ");
        break;
    case FieldType::CityCell:
        mvwprintw(windows[p.x][p.y], 1, 1, "^^^");
        mvwprintw(windows[p.x][p.y], 2, 1, "%3d", curFieldCell->power);
        break;
    case FieldType::Squad:
        mvwprintw(windows[p.x][p.y], 1, 1, "<->");
        mvwprintw(windows[p.x][p.y], 2, 1, "%3d", curFieldCell->power);
        break;
    default:
        break;
    }
    refresh();
    wrefresh(windows[p.x][p.y]);
}

void Game::printActiveWithDelete()
{   
    std::set<Pos> tmp = std::move(activePoss);
    // for(auto const& el : activePoss)
    //     tmp.insert(el);
    //activePoss.clear();
    for(auto const& el : tmp)
        printPos(el);
}

void Game::removeFromPlayer(const std::shared_ptr<FieldObject>& object)
{
    if(object == nullptr || object->getType() == FieldType::BadPlace
        || object->getType() == FieldType::Free)
        return;
    players[object->getPlayerId() - 1].removeObject(object);
}

bool Game::activeActivate()
{
    if(curPos == activatePos)
        return false;
    if(activePoss.count(curPos) == 0)
    {
        isActive = false;
        printActiveWithDelete();
        return false;
    }

    auto const& activeFieldCell = field.get(activatePos);
    auto const& curFieldCell = field.get(curPos);
    if(activeFieldCell->getType() == FieldType::CityCell)
    {
        field.set(curPos, std::make_shared<FieldObject>(activeFieldCell->getPlayerId(), FieldType::Squad, 
            get_rand(activeFieldCell->power / 2, activeFieldCell->power), curPos));
        players[curPlayerId - 1].addObject(field.get(curPos));
    }
    else if(activeFieldCell->getType() == FieldType::Squad)
    {
        activeFieldCell->pos = curPos;
        switch (collapse(*activeFieldCell, *curFieldCell))
        {
        case CollapseRes::FIRST:
            removeFromPlayer(activeFieldCell);
            break;
        case CollapseRes::SECOND:
            removeFromPlayer(curFieldCell);
            field.set(curPos, activeFieldCell);
            break;
        case CollapseRes::BOTH:
            removeFromPlayer(curFieldCell);
            field.set(curPos, std::make_shared<FieldObject>());
            removeFromPlayer(activeFieldCell);
            break;
        case CollapseRes::NONE:
            field.set(activatePos, activeFieldCell);
        default:
            break;
        }
        field.set(activatePos, std::make_shared<FieldObject>());
    }
    printActiveWithDelete();
    printPos(activatePos);
    isActive = false;
    return true;
}

bool Game::passiveActivate()
{
    const auto &curFieldCell = field.get(curPos);
    if(curFieldCell->getType() == FieldType::Free || 
        curFieldCell->getType() == FieldType::BadPlace ||
        curFieldCell->getPlayerId() != curPlayerId)
    {
        printActiveWithDelete();
        return false;
    }

    activatePos = curPos;
    for(int i = -1; i < 2; ++i)
    {
        for(int j = -1; j < 2; ++j)
        {
            uint x = curPos.x + i, y = curPos.y + j;
            if(x < 0 || x >= n || y < 0 || y >= m || curPos == Pos(x, y))
                continue;
            switch(field.get(Pos(x, y))->getType())
            {
            case FieldType::Free:
                activePoss.insert(Pos(x, y));
                break;
            case FieldType::Squad:
                if(curFieldCell->getType() == FieldType::Squad)
                    activePoss.insert(Pos(x, y));
                break;
            case FieldType::CityCell:
                if(curFieldCell->getType() == FieldType::Squad)
                    activePoss.insert(Pos(x, y));
                break;
            default: //BadPlace
                break;
            }
        }   
    }

    for(auto const& el : activePoss)
        printPos(el);
    isActive = activePoss.size() != 0;
    return false;
}

bool Game::activate() //разбей на 2 функции
{
    if(isActive)
    {
        return activeActivate();
    }
    return passiveActivate();
}

uint Game::countAlivePlayers() const
{
    uint res = 0;
    for(uint i = 0; i < playersNum; ++i)
    {
        if(players[i].countOfObjs() != 0)
            ++res;
    }
    return res;
}

void Game::printCurPlayer(WINDOW *place) const
{
    wattron(place, COLOR_PAIR((curPlayerId - 1) % 6 + 1));
    mvwprintw(place, 0, 0, "CurPlayer = %d", curPlayerId);
    refresh();
    wrefresh(place);
}

enum class Key {LEFT = 68, RIGHT = 67, UP = 65, DOWN = 66, ENTER = 10};

void Game::mainLoop()
{
    WINDOW *help = newwin(1, 100, 1, 5 * m + 2);
    printCurPlayer(help);
    int ch = wgetch(help);
    bool isFinished = false;
    while(ch != '1' && !isFinished)
    {
        Pos prevPos = curPos;
        bool needRefresh = false;
        bool activated;
        switch (static_cast<Key>(ch))
        {
        case Key::UP:
            if(curPos.x > 0)
            {
                --curPos.x;
                needRefresh = true;
            }
            break;
        case Key::LEFT:
            if(curPos.y > 0)
            {
                --curPos.y;
                needRefresh = true;
            }
            break;
        case Key::RIGHT:
            if(curPos.y < m - 1)
            {
                ++curPos.y;
                needRefresh = true;
            }
            break;
        case Key::DOWN:
            if(curPos.x < n - 1)
            {
                ++curPos.x;
                needRefresh = true;
            }
            break;
        case Key::ENTER:
            activated = activate();
            if(countAlivePlayers() <= 1)
                isFinished = true;
            else if(activated)
            {
                do
                {
                    ++curPlayerId;
                    if(curPlayerId == playersNum + 1)
                        curPlayerId = 1;
                } while (players[curPlayerId - 1].countOfObjs() == 0); 
            }
            printCurPlayer(help);
            break;
        default:
            break;
        }
        if(isFinished)
            break;
        if(needRefresh)
        {
            printPos(prevPos);
            printPos(curPos);
        }
        ch = wgetch(help);
    }
}

static inline WINDOW * ncursesInit()
{
    std::srand(std::time(nullptr));
    initscr();
    curs_set(0);
    start_color();
    init_pair(9, COLOR_BLUE, COLOR_RED);
    init_pair(8, COLOR_YELLOW, COLOR_BLUE);
    for(uint i = 1; i < 8; ++i)
    {
        init_pair(i, i, COLOR_BLACK);
    }
    noecho();
    cbreak();
    int xMax, yMax;
    getmaxyx(stdscr, yMax, xMax);
    WINDOW *menu = newwin(6, xMax - 12, yMax - 8, 5);
    box(menu, 0, 0);
    refresh();
    wrefresh(menu);

    keypad(menu, true);
    return menu;
}

void start()
{
    WINDOW* menu = ncursesInit();
    
    constexpr std::string_view choices[] = {"Start", "Map:", "Exit"};
    int choice;
    int highlight = 0;
    bool ready = false;
    std::vector<std::string> maps = getMaps();
    size_t map_num = 0;

    while(!ready)
    {
        for(int i = 0; i < 3; ++i)
        {
            if(i == highlight)
                wattron(menu, A_REVERSE);
            mvwprintw(menu, i + 1, 1, choices[i].data());
            if(i == 1)
            {
                mvwprintw(menu, i + 1, 5, "%s", maps[map_num].c_str());
            }
            wattroff(menu, A_REVERSE);
        }
        choice = wgetch(menu);
        switch (choice)
        {
        case KEY_UP:
            highlight -= (highlight == 0 ? 0 : 1);
            break;
        case KEY_DOWN:
            highlight += (highlight == 2 ? 0 : 1);
            break;
        case KEY_LEFT:
            if(highlight == 1)
                map_num -= (map_num == 0 ? 0 : 1);
            break;
        case KEY_RIGHT:
            if(highlight == 1)
                map_num += (map_num == maps.size() - 1 ? 0 : 1);
            break;
        case 10:
            if(highlight != 1)
                ready = true;
            break;
        default:
            break;
        }
    }
    wclear(menu);
    werase(menu);
    refresh();
    wrefresh(menu);

    if(highlight == 0)
    {
        Game g(maps[map_num]);
        g.mainLoop();
    }
    endwin();
}


}