#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <iostream>
#include "Board.h"
#include "AIPlayer.h"
#include "Icon.h"

class Game
{
public:
	Game(const sf::VideoMode& res, const std::string& title) : window(res, title) { }
	Game() : Game(sf::VideoMode(512, 512), "UNTITLED") { }
	void run();
	void over();
private:
	sf::RenderWindow window;
	const int TILESIZE = 128;
	const std::string bt_location = "Art\\Board.png";
	sf::Texture board_texture;
	sf::Sprite board_sprite;

	sf::Texture final_texture;

	Board game_board;

	bool playing = true;
	bool player_turn = true;
	char victor = ' ';
	std::vector<std::vector<char>> board = {
		{' ', ' ', ' '},
		{' ', ' ', ' '},
		{' ', ' ', ' '}
	};

	void render();

	bool check_victory();
	bool check_available(const sf::Vector2i& pos);
	void make_move(const sf::Vector2i& pos);

};

#endif