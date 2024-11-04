#ifndef POSITION_H
#define POSITION_H

#include "../main.h"
#include "Joystick.h"
#include "Spaceship.h"
#include "Screen.h"

float* normalizedDistance(int x1, int y1, int x2, int y2);

short int checkCollision(int euclidianDistance, int side1, int side2);

void updateSpaceshipPosition(SPACESHIP* sp, SPACESHIP* enemy, SCREEN* sc, void (*positionFunction) (SPACESHIP*, int, unsigned char, SCREEN*));

#endif
