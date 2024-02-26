#include "Game.h"

#include <SFML\Graphics.hpp>

int main()
{
	Game game("configs.txt");
	game.run();
	return 0;
}