#pragma once
#include <iostream>
#include "Names.h"
#include <vector>
#include <cstdlib>

// Stuct for SHIPS data
struct  ship {
	int x = 0;
	int y = 0;
	bool orient = VERTICAL;
	int type = DECK1;
};

// Struct for coords on board
struct coords {
	int x = 0;
	int y = 0;
};

// Game and bord
class Bord {
private:
	int hit(coords XY);
	int dead_zone(coords XY, int** bord);
	int add_hit (coords XY, int** bord);
	coords enter_XY();
	int check_inj(coords* XY);
	std::vector<coords> free_cells(int* size,int** bord);
	int create_ship(int** bord, int type);
	int Poison_Bord(int** bord);

public:
	int** Mybord;
	int** Enemybord;
	int** Hitbord;

	char print(int** bord);
	Bord();
	char turn(coords XY);
	char add_ship(ship SH, int** bord);
	char random_ships(int** bord);

};

// Constuct bord
Bord::Bord() {

	this->Mybord = new int* [LSIZE];
	for (int i = 0; i < LSIZE; i++) {
		this->Mybord[i] = new int[LSIZE];
	}
	for (int i = 0; i < LSIZE; i++) {
		for (int j = 0; j < LSIZE; j++) {
			this->Mybord[i][j] = 0;
		}
	}
	Bord::Poison_Bord(this->Mybord);

	this->Enemybord = new int* [LSIZE];
	for (int i = 0; i < LSIZE; i++) {
		this->Enemybord[i] = new int[LSIZE];
	}
	for (int i = 0; i < LSIZE; i++) {
		for (int j = 0; j < LSIZE; j++) {
			this->Enemybord[i][j] = 0;
		}
	}
	Bord::Poison_Bord(this->Enemybord);

	this->Hitbord = new int* [LSIZE];
	for (int i = 0; i < LSIZE; i++) {
		this->Hitbord[i] = new int[LSIZE];
	}
	for (int i = 0; i < LSIZE; i++) {
		for (int j = 0; j < LSIZE; j++) {
			this->Hitbord[i][j] = 0;
		}
	}
	Bord::Poison_Bord(this->Hitbord);

}

// Add ship on board
char Bord::add_ship(ship SH,int** bord) {
	
	// Add verical ship
	if (SH.orient == HORIZONT) {

		//check size
		if (SH.y + SH.type > SIZE) 
			return ERR_PLACE;

		for (int i = 0; i < SH.type; i++)
			bord[SH.x][SH.y + i] = SHIP;
	}

	if (SH.orient == VERTICAL) {
		//check size
		if (SH.x + SH.type > SIZE)
			return ERR_PLACE;

		for (int i = 0; i < SH.type; i++)
			bord[SH.x + i][SH.y] = SHIP;
	}
	
	return SUCCESS;
}

// Turn of player
char Bord::turn(coords XY) {
	this->Hitbord[XY.x][XY.y] = HIT_MISS;


	if (Bord::hit(XY) == HIT) {
		this->Hitbord[XY.x][XY.y] = HIT_SHIP;
		// Add new coords for HIT
		XY = enter_XY();
		// New turn with new coords
		Bord::turn(XY);
	}

	else if (Bord::hit(XY)  == MISS) {
		this->Hitbord[XY.x][XY.y] = HIT_MISS;
		return SUCCESS;
	}

	else if (Bord::hit(XY) == KILL) {
		this->Hitbord[XY.x][XY.y] = HIT_SHIP;
		// Add deadzone to board near ship
		dead_zone(XY, this->Hitbord);
		// Add new coords and go on your turn
		XY = enter_XY();
		Bord::turn(XY);
	}
}

// Check hit on board
int Bord::hit(coords XY) {

	if (this->Enemybord[XY.x][XY.y] == SHIP) {
		return check_inj(&XY);
	}
	else
		return MISS;
}

// Input coords XY
coords Bord::enter_XY () {
	coords Node;
	std::cin >> Node.x;
std::cin >> Node.y;
return Node;
}

// Add dead zone near dead ship
int Bord::dead_zone(coords XY, int** bord) {
	int orient = 0;
	int i = 1;
	coords XY_ = XY;
	add_hit(XY,bord);
	if (bord[XY.x + 1][XY.y] == SHIP || bord[XY.x - 1][XY.y] == SHIP)
		orient = VERTICAL;
	else
		orient = HORIZONT;


	if (orient == VERTICAL) {
		while (bord[XY.x + i][XY.y] == SHIP) {
			XY_.x = XY.x + i;
			add_hit(XY_,bord);
			i++;
		}
		i = 1;
		while (bord[XY.x - i][XY.y] == SHIP) {
			XY_.x = XY.x - i;
			add_hit(XY_,bord);
			i--;
		}
	}
	i = 1;
	if (orient == HORIZONT) {
		while (bord[XY.x][XY.y + i] == SHIP) {
			XY_.y = XY.y + i;
			add_hit(XY_,bord);
			i++;
		}
		i = 1;
		while (bord[XY.x][XY.y - i] == SHIP) {
			XY_.y = XY.y - i;
			add_hit(XY_,bord);
			i--;
		}

	}

	return SUCCESS;
}

