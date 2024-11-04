#ifndef SCREEN_H
#define SCREEN_H
#include "../main.h"

typedef struct screen SCREEN;
struct screen {
	int max_x;
	int max_y;
};

SCREEN* createScreen(int max_x, int max_y);
void destroyScreen(SCREEN* sc);

#endif
