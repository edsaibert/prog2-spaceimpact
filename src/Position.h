#ifndef POSITION_H
#define POSITION_H

#include "../main.h"
#include "Joystick.h"
#include "Spaceship.h"
#include "Screen.h"

int* normalizedDistance(int x1, int y2, int x2, int y2);

short int checkCollision(int euclidianDistance, int side1, int side2);

void updateSpaceshipPosition(SPACESHIP* sp, SCREEN* sc, void (*positionFunction) (SPACESHIP*, int, unsigned char, SCREEN*));

#endif
