#include "Enemy.h"

ENEMIES* createEnemyNode(SPACESHIP* enemy, MOVEMENT_PATTERN movement_pattern){
	ENEMIES* node = (ENEMIES*) malloc(sizeof(ENEMIES));
	node->closerEnemy = enemy;
	node->next = NULL;
	node->movement_pattern = movement_pattern;
	node->originX = enemy->x;
	node->originY = enemy->y;

	return node;
}

void insertIntoEnemyList(ENEMIES** head, SPACESHIP* enemy, MOVEMENT_PATTERN movement_pattern){
	ENEMIES* node = createEnemyNode(enemy, movement_pattern);

	if (*head == NULL)
		*head = node;
	else {
		ENEMIES* temp = *head;
		while (temp->next != NULL){
			temp = temp->next;
		}
		temp->next = node;
	}	
}

void removeFromEnemyList(ENEMIES** head, SPACESHIP* enemy){
	if (!head || !*head || !enemy) return;

	ENEMIES* current = *head;
	ENEMIES* prev = NULL;

	while (current != NULL){ 
		if (current->closerEnemy == enemy) {
			if (prev == NULL) {
				*head = current->next;
			} else {
				prev->next = current->next;
			}

			destroySpaceship(current->closerEnemy);
			free(current);
			return;
		}
		
		prev = current;
		current = current->next;

	}

}

void enemiesShoot(ENEMIES* head, SCREEN* sc){
	if (!head) return;

	ENEMIES* temp = head;
	while (temp->next != NULL){
		if (rand() % 100 < 10){
			shotGun(temp->closerEnemy->x, temp->closerEnemy->y, 1, temp->closerEnemy->gun);
		}
		temp = temp->next;
	}

}

void drawEnemyBullets(ENEMIES* head){
	if (!head) return;

	ENEMIES* temp = head;
	while (temp->next != NULL){
		drawBullet(temp->closerEnemy->gun->shots);
		temp = temp->next;
	}
}


void hitPlayer(ENEMIES** enemies, SPACESHIP* sp) {
    if (!enemies || !*enemies) return;

    ENEMIES* temp = *enemies;
	int damageToPlayer = 0;
	int damageToEnemies = 0;

    while (temp) {
        damageToPlayer = checkCollisionFromBullet(&(temp->closerEnemy->gun->shots), sp->x, sp->y, sp->side);
		damageToEnemies = checkCollisionFromBullet(&(sp->gun->shots), temp->closerEnemy->x, temp->closerEnemy->y, temp->closerEnemy->side);

        hitSpaceship(sp, damageToPlayer); 
		hitSpaceship(temp->closerEnemy, damageToEnemies);

        temp = temp->next;
    }
}

void moveEnemySpaceship(SPACESHIP* sp, int stepCount, unsigned char trajectory, SCREEN* sc){

	if (!trajectory){
		sp->sprite->active = sp->sprite->front;
			// Movimentação para a esquerda
			sp->x = sp->x - stepCount*SPACESHIP_STEP;
	}
	else if (trajectory == 1) {
		sp->sprite->active = sp->sprite->front;	
			// Movimentação para a direita
			sp->x = sp->x + stepCount*SPACESHIP_STEP;
	}
	else if (trajectory == 2) {
		sp->sprite->active = sp->sprite->left;
			// Movimentação para cima
			sp->y = sp->y - stepCount*SPACESHIP_STEP;
	}
	else if (trajectory == 3) {
		sp->sprite->active = sp->sprite->right;
			// Movimentação para baixo
			sp->y = sp->y + stepCount*SPACESHIP_STEP;
	}
}


