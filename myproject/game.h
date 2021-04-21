#pragma once
#pragma warning(disable: 4996)
#include <iostream>
#include "Names.h"
#include <stdio.h>
#include <string>
#include <vector>

int CharToInt(char a) {
	int b = (int)(a);
	return b;
}

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
	int hit(coords XY, int** bord, int** bord2);
	int dead_zone(coords XY, int** bord, int check);
	int add_hit (coords XY, int** bord, int check);
	int check_inj(coords* XY, int** bord1, int** bord2);
	std::vector<coords> free_cells(int* size,int** bord);
	int create_ship(int** bord, int type);
	int Poison_Bord(int** bord);
	int clean_dead_zone(int** bord);

public:
	int** Mybord;
	int** Enemybord;
	int** Visualbord;
	int** Hitbord;
	int** HitEnemybord;

	char print(int** bord);
	Bord();
	char turn(coords XY);
	char enemy_turn();
	coords enter_XY();
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

	this->HitEnemybord = new int* [LSIZE];
	for (int i = 0; i < LSIZE; i++) {
		this->HitEnemybord[i] = new int[LSIZE];
	}
	for (int i = 0; i < LSIZE; i++) {
		for (int j = 0; j < LSIZE; j++) {
			this->HitEnemybord[i][j] = 0;
		}
	}
	Bord::Poison_Bord(this->HitEnemybord);

	this->Visualbord = new int* [LSIZE];
	for (int i = 0; i < LSIZE; i++) {
		this->Visualbord[i] = new int[LSIZE];
	}
	for (int i = 0; i < LSIZE; i++) {
		for (int j = 0; j < LSIZE; j++) {
			this->Visualbord[i][j] = 0;
		}
	}
	Bord::Poison_Bord(this->Visualbord);

}

//Copy only ships on bord
int Bord::clean_dead_zone(int** bord) {

	for (int i = 0; i < LSIZE; i++)
		for (int j = 0; j < LSIZE; j++)
			if (bord[i][j] != SHIP)
				bord[i][j] = 0;

	Bord::Poison_Bord(bord);
	return SUCCESS;
}

// Turn of computer
char Bord::enemy_turn() {
	int size = 0;
	std::vector<coords> free = free_cells(&size, this->HitEnemybord);
	coords XY = free[rand() % size];

	this->HitEnemybord[XY.x][XY.y] = HIT_MISS;


	if (Bord::hit(XY, this->Mybord, this->HitEnemybord) == HIT) {
		this->HitEnemybord[XY.x][XY.y] = HIT_SHIP;
		this->Mybord[XY.x][XY.y] = HIT_MYSHIP;
		print(this->Mybord);
		Bord::enemy_turn();
	}

	else if (Bord::hit(XY, this->Mybord, this->HitEnemybord) == MISS) {
		this->HitEnemybord[XY.x][XY.y] = HIT_MISS;
		this->Mybord[XY.x][XY.y] = HIT_MISS;
		print(this->Mybord);
		return SUCCESS;
	}

	else if (Bord::hit(XY, this->Mybord, this->HitEnemybord) == KILL) {
		this->HitEnemybord[XY.x][XY.y] = HIT_SHIP;
		this->Mybord[XY.x][XY.y] = HIT_MYSHIP;
		// Add deadzone to board near ship
		dead_zone(XY, this->HitEnemybord, SHIP);
		dead_zone(XY, this->Mybord, HIT_MYSHIP);
		// Add new coords and go on your turn
		print(this->Mybord);
		Bord::enemy_turn();
	}

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


	if (Bord::hit(XY,this->Enemybord, this->Hitbord) == HIT) {
		this->Hitbord[XY.x][XY.y] = HIT_SHIP;
		// Add new coords for HIT
		print(this->Hitbord);
		XY = enter_XY();
		// New turn with new coords
		Bord::turn(XY);
	}

	else if (Bord::hit(XY,this->Enemybord, this->Hitbord)  == MISS) {
		this->Hitbord[XY.x][XY.y] = HIT_MISS;
		print(this->Hitbord);
		return SUCCESS;
	}

	else if (Bord::hit(XY,this->Enemybord, this->Hitbord) == KILL) {
		this->Hitbord[XY.x][XY.y] = HIT_SHIP;
		// Add deadzone to board near ship
		dead_zone(XY, this->Hitbord, SHIP);
		// Add new coords and go on your turn
		print(this->Hitbord);
		XY = enter_XY();
		Bord::turn(XY);
	}
}

// Check hit on board
int Bord::hit(coords XY, int** bord, int** bord2) {

	if (bord[XY.x][XY.y] == SHIP) {
		return check_inj(&XY, bord, bord2);
	}
	else
		return MISS;
}

