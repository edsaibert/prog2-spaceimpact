#include "Enemy.h"

ENEMIES* createEnemyNode(SPACESHIP* enemy){
	ENEMIES* node = (ENEMIES*) malloc(sizeof(ENEMIES));
	node->closerEnemy = enemy;
	node->next = NULL;
	node->movement_pattern = UP_DOWN;
	node->originX = enemy->x;
	node->originY = enemy->y;

	return node;
}

void insertIntoEnemyList(ENEMIES** head, SPACESHIP* enemy){
	ENEMIES* node = createEnemyNode(enemy);

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
		if (rand() % 100 < 20){
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
				updateJoystickLeft(temp->closerEnemy->control);
				break;

			case UP_DOWN:
				int max_y = temp->originY + 10;
				int min_y = temp->originY - 10;

				updateJoystickLeft(temp->closerEnemy->control);

				if (temp->closerEnemy->y <= max_y){
					temp->closerEnemy->control->up = 1;
					temp->closerEnemy->control->down = 0;
					// updateJoystickUp(temp->closerEnemy->control);
				}
				else if (temp->closerEnemy->y >= min_y){
					// updateJoystickDown(temp->closerEnemy->control);
					temp->closerEnemy->control->up = 0;
					temp->closerEnemy->control->down = 1;
				}
				break;
		}

		updateSpaceshipPosition(temp->closerEnemy, sp, sc, moveEnemySpaceship);	


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
void addEnemy(ENEMIES** head, SCREEN* sc){
	int randomY = rand() % (sc->max_y + 1);

	SPACESHIP *enemy;

	if (rand() % 150 == 0){
		enemy = createSpaceship(sc->max_x + SPACESHIP_SIDE, randomY, 1, 3, "./sprites/spaceships/player/ship_1/");
		updateJoystickUp(enemy->control);

		if (!enemy) {return;};
		
		insertIntoEnemyList(head, enemy);
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