void updateScreenForEnemies(ENEMIES** head, SPACESHIP* sp, SCREEN* sc) {                                            
    ENEMIES* temp = *head;
    if (*head == NULL) return;

    while (temp != NULL) {
        ENEMIES* nextTemp = temp->next;

		updateScreenForBullet(&(temp->closerEnemy->gun->shots), sc);

		/*
		if (!(sp->x + sp->side / 2 == temp->closerEnemy->x - temp->closerEnemy->side / 2 &&
			  sp->y + sp->side / 2 >= temp->closerEnemy->y - temp->closerEnemy->side / 2 &&
			  sp->y - sp->side / 2 <= temp->closerEnemy->y + temp->closerEnemy->side / 2))
		{
			temp->closerEnemy->sprite->active = temp->closerEnemy->sprite->front;

			if (temp->closerEnemy->x - SPACESHIP_STEP >= -temp->closerEnemy->side)
				temp->closerEnemy->x -= SPACESHIP_STEP;
			else
				temp->closerEnemy->x = -temp->closerEnemy->side;
		}
		*/

		switch (temp->movement_pattern){
			case LINEAR:
				temp->closerEnemy->control->left = 1;
				updateSpaceshipPosition(temp->closerEnemy, sp, sc, moveEnemySpaceship, compareFunctionUpDownEnemy);

				break;

			case UP_DOWN:

				printf("originY: %d, Y: %d", temp->originY, temp->closerEnemy->y);

				updateJoystickLeft(temp->closerEnemy->control);

				if (temp->closerEnemy->y > temp->originY + 10){
					temp->closerEnemy->control->up = 1;
					temp->closerEnemy->control->down = 0;
					// updateJoystickUp(temp->closerEnemy->control);
				}
				else if (temp->closerEnemy->y <= temp->originY - 10){
					// updateJoystickDown(temp->closerEnemy->control);
					temp->closerEnemy->control->up = 0;
					temp->closerEnemy->control->down = 1;
				}

				updateSpaceshipPosition(temp->closerEnemy, sp, sc, moveEnemySpaceship, compareFunctionUpDownEnemy);

				break;

			case FOLLOW_X:
				break;

			case FOLLOW_ALL:
				break;

			case RANDOM:
				break;
		}


		if (temp->closerEnemy->x == -temp->closerEnemy->side || temp->closerEnemy->health <= 0) {
			printf("Removendo inimigo\n");
            removeFromEnemyList(head, temp->closerEnemy);
            temp = *head;  
        } else {
            temp = nextTemp;
        }
    }
}


ENEMIES* createEnemyList(SCREEN* sc){
	ENEMIES* head = NULL;

	// for (int i = 0; i < NUMBER_OF_ENEMIES; i++){
	// 	int randomX = rand() % (sc->max_x + 1);
	// 	int randomY = rand() % (sc->max_y + 1);

	// 	SPACESHIP* enemy = createSpaceship(randomX, randomY, 1, "./sprites/spaceships/player/ship_1/");
	// 	if (!enemy) {return NULL;};
		
	// 	insertIntoEnemyList(&head, enemy);
	// }

	return head;
}

//adicionar enemy type
void addEnemy(ENEMIES** head, SCREEN* sc, ALLEGRO_TIMER *timer){
	int randomY;
	SPACESHIP *enemy;

	// Quantos segundos se passaram desde o início do jogo
	long int seconds = al_get_timer_count(timer)/60;

	if (rand() % 150 == 0){
		randomY = rand() % ((sc->max_y - SPACESHIP_SIDE/2) + 1);
		enemy = createSpaceship(sc->max_x + SPACESHIP_SIDE, randomY, 1, 3, "./sprites/spaceships/enemy/special-04/");


		if (!enemy) {return;};
		
		insertIntoEnemyList(head, enemy, LINEAR);
	}

	else if (rand() % 150 == 0 && seconds > 15){
		randomY = rand() % ((sc->max_y - SPACESHIP_SIDE/2) + 1);
		enemy = createSpaceship(sc->max_x + SPACESHIP_SIDE, randomY, 1, 3, "./sprites/spaceships/player/ship_2/");
		updateJoystickUp(enemy->control);


		if (!enemy) {return;};
		
		insertIntoEnemyList(head, enemy, UP_DOWN);
	}


}

void drawEnemies(ENEMIES* head){
	if (!head) return;

	ENEMIES* temp = head;
	while (temp->next != NULL){
		drawSpaceship(temp->closerEnemy);
		temp = temp->next;
	}
}

// Verifica se há colisão com algum inimigo, caso houver, retorna o inimigo
SPACESHIP* checkCollisionFromEnemies(ENEMIES* enemies, int x, int y, int side){
	if (!enemies) return NULL;

	ENEMIES* head = enemies;
	int collision = 0;

	while (head->next != NULL){
		collision = checkCollision(head->closerEnemy->x, head->closerEnemy->y, x, y, head->closerEnemy->side, side);

		if (collision) {
			return head->closerEnemy;
		}

		head = head->next;	
	}
	return NULL;
}

void destroyEnemyList(ENEMIES* enemy){
	ENEMIES* current = enemy;
	ENEMIES* aux;

	while (current != NULL){
		aux = current->next;
		destroySpaceship(current->closerEnemy);
		free(current);
		current = aux;
	}
	
}
