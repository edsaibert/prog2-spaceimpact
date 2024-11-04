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

// Movimenta a nave (SPACESHIP* sp) até o limite da tela (SCREEN* sc)
void moveSpaceship(SPACESHIP* sp, int stepCount, unsigned char trajectory, SCREEN* sc){
	if (!trajectory){
		if (sp->x - stepCount*SPACESHIP_STEP - sp->side/2 >= 0)
			// Movimentação para a esquerda
			sp->x = sp->x - stepCount*SPACESHIP_STEP;
		else sp->x = sp->side/2;
	}
	else if (trajectory == 1) {
		if (sp->x + stepCount*SPACESHIP_STEP + sp->side/2 <= sc->max_x)
			// Movimentação para a direita
			sp->x = sp->x + stepCount*SPACESHIP_STEP;
		else sp->x = sc->max_x - sp->side/2;
	}
	else if (trajectory == 2) {
		if (sp->y - stepCount*SPACESHIP_STEP - sp->side/2 >= 0)
			// Movimentação para cima
			sp->y = sp->y - stepCount*SPACESHIP_STEP;
		else sp->y = sp->side/2;
	}
	else if (trajectory == 3) {
		if (sp->y + stepCount*SPACESHIP_STEP + sp->side/2 <= sc->max_y)
			// Movimentação para baixo
			sp->y = sp->y + stepCount*SPACESHIP_STEP;
		else sp->y = sc->max_y - sp->side/2;
	}
}

void drawSpaceship(SPACESHIP* sp){
	al_draw_filled_rectangle(sp->x-sp->side/2, sp->y-sp->side/2, sp->x+sp->side/2, sp->y+sp->side/2, al_map_rgb(255,0,0));
}
