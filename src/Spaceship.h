#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "../main.h"
#include "Joystick.h"
#include "Screen.h"
#include "Sprite.h"
#include "Gun.h"

#define SPACESHIP_STEP 10 
#define SPACESHIP_SIDE 50 

typedef struct spaceship SPACESHIP;
struct spaceship {
	int x;
	int y;
	int enemy;
	unsigned char side;
	JOYSTICK* control;
	GUN* gun;
	SPRITE* sprite;
};

SPACESHIP* createSpaceship(int x, int y, int enemy, const char* spriteFolderPath);
void moveSpaceship(SPACESHIP* sp, int stepCount, unsigned char trajectory, SCREEN* screen);
void drawSpaceship(SPACESHIP* sp);
void destroySpaceship(SPACESHIP* sp);

#endif
