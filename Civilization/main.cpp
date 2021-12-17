//#include <SFML/Graphics.hpp> //-lsfml-window -lsfml-graphics -lsfml-system
#include "game.h"
#include <iostream>
#include <string>

#include <ncurses.h> //подключаем библиотеку ncurses

//66 - DOWN
//65 - UP
//67 - RIGHT
//68 - LEFT
//9 - TAB

int main()
{
    Civilization::start();

    return 0;
}