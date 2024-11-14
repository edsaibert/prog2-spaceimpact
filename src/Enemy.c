#include "Enemy.h"

ENEMIES* createNode(SPACESHIP* enemy){
	ENEMIES* node = (ENEMIES*) malloc(sizeof(ENEMIES));
	node->closerEnemy = enemy;
	node->next = NULL;
	return node;
}

void insertIntoList(ENEMIES** head, SPACESHIP* enemy){
	ENEMIES* node = createNode(enemy);
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

ENEMIES* createEnemyList(SCREEN* sc){
	ENEMIES* head = NULL;

	for (int i = 0; i < NUMBER_OF_ENEMIES; i++){
		int randomX = rand() % (sc->max_x + 1);
		int randomY = rand() % (sc->max_y + 1);

		SPACESHIP* enemy = createSpaceship(randomX, randomY, 1, "./../sprites/player/ship_1/");
		if (!enemy) return NULL;
		
		insertIntoList(&head, enemy);
	}
	
}

// Verifica se há colisão com algum inimigo, caso houver, retorna o inimigo
SPACESHIP* checkCollisionFromEnemies(ENEMIES* enemies, int x, int y){
	ENEMIES* head = enemies;
	int collision = 0;

	while (head->next != NULL){
		collision = checkCollision(head->enemy->x, head->enemy->y, x, y);

		if (collision) {
			return head->enemy;
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
		destroySpaceship(current->enemy);
		free(current);
		current = aux;
	}
	
}
