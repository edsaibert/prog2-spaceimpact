#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "../main.h"

#define SPACESHIP_STEP 20

typedef struct spaceship SPACESHIP;
struct spaceship {
	int x;
	int y;
	unsigned char side;
};

SPACESHIP* createSpaceship(int x, int y);
void updateSpaceshipPos(SPACESHIP* sp, int stepCount, unsigned char trajectory);
void drawSpaceship(SPACESHIP* sp);

#endif
