#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "../main.h"
#include "Joystick.h"
#include "Screen.h"

#define SPACESHIP_STEP 20
#define SPACESHIP_SIDE 10

typedef struct spaceship SPACESHIP;
struct spaceship {
	int x;
	int y;
	unsigned char side;
	JOYSTICK* control;
};

SPACESHIP* createSpaceship(int x, int y);
void moveSpaceship(SPACESHIP* sp, int stepCount, unsigned char trajectory, SCREEN* screen);
void drawSpaceship(SPACESHIP* sp);

#endif
