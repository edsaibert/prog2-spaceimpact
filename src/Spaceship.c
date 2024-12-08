#include "Spaceship.h"

SPACESHIP* createSpaceship(int x, int y, int enemy, int health, int side, const char* spriteFolderPath){
	SPACESHIP* sp;

	sp = (SPACESHIP*) malloc(sizeof(SPACESHIP));
	if (!sp)
		return NULL;

	sp->x = x;
	sp->y = y;
	sp->enemy = enemy;
	sp->side = side;
	sp->control = createJoystick();
	sp->sprite = createSprite(spriteFolderPath);
	sp->gun = createGun();
	sp->health = health;
	sp->score = 0;
	sp->shield = 0;

	return sp;
}

// Movimenta a nave (SPACESHIP* sp) até o limite da tela (SCREEN* sc)
void moveSpaceship(SPACESHIP* sp, int stepCount, unsigned char trajectory, SCREEN* sc){
	if (!trajectory){
		sp->sprite->active = sp->sprite->front;
		if (sp->x - stepCount*SPACESHIP_STEP - sp->side/2 >= 0)
			// Movimentação para a esquerda
			sp->x = sp->x - stepCount*(SPACESHIP_STEP+4);
		else sp->x = sp->side/2;
	}
	else if (trajectory == 1) {
		sp->sprite->active = sp->sprite->front;	
		if (sp->x + stepCount*SPACESHIP_STEP + sp->side/2 <= sc->max_x)
			// Movimentação para a direita
			sp->x = sp->x + stepCount*(SPACESHIP_STEP+4);
		else sp->x = sc->max_x - sp->side/2;
	}
	else if (trajectory == 2) {
		sp->sprite->active = sp->sprite->left;
		if (sp->y - stepCount*SPACESHIP_STEP - sp->side/2 >= 0)
			// Movimentação para cima
			sp->y = sp->y - stepCount*(SPACESHIP_STEP+4);
		else sp->y = sp->side/2;
	}
	else if (trajectory == 3) {
		sp->sprite->active = sp->sprite->right;
		if (sp->y + stepCount*SPACESHIP_STEP + sp->side/2 <= sc->max_y)
			// Movimentação para baixo
			sp->y = sp->y + stepCount*(SPACESHIP_STEP+4);
		else sp->y = sc->max_y - sp->side/2;
	}
}

void compareFunctionPlayer(SPACESHIP* sp, SPACESHIP* enemy, SCREEN* sc, void (*positionFunction)(SPACESHIP *, int, unsigned char, SCREEN *)){
	float* d = NULL;
	/*
		Caso tenha tido colisao com um inimigo = enemy != NULL
	*/
	if (enemy){
		d = normalizedDistance(sp->x, sp->y, enemy->x, enemy->y);	
	}

	if (sp->control->left && (!d || d[0] > -EPSILON)){
	positionFunction(sp, 1, 0, sc);
	}
	if (sp->control->right && (!d || d[0] < EPSILON)){
	positionFunction(sp, 1, 1, sc);
	}
	if (sp->control->up && (!d || d[1] > -EPSILON)){
	positionFunction(sp, 1, 2, sc);
	}
	if (sp->control->down && (!d || d[1] < EPSILON)){
	positionFunction(sp, 1, 3, sc);
	}

}

void compareFunctionUpDownEnemy(SPACESHIP* sp, SPACESHIP* enemy, SCREEN* sc, void (*positionFunction)(SPACESHIP *, int, unsigned char, SCREEN *)){
	/*
		Caso tenha tido colisao com um inimigo = enemy != NULL
	*/

	if (sp->control->left){
		positionFunction(sp, 1, 0, sc);
	}
	if (sp->control->right){
		positionFunction(sp, 1, 1, sc);
	}
	if (sp->control->up){
		positionFunction(sp, 1, 2, sc);
	}
	if (sp->control->down){
		positionFunction(sp, 1, 3, sc);
	}
}


void compareFunctionFollowX(SPACESHIP* sp, SPACESHIP* enemy, SCREEN* sc, void (*positionFunction)(SPACESHIP *, int, unsigned char, SCREEN *)){
	float *d = NULL;

	d = normalizedDistance(sp->x, sp->y, enemy->x, enemy->y);

	// padrão de movimentação que segue o player no eixo x

	if (d[0] > EPSILON){
		positionFunction(sp, 1, 1, sc);
	}
	else if (d[0] < -EPSILON){
		positionFunction(sp, 1, 0, sc);
	}
	else {
		if (d[1] > EPSILON){
			positionFunction(sp, 1, 3, sc);
		}
		else if (d[1] < -EPSILON){
			positionFunction(sp, 1, 2, sc);
		}
	}
	
}

void updateSpaceshipPosition(SPACESHIP* sp, SPACESHIP* enemy, SCREEN* sc, void (*positionFunction) (SPACESHIP*, int, unsigned char, SCREEN*), void (*comparisonFunction) (SPACESHIP*, SPACESHIP*, SCREEN*, void (*positionFunction)(SPACESHIP*, int, unsigned char, SCREEN*))){

	comparisonFunction(sp, enemy, sc, positionFunction);	

}


/*
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
*/

void hitSpaceship(SPACESHIP* sp, int damage){
	if (!sp) return;
	
	if (sp->shield) sp->shield -= damage;
	else sp->health -= damage;

	if (sp->shield <= 0){
		sp->shield = 0;
	}

	if (sp->health <= 0){
		sp->health = 0;
	}
}

void shootSpaceship(SPACESHIP* sp){
	if (!sp) return;

	if (sp->control->shoot) shotGun(sp->x, sp->y, 0, sp->gun); // A nave está parada

}

int checkIfSpaceshipIsDead(SPACESHIP* sp){
	if (!sp) return 1;

	if (sp->health == 0) return 1;
	return 0;
}

void drawSpaceship(SPACESHIP* sp) {
    if (!sp) return;

    float cx = sp->side / 2.0f;     
	float cy = sp->side / 2.0f;

    float angleEnemy = 3.0f * ALLEGRO_PI / 2.0f;
	float angle = ALLEGRO_PI / 2.0f;

	float xscale = (float) sp->side / (float)SPACESHIP_SIDE;
	float yscale = (float) sp->side / (float)SPACESHIP_SIDE;

	if (sp->shield){
		al_draw_filled_circle(
		sp->x, sp->y,
		sp->side/2 + 1,
		al_map_rgba(186, 245, 255, 75)
		);
	}

	if (sp->enemy){
		al_draw_scaled_rotated_bitmap(
				sp->sprite->active,  
				cx, cy,             
				sp->x, sp->y,      
				xscale, yscale,
				angleEnemy,            
				0                
    	);

	}
    else {
		al_draw_scaled_rotated_bitmap(
				sp->sprite->active,  
				cx, cy,             
				sp->x, sp->y,      
				xscale, yscale,
				angle,            
				0                
    	);
	}
}

void destroySpaceship(SPACESHIP* sp){
	destroyJoystick(sp->control);
	destroyGun(sp->gun);
	destroySprite(sp->sprite);
	free(sp);	
	sp = NULL;
}
