#include "Boss.h"

BOSS* addBoss(int x, int y, int side, int health, MOVEMENT_PATTERN movement_pattern, LEVEL_ID currentLevel, const char* path, SCREEN* sc){
	SPACESHIP* boss = createSpaceship(x, y, 1, health, side, path);
	if (!boss) return NULL;

	BOSS* b = (BOSS*) malloc(sizeof(BOSS));
	if (!b) return NULL;

	b->sp = boss;
	b->originX = sc->max_x - 200;
	b->originY = sc->max_y / 2;
	b->movement_pattern = movement_pattern;
	b->currentLevel = currentLevel;
	b->lastSeconds = 0;

	return b;
}

void hitPlayerBoss(BOSS** boss, SPACESHIP* sp, SCREEN* sc){
	if (!*boss) return;

	int damageToBoss = 0;
	int damageToPlayer = 0;

	damageToPlayer += checkCollisionFromBullet(&((*boss)->sp->gun->shots), sp->x, sp->y, sp->side);
	hitSpaceship(sp, damageToPlayer);

	if (sp->gun->isLightning){
		sp->gun->isLightning = 0;
		sp->score += 1;

		damageToBoss += 10;
	}

	damageToBoss += checkCollisionFromBullet(&(sp->gun->shots), (*boss)->sp->x, (*boss)->sp->y, (*boss)->sp->side);
	hitSpaceship((*boss)->sp, damageToBoss);
}

void bossShoot(LEVEL_ID level, BOSS* boss, SCREEN* sc){

	if (boss->sp->gun->specialMajor && level == FIRST_BOSS){
		if ((rand() % 50 + 1) == 1)
			shotGunBoss(boss->currentLevel, boss->sp->x, boss->sp->y, 1, boss->sp->gun);
		return;
	}

	if (boss->sp->gun->specialMajor && level == LAST_BOSS){
		
		for (int i = 10; i < sc->max_x - 10; i+=10){
			if ((rand() % 180 + 1) == 1)
				shotGunBoss(boss->currentLevel, i, -10, 2, boss->sp->gun);
		}
	}

	if ((rand() % 150 + 1) < 5)
		shotGunBoss(boss->currentLevel, boss->sp->x, boss->sp->y, 1, boss->sp->gun);

	if (!(boss->sp->gun->specialMajor || boss->sp->gun->specialMinor)){
		if ((rand() % 150 + 1) < 5)
			shotGunBoss(boss->currentLevel, boss->sp->x, boss->sp->y, 2, boss->sp->gun);
			
		if ((rand() % 150 + 1) < 5)
			shotGunBoss(boss->currentLevel, boss->sp->x, boss->sp->y, 3, boss->sp->gun);
	}
}

void compareFunctionDodge(SPACESHIP* sp, SPACESHIP* enemy, SCREEN* sc, void (*positionFunction)(SPACESHIP *, int, unsigned char, SCREEN *)){
	float* d = normalizedDistance(sp->x, sp->y, enemy->x, enemy->y);	

	if (fabs(d[0]) > fabs(d[1])) { 
		positionFunction(sp, 1, d[1] < 0 ? 3 : 2, sc); 
	} else {  
		positionFunction(sp, 1, d[0] < 0 ? 1 : 0, sc);
	}
}

void moveBoss(SPACESHIP* sp, int stepCount, unsigned char trajectory, SCREEN* sc){
	if (!trajectory){
		sp->sprite->active = sp->sprite->front;
		if (sp->x - stepCount*SPACESHIP_STEP - sp->side/2 >= 100)
			// Movimentação para a esquerda
			sp->x = sp->x - stepCount*(SPACESHIP_STEP);
		else sp->x = sp->side/2 + 100;
	}
	else if (trajectory == 1) {
		sp->sprite->active = sp->sprite->front;	
		if (sp->x + stepCount*SPACESHIP_STEP + sp->side/2 <= sc->max_x - 200)
			// Movimentação para a direita
			sp->x = sp->x + stepCount*(SPACESHIP_STEP);
		else sp->x = sc->max_x - sp->side/2 - 200;
	}
	else if (trajectory == 2) {
		sp->sprite->active = sp->sprite->left;
		if (sp->y - stepCount*SPACESHIP_STEP - sp->side/2 >= 100)
			// Movimentação para cima
			sp->y = sp->y - stepCount*(SPACESHIP_STEP);
		else sp->y = sp->side/2 + 100;
	}
	else if (trajectory == 3) {
		sp->sprite->active = sp->sprite->right;
		if (sp->y + stepCount*SPACESHIP_STEP + sp->side/2 <= sc->max_y - 100)
			// Movimentação para baixo
			sp->y = sp->y + stepCount*(SPACESHIP_STEP);
		else sp->y = sc->max_y - sp->side/2 - 100;
	}
}

