#include "Boss.h"

void addBoss(ENEMIES** head, int x, int y, int side, int health, MOVEMENT_PATTERN movement_pattern, const char* path){
	SPACESHIP* boss = createSpaceship(x, y, 1, health, side, path);
	if (!boss) return;

	insertIntoEnemyList(head, boss, movement_pattern);
	
}

void updateScreenForBoss(ENEMIES** head, SPACESHIP* sp, SCREEN* sc){
	ENEMIES* temp = *head;

	while (temp != NULL){
		ENEMIES* nextTemp = temp->next;
		temp->originX = sc->max_x - 150;
		temp->originY = sc->max_y/2;

		switch (temp->movement_pattern){
			// LINEAR: BOSS VOLTA PARA A ORIGEM

			case LINEAR:

				if (temp->closerEnemy->x == temp->originX && temp->closerEnemy->y == temp->originY){
					temp->movement_pattern = DODGE;
					break;

				}
				if (temp->originX < temp->closerEnemy->x){
					temp->closerEnemy->control->left = 0;
					temp->closerEnemy->control->right = 1;
				}
				else if (temp->originX > temp->closerEnemy->x){
					temp->closerEnemy->control->right = 0;
					temp->closerEnemy->control->left = 1;
				}

				if (temp->originY < temp->closerEnemy->y){
					temp->closerEnemy->control->down = 1;
					temp->closerEnemy->control->up = 0;
				}

				else if (temp->originY > temp->closerEnemy->y){
					temp->closerEnemy->control->up = 1;
					temp->closerEnemy->control->down = 0;
				}
	
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
		

		temp = nextTemp;
	}
}


