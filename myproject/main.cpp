#include "game.h"
int main() {
	Bord game;
	coords XY;
	game.random_ships(game.Enemybord);
	game.random_ships(game.Mybord);
	game.print(game.Mybord);
	game.print(game.Enemybord);


	for (int i = 0; i < 15; i++) {
		XY = game.enter_XY();
		game.turn(XY);
		game.enemy_turn();
	}
	return 0;
}