// Find injured cell and return HIT or KILL
int Bord::check_inj(coords* XY) {
	int orient = 0;
	int i = 1;

	if (this->Enemybord[XY->x + 1][XY->y] == SHIP || this->Enemybord[XY->x - 1][XY->y] == SHIP)
		orient = VERTICAL;
	else
		orient = HORIZONT;

	if (orient == VERTICAL) {
		while (this->Enemybord[XY->x + i][XY->y] == SHIP) {
			if (this->Enemybord[XY->x + i][XY->y] && this->Hitbord[XY->x + i][XY->y] == 0)
				return HIT;
			i++;
		}
		while (this->Enemybord[XY->x - i][XY->y] == SHIP) {
			if (this->Enemybord[XY->x - i][XY->y] && this->Hitbord[XY->x - i][XY->y] == 0)
				return HIT;
			i--;
		}
	}

	if (orient == HORIZONT) {
		while (this->Enemybord[XY->x][XY->y + i] == SHIP) {
			if (this->Enemybord[XY->x][XY->y + i] && this->Hitbord[XY->x][XY->y + i] == 0)
				return HIT;
			i++;
		}
		while (this->Enemybord[XY->x][XY->y - i] == SHIP) {
			if (this->Enemybord[XY->x][XY->y - i] && this->Hitbord[XY->x][XY->y - i] == 0)
				return HIT;
			i--;
		}
	}

	return KILL;
}

// Add hit around cell 
int Bord::add_hit(coords XY, int** bord) {
	if (bord[XY.x+1][XY.y] != SHIP )
		bord[XY.x + 1][XY.y] = DEAD_ZONE;
	if (bord[XY.x - 1][XY.y] != SHIP )
		bord[XY.x - 1][XY.y] = DEAD_ZONE;
	if (bord[XY.x][XY.y - 1] != SHIP)
		bord[XY.x][XY.y - 1] = DEAD_ZONE;
	if (bord[XY.x][XY.y + 1] != SHIP)
		bord[XY.x][XY.y + 1] = DEAD_ZONE;
	if (bord[XY.x + 1][XY.y + 1] != SHIP)
		bord[XY.x + 1][XY.y + 1] = DEAD_ZONE;
	if (bord[XY.x - 1][XY.y + 1] != SHIP)
		bord[XY.x - 1][XY.y + 1] = DEAD_ZONE;
	if (bord[XY.x + 1][XY.y - 1] != SHIP)
		bord[XY.x + 1][XY.y - 1] = DEAD_ZONE;
	if (bord[XY.x - 1][XY.y - 1] != SHIP)
		bord[XY.x - 1][XY.y - 1] = DEAD_ZONE;
	return SUCCESS;
}

// Randoms ships on bord
char Bord::random_ships(int** bord) {
	
	create_ship(bord, DECK1);
	create_ship(bord, DECK2);
	create_ship(bord, DECK3);
	create_ship(bord, DECK4);

	return SUCCESS;
}

// Find all free cells in Mybord
std::vector<coords> Bord::free_cells(int* size, int** bord) {
	std::vector<coords> cells;
	int k = 0;
	coords XY;
	int j = 0;
	for (int x = 0; x < SIZE; x++) {
		for (int y = 0; y < SIZE; y++) {
			char elm = *(*(bord + x) + y);
			if (*(*(bord + x) + y) == 0) {
				XY.x = x;
				XY.y = y;
				cells.push_back(XY);
				k++;
			}
		}
	}

	*size = k;
	return  cells;
}

// Print bord in SHELL
char Bord::print(int** bord) {
	for (int i = 0; i < LSIZE; i++) {
		for (int j = 0; j < LSIZE; j++) {
			std::cout << bord[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << '\n';
	return SUCCESS;
}

// Create one type random ships
int Bord::create_ship(int** bord, int type) {
	
	int size = 0;
	coords random_node;
	ship SH;

	for (int i = 0; i < 5 - type; i++) {
		SH.type = type;
		std::vector<coords> free = this->free_cells(&size,bord);
		random_node = free[rand() % size];

		SH.x = random_node.x;
		SH.y = random_node.y;

		if (random_node.x + type < SIZE && rand() % 2 == 1) {
			SH.orient = VERTICAL;
			if (bord[SH.x + type - 1][SH.y] == 0) {
				add_ship(SH, bord);
				dead_zone(random_node, bord);
			}
			else
				i--;
		}
		else if (random_node.y + type < SIZE && rand() % 2 == 1) {
			SH.orient = HORIZONT;
			if (bord[SH.x][SH.y + type - 1] == 0) {
				add_ship(SH,bord);
				dead_zone(random_node, bord);
			}
			else
				i--;
		}
		else
			i--;
	}
	return SUCCESS;
}

// Create poison for Bord
int Bord::Poison_Bord(int** bord) {
	for (int i = 0; i < LSIZE; i++) {
		bord[0][i] = POISON;
	}

	for (int i = 0; i < LSIZE; i++) {
		bord[SIZE][i] = POISON;
	}

	for (int i = 0; i < LSIZE; i++) {
		bord[i][0] = POISON;
	}

	for (int i = 0; i < LSIZE; i++) {
		bord[i][SIZE] = POISON;
	}

	return SUCCESS;
}
