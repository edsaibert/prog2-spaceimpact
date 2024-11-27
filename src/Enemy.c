#include "Enemy.h"

ENEMIES* createEnemyNode(SPACESHIP* enemy){
	ENEMIES* node = (ENEMIES*) malloc(sizeof(ENEMIES));
	node->closerEnemy = enemy;
	node->next = NULL;

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
		if (rand() % 100 < 50){
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

void hitPlayer(ENEMIES** enemies, SPACESHIP* sp){
	if (!enemies || !*enemies) return;
	int damage = 0;

	ENEMIES* temp = *enemies;
	while (temp->next != NULL){
		damage = checkCollisionFromBullet(&(temp->closerEnemy->gun->shots), sp->x, sp->y, sp->side);
		hitSpaceship(sp, damage);
		temp = temp->next;
	}
}


void updateScreenForEnemies(ENEMIES** head, SPACESHIP* sp, SCREEN* sc) {                                            
    ENEMIES* temp = *head;
    if (*head == NULL) return;

    while (temp != NULL) {
        ENEMIES* nextTemp = temp->next;

		updateScreenForBullet(&(temp->closerEnemy->gun->shots), sc);

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

		if (temp->closerEnemy->x == -temp->closerEnemy->side) {
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
		enemy = createSpaceship(sc->max_x + SPACESHIP_SIDE, randomY, 1, "./sprites/spaceships/player/ship_1/");
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
