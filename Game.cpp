#include "Game.h"

void Game::render()
{
	window.clear();
	window.draw(board_sprite);

	window.draw(game_board);
	// TODO: Add drawing of text on board

	window.display();
}

bool Game::check_victory()
{
	return false;
}

bool Game::check_available(const sf::Vector2i& pos)
{
	return false;
}

void Game::make_move(const sf::Vector2i& pos)
{
	sf::Vector2i board_index(pos.x / TILESIZE, pos.y / TILESIZE);
	
	if (check_available(board_index))
	{
		board[board_index.y][board_index.x] = 'X';
	}

}

void Game::over()
{
	render();
	if (game_board.get_victor() == 'X')
	{
		final_texture.loadFromFile("Art\\Win.png");
	}
	else
	{
		final_texture.loadFromFile("Art\\Lost.png");
	}
	sf::Sprite final_message(final_texture);
	window.draw(final_message);
	window.display();
	playing = false;
}

void Game::run()
{

	window.setIcon(sfml_icon.width, sfml_icon.height, sfml_icon.pixel_data);

	// Load board texture and set the sprite to use that texture
	if (!board_texture.loadFromFile(bt_location))
	{
		return;
	}
	board_sprite.setTexture(board_texture);

	AIPlayer ai(game_board);

	sf::Event event;
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				return;
			}
		}
		while (playing)
		{
		
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				if (player_turn)
				{
					sf::Vector2i position = sf::Mouse::getPosition(window);
					if ((position.x > 0 && position.x < window.getSize().x) && (position.y > 0 && position.y < window.getSize().y))
					{
						sf::Vector2i board_index(position.x / TILESIZE, position.y / TILESIZE);
						//std::cout << board_index.x << ',' << board_index.y << std::endl;
						if (game_board.move_available(board_index))
						{
							game_board.update_board(board_index, 'X');
							player_turn = false;
							ai.can_move = true;
						}

					}
				}
			}

			render();

			if (game_board.victory())
			{
				over();
				break;
			}

			if (!player_turn)
			{
				player_turn = ai.move();
			}

			render();

			if (game_board.victory())
			{
				over();
				break;
			}
		}

	}

	return;
}