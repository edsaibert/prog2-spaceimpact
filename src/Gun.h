#ifndef GUN_H
#define GUN_H

#include "../main.h"

#include "Bullet.h"
#include "Position.h"

#define PISTOL_COOLDOWN 10

typedef struct gun {
	unsigned char timer;
	BULLET *shots;
} GUN;

GUN* createGun();

BULLET* shotGun(int x, int y, unsigned char trajectory, GUN* gun);


void destroyGun(GUN* gun);

#endif
