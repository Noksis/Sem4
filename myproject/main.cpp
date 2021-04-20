#include "game.h"
int main() {
	Bord game;
	game.random_ships(game.Enemybord);
	game.print(game.Enemybord);
	coords XY;
	std::cin >> XY.x;
	std::cin >> XY.y;
	game.print(game.Hitbord);
	game.turn(XY);
	game.print(game.Hitbord);
	game.print(game.Enemybord);
	return 0;
}
