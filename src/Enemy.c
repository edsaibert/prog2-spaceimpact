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
	int random = 0;

	ENEMIES* temp = head;
	while (temp->next != NULL){
		// define a dificuldade do inimigo
		if (temp->movement_pattern == FOLLOW_X)
			random = rand() % 50;
		else random = rand() % 100;

		if (random < 10){
			if (temp->movement_pattern == FOLLOW_X)
				shotGun(temp->closerEnemy->x, temp->closerEnemy->y, temp->closerEnemy->y-temp->closerEnemy->side/2 > sc->max_y/2 ? 3 : 2, temp->closerEnemy->gun);

			if (temp->movement_pattern == DOWN){
				shotGun(temp->closerEnemy->x, temp->closerEnemy->y, 2, temp->closerEnemy->gun);
				shotGun(temp->closerEnemy->x, temp->closerEnemy->y, 3, temp->closerEnemy->gun);

			}
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

int countEnemies(ENEMIES* enemies){
	int count = 0;
	ENEMIES* temp = enemies;

	while (temp){
		count += temp->closerEnemy->health;
		temp = temp->next;
	}

	return count;
}

void hitPlayer(ENEMIES** enemies, SPACESHIP* sp, SCREEN* sc) {
    if (!enemies || !*enemies) return;

    ENEMIES* temp = *enemies;
	int damageToPlayer = 0;
	int damageToEnemies = 0;

    while (temp) {
        damageToPlayer = checkCollisionFromBullet(&(temp->closerEnemy->gun->shots), sp->x, sp->y, sp->side);
        hitSpaceship(sp, damageToPlayer); 

		// Se o player pegou o ataque especial LIGTHNING
		if (sp->gun->isLightning){
			sp->gun->isLightning = 0;
			sp->score += countEnemies(*enemies);

			destroyEnemyList(*enemies);
			*enemies = NULL;
			return;
		}

		damageToEnemies = checkCollisionFromBullet(&(sp->gun->shots), temp->closerEnemy->x, temp->closerEnemy->y, temp->closerEnemy->side);
		hitSpaceship(temp->closerEnemy, damageToEnemies);
		sp->score += damageToEnemies;

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

		switch (temp->movement_pattern){
			case LINEAR:
				temp->closerEnemy->control->left = 1;
				updateSpaceshipPosition(temp->closerEnemy, sp, sc, moveEnemySpaceship, compareFunctionUpDownEnemy);

				break;

			case UP_DOWN:
				updateJoystickLeft(temp->closerEnemy->control);

				if (temp->closerEnemy->y > temp->originY + 10){
					temp->closerEnemy->control->up = 1;
					temp->closerEnemy->control->down = 0;
				}
				else if (temp->closerEnemy->y <= temp->originY - 10){
					temp->closerEnemy->control->up = 0;
					temp->closerEnemy->control->down = 1;
				}

				updateSpaceshipPosition(temp->closerEnemy, sp, sc, moveEnemySpaceship, compareFunctionUpDownEnemy);

				break;

			case FOLLOW_X:
				updateSpaceshipPosition(temp->closerEnemy, sp, sc, moveEnemySpaceship, compareFunctionFollowX);
				break;

			case FOLLOW_ALL:
				break;

			case DOWN:
				// Pode parar em um y qualquer da tela e continuar atirando no player
				if (rand() % 120 == 0 && temp->closerEnemy->y >= SPACESHIP_SIDE && temp->closerEnemy->y <= sc->max_y - SPACESHIP_SIDE){
					temp->closerEnemy->control->down = 0;
					temp->closerEnemy->control->up = 1;
					break;
				}

				temp->closerEnemy->control->down = 1;
				updateSpaceshipPosition(temp->closerEnemy, sp, sc, moveEnemySpaceship, compareFunctionUpDownEnemy);

				break;
		}


		if (temp->closerEnemy->x == -temp->closerEnemy->side || temp->closerEnemy->y == sc->max_y + temp->closerEnemy->side || temp->closerEnemy->health <= 0) {
            removeFromEnemyList(head, temp->closerEnemy);
            temp = *head;  
        } else {
            temp = nextTemp;
        }
    }
}


ENEMIES* createEnemyList(SCREEN* sc){
	ENEMIES* head = NULL;

	return head;
}

int noneWithType(ENEMIES* head, MOVEMENT_PATTERN type){
	ENEMIES* temp = head;
	while (temp != NULL){
		if (temp->movement_pattern == type) return 0;
		temp = temp->next;
	}
	return 1;
}

//adicionar enemy type
void addEnemy(ENEMIES** head, SCREEN* sc, ALLEGRO_TIMER *timer, LEVEL_ID currentLevel){
	int randomY;
	SPACESHIP *enemy;

	int minY = SPACESHIP_SIDE;
	int maxY = sc->max_y - SPACESHIP_SIDE;

	// Quantos segundos se passaram desde o início do jogo
	long int seconds = al_get_timer_count(timer)/30;

	if (rand() % 170 + 1 < 5){
		randomY = minY + (rand() % (maxY - minY + 1));
		enemy = createSpaceship(sc->max_x + SPACESHIP_SIDE, randomY, 1, 3, SPACESHIP_SIDE, "./sprites/spaceships/enemy/special-04/");


		if (!enemy) {return;};
		
		insertIntoEnemyList(head, enemy, LINEAR);
	}

	else if (currentLevel == FIRST && rand() % 170 + 1 < 2 && seconds > 20){
		randomY = minY + (rand() % (maxY - minY + 1));
		enemy = createSpaceship(sc->max_x + SPACESHIP_SIDE, randomY, 1, 3, SPACESHIP_SIDE, "./sprites/spaceships/player/ship_2/");
		updateJoystickUp(enemy->control);


		if (!enemy) {return;};
		
		insertIntoEnemyList(head, enemy, UP_DOWN);
	}

	else if (currentLevel == LAST && rand() % 170 + 1 < 2 && seconds > 20 && noneWithType(*head, FOLLOW_X)){
		randomY = minY + (rand() % (maxY - minY + 1));
		enemy = createSpaceship(sc->max_x + SPACESHIP_SIDE, randomY, 1, 5, SPACESHIP_SIDE, "./sprites/spaceships/player/ship_3/");
		updateJoystickUp(enemy->control);

		if (!enemy) {return;};

		insertIntoEnemyList(head, enemy, FOLLOW_X);
	}

	if (currentLevel == LAST && *head == NULL){
		for (int i = 2 * SPACESHIP_SIDE; i < sc->max_x-SPACESHIP_SIDE; i += 100){
			enemy = createSpaceship(i, -SPACESHIP_SIDE, 1, 5, SPACESHIP_SIDE, "./sprites/spaceships/enemy/special-02/");
			if (!enemy) {return;};
			insertIntoEnemyList(head, enemy, DOWN);
		}
	}
}

void drawEnemies(ENEMIES* head){
	if (!head) return;

	ENEMIES* temp = head;
	while (temp != NULL){
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
