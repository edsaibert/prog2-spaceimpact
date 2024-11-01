#include "Spaceship.h"

SPACESHIP* createSpaceship(int x, int y){
	SPACESHIP* sp;

	sp = (SPACESHIP*) malloc(sizeof(SPACESHIP));
	if (!sp)
		return NULL;

	sp->x = x;
	sp->y = y;

	return sp;
}

void updateSpaceshipPos(SPACESHIP* sp, int stepCount, unsigned char trajectory){
	sp->x += stepCount*SPACESHIP_STEP;
}

void drawSpaceship(SPACESHIP* sp){
	al_draw_filled_rectangle(sp->x-sp->side, sp->y+sp->side, sp->x+sp->side, sp->y+sp->side, al_color_name("tomato"));
}
