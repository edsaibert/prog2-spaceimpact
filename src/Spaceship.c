#include "Spaceship.h"

SPACESHIP* createSpaceship(int x, int y, int enemy, const char* spriteFolderPath){
	SPACESHIP* sp;

	sp = (SPACESHIP*) malloc(sizeof(SPACESHIP));
	if (!sp)
		return NULL;

	sp->x = x;
	sp->y = y;
	sp->enemy = enemy;
	sp->side = SPACESHIP_SIDE; // default para 10
	sp->control = createJoystick();
	sp->sprite = createSprite(spriteFolderPath);

	return sp;
}

// Movimenta a nave (SPACESHIP* sp) até o limite da tela (SCREEN* sc)
void moveSpaceship(SPACESHIP* sp, int stepCount, unsigned char trajectory, SCREEN* sc){
	if (!trajectory){
		sp->sprite->active = sp->sprite->left;
		if (sp->x - stepCount*SPACESHIP_STEP - sp->side/2 >= 0)
			// Movimentação para a esquerda
			sp->x = sp->x - stepCount*SPACESHIP_STEP;
		else sp->x = sp->side/2;
	}
	else if (trajectory == 1) {
		sp->sprite->active = sp->sprite->right;	
		if (sp->x + stepCount*SPACESHIP_STEP + sp->side/2 <= sc->max_x)
			// Movimentação para a direita
			sp->x = sp->x + stepCount*SPACESHIP_STEP;
		else sp->x = sc->max_x - sp->side/2;
	}
	else if (trajectory == 2) {
		sp->sprite->active = sp->sprite->front;
		if (sp->y - stepCount*SPACESHIP_STEP - sp->side/2 >= 0)
			// Movimentação para cima
			sp->y = sp->y - stepCount*SPACESHIP_STEP;
		else sp->y = sp->side/2;
	}
	else if (trajectory == 3) {
		sp->sprite->active = sp->sprite->front;
		if (sp->y + stepCount*SPACESHIP_STEP + sp->side/2 <= sc->max_y)
			// Movimentação para baixo
			sp->y = sp->y + stepCount*SPACESHIP_STEP;
		else sp->y = sc->max_y - sp->side/2;
	}
}

void drawSpaceship(SPACESHIP* sp){

	int bitmap_width = al_get_bitmap_width(sp->sprite->active);
	int bitmap_height = al_get_bitmap_height(sp->sprite->active);

	if (!(sp->enemy))
		al_draw_scaled_bitmap(
			sp->sprite->active,
			0,0,
			bitmap_width, bitmap_height,  
			sp->x-sp->side/2, sp->y-sp->side/2,                         
			sp->side, sp->side,
			0                           
		);
	else 
		al_draw_scaled_bitmap(
			sp->sprite->active,
			0,0,
			bitmap_width, bitmap_height,
			sp->x-sp->side/2, sp->y-sp->side/2,
			sp->side, sp->side,
			ALLEGRO_FLIP_HORIZONTAL | ALLEGRO_FLIP_VERTICAL				
	);
}

void destroySpaceship(SPACESHIP* sp){
	destroyJoystick(sp->control);
	destroySprite(sp->sprite);
	free(sp);	
}
