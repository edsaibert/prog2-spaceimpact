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

	return b;
}

void updateScreenForBoss(BOSS** boss, SPACESHIP* sp, SCREEN* sc){
	if (!boss) return;

	BOSS* temp = *boss;

	switch (temp->movement_pattern){
		case LINEAR:

			// LINEAR: BOSS VOLTA PARA A ORIGEM
			if (abs(temp->sp->x - temp->originX < temp->sp->side/2) && abs(temp->sp->y - temp->originY) < temp->sp->side/2){
				temp->movement_pattern = DODGE;
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

			updateSpaceshipPosition(temp->sp, sp, sc, moveEnemySpaceship, compareFunctionUpDownEnemy);

			break;
		case FOLLOW_X:
			//updateSpaceshipPosition(temp->closerEnemy, sp, sc, moveSpaceship, compareFunctionFollowX);
			break;
		case SPECIAL:
			//updateSpaceshipPosition(temp->closerEnemy, sp, sc, moveSpaceship, compareFunctionUpDownEnemy);

			break;
		case DODGE:
			//updateSpaceshipPosition(temp->closerEnemy, sp, sc, moveSpaceship, compareFunctionDodge);
			printf("oi\n");
			break;
	}
	

}