void updateScreenForBoss(BOSS** boss, ALLEGRO_TIMER* timer, SPACESHIP* sp, SCREEN* sc){
	if (!boss) return;

	BOSS* temp = *boss;
	int newTimer = (int) al_get_timer_count(timer);
	printf("timer: %d\n", newTimer);

	switch (temp->movement_pattern){
		case LINEAR:

			// LINEAR: BOSS VOLTA PARA A ORIGEM
			if (abs(temp->sp->x - temp->originX) < temp->sp->side && abs(temp->sp->y - temp->originY) < temp->sp->side){
				temp->movement_pattern = FOLLOW_X;
				printf("linear to dodge");
				break;

			}
			if (temp->originX < temp->sp->x){
				temp->sp->control->left = 1;
				temp->sp->control->right = 0;
			}
			else if (temp->originX > temp->sp->x){
				temp->sp->control->right = 1;
				temp->sp->control->left = 0;
			}

			if (temp->originY < temp->sp->y){
				temp->sp->control->down = 0;
				temp->sp->control->up = 1;
			}

			else if (temp->originY > temp->sp->y){
				temp->sp->control->up = 0;
				temp->sp->control->down = 1;
			}

			temp->sp->gun->specialMajor = 1;
			temp->sp->gun->specialMinor = 0;
			updateSpaceshipPosition(temp->sp, sp, sc, moveBoss, compareFunctionUpDownEnemy);

			break;
		case FOLLOW_X:
			if (newTimer % (600) == 0){
				temp->movement_pattern = DODGE; }
			temp->sp->gun->specialMajor = 0;
			updateSpaceshipPosition(temp->sp, sp, sc, moveBoss, compareFunctionFollowX);
			break;
		// case SPECIAL_ATTACK:

		// 	temp->sp->gun->specialMajor = 10;
		// 	if (abs(temp->sp->x - (sc->max_x - 100)) < temp->sp->side && abs(temp->sp->y - 200) < temp->sp->side){
		// 		temp->movement_pattern = DODGE;
		// 		break;
		// 	}
		// 	if (sc->max_x - 100 < temp->sp->x){
		// 		temp->sp->control->left = 1;
		// 		temp->sp->control->right = 0;
		// 	}
		// 	else if (sc->max_x - 100 > temp->sp->x){
		// 		temp->sp->control->right = 1;
		// 		temp->sp->control->left = 0;
		// 	}

		// 	if ((sc->max_y - 200) < temp->sp->y){
		// 		temp->sp->control->down = 0;
		// 		temp->sp->control->up = 1;
		// 	}

		// 	else if ((sc->max_y - 200) > temp->sp->y){
		// 		temp->sp->control->up = 0;
		// 		temp->sp->control->down = 1;
		// 	}

		// 	updateSpaceshipPosition(temp->sp, sp, sc, moveBoss, compareFunctionUpDownEnemy);

		// 	break;
		case DODGE:
			updateSpaceshipPosition(temp->sp, sp, sc, moveBoss, compareFunctionDodge);
			if (newTimer % (600) == 0){
				temp->movement_pattern = LINEAR;
			}
			
			temp->sp->gun->specialMinor = 1;
			break;
		default:
			break;

	}

	if ((*boss)->sp->health <= 0){
		destroyBoss((*boss));
	}
	

}

void destroyBoss(BOSS* boss){
	destroySpaceship(boss->sp);
	free(boss);
}