// Input coords XY
coords Bord::enter_XY () {
	coords Node;
	char x = 0;
	int y = 0;
	// Cycle for input success coords
	while (true) {
		Node.x = 0;
		Node.y = 0;

		std::cout << "Please, input coords (Like a A1,B2,E9 and etc) :" << std::endl;
		scanf("%c", &x);
		scanf("%d", &y);
		scanf("%*c");

		switch (x) {
		case ('A'):
			Node.y = 1;
			break;
		case ('B'):
			Node.y = 2;
			break;
		case ('C'):
			Node.y = 3;
			break;
		case ('D'):
			Node.y = 4;
			break;
		case ('E'):
			Node.y = 4;
			break;
		case ('F'):
			Node.y = 5;
			break;
		case ('G'):
			Node.y = 6;
		case ('H'):
			Node.y = 7;
		case ('I'):
			Node.y = 8;
		case ('J'):
			Node.y = 9;
			break;
		case ('K'):
			Node.y = 10;
			break;
		}
		if (y > 0 && y <= 10) 
			Node.x = y;

		if (Node.x != 0 && Node.y != 0) {
			std::cout << "Accept your coords!" << std::endl;
			break;
		}
		else
			std::cout << "Your coords is WRONG!!!! Please repeat!" << std::endl;

	}
	return Node;
}

// Add dead zone near dead ship
int Bord::dead_zone(coords XY, int** bord, int check) {
	int orient = 0;
	int i = 1;
	coords XY_ = XY;
	add_hit(XY,bord, check);
	if (bord[XY.x + 1][XY.y] == check || bord[XY.x - 1][XY.y] == check)
		orient = VERTICAL;
	else
		orient = HORIZONT;


	if (orient == VERTICAL) {
		while (bord[XY.x + i][XY.y] == check) {
			XY_.x = XY.x + i;
			add_hit(XY_,bord, check);
			i++;
		}
		i = 1;
		while (bord[XY.x - i][XY.y] == check) {
			XY_.x = XY.x - i;
			add_hit(XY_,bord, check);
			i--;
		}
	}
	i = 1;
	if (orient == HORIZONT) {
		while (bord[XY.x][XY.y + i] == check) {
			XY_.y = XY.y + i;
			add_hit(XY_,bord, check);
			i++;
		}
		i = 1;
		while (bord[XY.x][XY.y - i] == check) {
			XY_.y = XY.y - i;
			add_hit(XY_,bord, check);
			i--;
		}

	}

	return SUCCESS;
}

// Find injured cell and return HIT or KILL
int Bord::check_inj(coords* XY, int** bord1, int** bord2) {
	int orient = 0;
	int i = 1;

	if (bord1[XY->x + 1][XY->y] == SHIP || bord2[XY->x - 1][XY->y] == SHIP)
		orient = VERTICAL;
	else
		orient = HORIZONT;

	if (orient == VERTICAL) {
		while (bord1[XY->x + i][XY->y] == SHIP) {
			if (bord1[XY->x + i][XY->y] && bord2[XY->x + i][XY->y] == 0)
				return HIT;
			i++;
		}
		while (bord1[XY->x - i][XY->y] == SHIP) {
			if (bord1[XY->x - i][XY->y] && bord2[XY->x - i][XY->y] == 0)
				return HIT;
			i--;
		}
	}

	if (orient == HORIZONT) {
		while (bord1[XY->x][XY->y + i] == SHIP) {
			if (bord1[XY->x][XY->y + i] && bord2[XY->x][XY->y + i] == 0)
				return HIT;
			i++;
		}
		while (bord1[XY->x][XY->y - i] == SHIP) {
			if (bord1[XY->x][XY->y - i] && bord2[XY->x][XY->y - i] == 0)
				return HIT;
			i--;
		}
	}

	return KILL;
}

// Add hit around cell 
int Bord::add_hit(coords XY, int** bord, int check) {
	if (bord[XY.x+1][XY.y] != check)
		bord[XY.x + 1][XY.y] = DEAD_ZONE;
	if (bord[XY.x - 1][XY.y] != check)
		bord[XY.x - 1][XY.y] = DEAD_ZONE;
	if (bord[XY.x][XY.y - 1] != check)
		bord[XY.x][XY.y - 1] = DEAD_ZONE;
	if (bord[XY.x][XY.y + 1] != check)
		bord[XY.x][XY.y + 1] = DEAD_ZONE;
	if (bord[XY.x + 1][XY.y + 1] != check)
		bord[XY.x + 1][XY.y + 1] = DEAD_ZONE;
	if (bord[XY.x - 1][XY.y + 1] != check)
		bord[XY.x - 1][XY.y + 1] = DEAD_ZONE;
	if (bord[XY.x + 1][XY.y - 1] != check)
		bord[XY.x + 1][XY.y - 1] = DEAD_ZONE;
	if (bord[XY.x - 1][XY.y - 1] != check)
		bord[XY.x - 1][XY.y - 1] = DEAD_ZONE;
	return SUCCESS;
}

// Randoms ships on bord
char Bord::random_ships(int** bord) {
	
	create_ship(bord, DECK1);
	create_ship(bord, DECK2);
	create_ship(bord, DECK3);
	create_ship(bord, DECK4);
	clean_dead_zone(bord);
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
	std::cout << '\n';
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
				dead_zone(random_node, bord, SHIP);
			}
			else
				i--;
		}
		else if (random_node.y + type < SIZE && rand() % 2 == 1) {
			SH.orient = HORIZONT;
			if (bord[SH.x][SH.y + type - 1] == 0) {
				add_ship(SH,bord);
				dead_zone(random_node, bord, SHIP);
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

