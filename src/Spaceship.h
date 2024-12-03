#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "../main.h"
#include "Joystick.h"
#include "Screen.h"
#include "Sprite.h"
#include "Gun.h"

#define SPACESHIP_STEP 3
#define SPACESHIP_SIDE 50 
#define SPACESHIP_HEALTH 100


typedef struct spaceship SPACESHIP;
struct spaceship {
	int x;
	int y;
	unsigned char side;
	
	int health;
	int shield;

	int enemy;

	JOYSTICK* control;
	GUN* gun;
	SPRITE* sprite;
};

SPACESHIP* createSpaceship(int x, int y, int enemy, int health, const char* spriteFolderPath);

void compareFunctionPlayer(SPACESHIP* sp, SPACESHIP* enemy, SCREEN* sc, void (*positionFunction)(SPACESHIP *, int, unsigned char, SCREEN *));

void compareFunctionUpDownEnemy(SPACESHIP* sp, SPACESHIP* enemy, SCREEN* sc, void (*positionFunction)(SPACESHIP *, int, unsigned char, SCREEN *));

void updateSpaceshipPosition(SPACESHIP* sp, SPACESHIP* enemy, SCREEN* sc, void (*positionFunction) (SPACESHIP*, int, unsigned char, SCREEN*), void (*comparisonFunction) (SPACESHIP*, SPACESHIP*, SCREEN*, void (*positionFunction)(SPACESHIP*, int, unsigned char, SCREEN*)));

void moveSpaceship(SPACESHIP* sp, int stepCount, unsigned char trajectory, SCREEN* screen);

void shootSpaceship(SPACESHIP* sp);

void hitSpaceship(SPACESHIP* sp, int damage);

int checkIfSpaceshipIsDead(SPACESHIP* sp);

void drawSpaceship(SPACESHIP* sp);

void destroySpaceship(SPACESHIP* sp);

#endif
