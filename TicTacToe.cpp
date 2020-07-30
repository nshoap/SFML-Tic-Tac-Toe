#include "Game.h"

int main()
{
    Game game(sf::VideoMode(384, 384), "Tic Tac Toe");
    game.run();
    return 0;
}