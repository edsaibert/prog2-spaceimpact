#include "Spaceship.h"

SPACESHIP* createSpaceship(int x, int y){
	SPACESHIP* sp;

	sp = (SPACESHIP*) malloc(sizeof(SPACESHIP));
	if (!sp)
		return NULL;

	sp->x = x;
	sp->y = y;
	sp->side = SPACESHIP_SIDE; // default para 10
	sp->control = createJoystick();

	return sp;
}

void updateSpaceshipPos(SPACESHIP* sp, int stepCount, unsigned char trajectory){
	sp->x += stepCount*SPACESHIP_STEP;
	printf("%d\n", sp->x);
}

void drawSpaceship(SPACESHIP* sp){
	al_draw_filled_rectangle(sp->x-sp->side, sp->y-sp->side, sp->x+sp->side, sp->y+sp->side, al_map_rgb(255,0,0));
}
