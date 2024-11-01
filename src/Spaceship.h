#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "../main.h"
#include "Joystick.h"

#define SPACESHIP_STEP 20
#define SPACESHIP_SIDE 10

typedef struct spaceship SPACESHIP;
struct spaceship {
	int x;
	int y;
	unsigned char side;
	JOYSTICK* jt;
};

SPACESHIP* createSpaceship(int x, int y);
void updateSpaceshipPos(SPACESHIP* sp, int stepCount, unsigned char trajectory);
void drawSpaceship(SPACESHIP* sp);

#endif
