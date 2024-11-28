#ifndef POSITION_H
#define POSITION_H

#include "../main.h"
//#include "Joystick.h"
//#include "Spaceship.h"
//#include "Screen.h"

float* normalizedDistance(int x1, int y1, int x2, int y2);

short int checkCollision(int x1, int y1, int x2, int y2, int side1, int side2);


#endif
