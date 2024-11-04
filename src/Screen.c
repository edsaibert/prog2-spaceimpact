#include "Screen.h"

SCREEN* createScreen(int max_x, int max_y){
	SCREEN* sc = (SCREEN*) malloc(sizeof(SCREEN));

	if (!sc) return NULL;

	sc->max_x = max_x;
	sc->max_y = max_y;

	return sc;
}

void destroyScreen(SCREEN* sc){
	free(sc);
}


