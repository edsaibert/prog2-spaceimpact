#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "../main.h"
#include "Screen.h"

#define PARALLAX_SPEED 2 

typedef struct background {
	int width;
	int height;
	
	int x;
	int y;

	ALLEGRO_BITMAP* foreground;
	ALLEGRO_BITMAP* background;
	ALLEGRO_BITMAP* middleground;
} BACKGROUND;

BACKGROUND* createBackground(const char* foreground, const char* background, const char* middleground, int width, int height);

void changeBackground(BACKGROUND* prev, const char* foreground, const char* background, const char* middleground);

void updateScreenForBackground(BACKGROUND* bg);

void drawBackground(BACKGROUND* bg, SCREEN* sc);

void destroyBackground(BACKGROUND* bg);

#endif 
