#pragma once
#include <iostream>
#include "Names.h"

struct  ship {
	int x = 0;
	int y = 0;
	bool orient = VERTICAL;
	int type = DECK1;
};

struct coords {
	int x = 0;
	int y = 0;
};

class Bord {
private:
	char Mybord[SIZE][SIZE];
	char Enemybord[SIZE][SIZE];
	char Hitbord[SIZE][SIZE];
	int hit(coords XY);
	int dead_zone(coords XY);
	int info_ship(coords* XY);
public:
	Bord();
	char turn(coords XY);
	char add_ship(ship SH);

};

Bord::Bord() {

}

// Add ship on board
char Bord::add_ship(ship SH) {
	
	// Add verical ship
	if (SH.orient == VERTICAL) {

		//check size
		if (SH.y + SH.type > SIZE) 
			return ERR_PLACE;

		for (int i = 0; i < SH.type; i++)
			this->Mybord[SH.x][SH.y + i] = 1;
	}

	if (SH.orient == HORIZONT) {
		//check size
		if (SH.x + SH.type > SIZE)
			return ERR_PLACE;

		for (int i = 0; i < SH.type; i++)
			this->Mybord[SH.x + i][SH.y] = 1;
	}
	
	return SUCCESS;
}

// Turn of player
char Bord::turn(coords XY) {
	if (Bord::hit(XY) == HIT) {
		this->Hitbord[XY.x][XY.y] = 1;
		XY = enter_XY();
		Bord::turn(XY);
	}

	else if (Bord::hit(XY) == MISS) {
		this->Hitbord[XY.x][XY.y] = 1;
	}

	else if (Bord::hit(XY) == KILL) {
		this->Hitbord[XY.x][XY.y] = 1;
		dead_zone(XY);
		XY = enter_XY();
		Bord::turn(XY);
	}
}


// Check hit on board
int Bord::hit(coords XY) {
	coords* info;

	if (this->Enemybord[XY.x][XY.y] == 1) {
		for (int i = 0; i++; i < info_ship(info)) {
			if (this->Hitbord[info[i].x][info[i].y] != 1)
				return HIT;
		}

		return KILL;
	}
	else
		return MISS;
}

// Input coords XY
coords enter_XY () {
}

// Add dead zone near dead ship
int Bord::dead_zone(coords XY) {

}

// Return len(ship) and add coords in massive XY*
int Bord::info_ship(coords* XY) {

}

