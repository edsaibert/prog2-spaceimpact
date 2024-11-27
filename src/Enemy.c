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

void moveEnemySpaceship(SPACESHIP* sp, int stepCount, unsigned char trajectory, SCREEN* sc){
	if (!trajectory){
		sp->sprite->active = sp->sprite->front;
		if (sp->x - stepCount*SPACESHIP_STEP - sp->side/2 >= -sp->side)
			// Movimentação para a esquerda
			sp->x = sp->x - stepCount*SPACESHIP_STEP;
		else sp->x = -sp->side;
	}
	else if (trajectory == 1) {
		sp->sprite->active = sp->sprite->front;	
		if (sp->x + stepCount*SPACESHIP_STEP + sp->side/2 <= sc->max_x)
			// Movimentação para a direita
			sp->x = sp->x + stepCount*SPACESHIP_STEP;
		else sp->x = sc->max_x - sp->side/2;
	}
	else if (trajectory == 2) {
		sp->sprite->active = sp->sprite->left;
		if (sp->y - stepCount*SPACESHIP_STEP - sp->side/2 >= 0)
			// Movimentação para cima
			sp->y = sp->y - stepCount*SPACESHIP_STEP;
		else sp->y = sp->side/2;
	}
	else if (trajectory == 3) {
		sp->sprite->active = sp->sprite->right;
		if (sp->y + stepCount*SPACESHIP_STEP + sp->side/2 <= sc->max_y)
			// Movimentação para baixo
			sp->y = sp->y + stepCount*SPACESHIP_STEP;
		else sp->y = sc->max_y - sp->side/2;
	}
}

void updateScreenForEnemies(ENEMIES** head, SCREEN* sc) {                                            
    ENEMIES* temp = *head;
    if (*head == NULL) return;

    while (temp != NULL) {
        ENEMIES* nextTemp = temp->next;

        moveEnemySpaceship(temp->closerEnemy, 1, 0, sc);

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

	for (int i = 0; i < NUMBER_OF_ENEMIES; i++){
		int randomX = rand() % (sc->max_x + 1);
		int randomY = rand() % (sc->max_y + 1);

		SPACESHIP* enemy = createSpaceship(randomX, randomY, 1, "./sprites/spaceships/player/ship_1/");
		if (!enemy) {return NULL;};
		
		insertIntoEnemyList(&head, enemy);
	}

	return head;
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
