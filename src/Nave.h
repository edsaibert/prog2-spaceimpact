#ifndef SPACESHIP_H 
#define SPACESHIP_H
#include "../main.h"

#define SPACESHIP_STEP 20

struct SPACESHIP { 
	Pos position;	
}

SPACESHIP* createSpaceship(Pos position);
void updateSpaceshipPosition(Pos position);

#endif
