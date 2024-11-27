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

void updateScreenForEnemies(ENEMIES* head, SCREEN* sc) {                                            
	ENEMIES* temp = head;
    ENEMIES* nextTemp = NULL;

	if (head == NULL) return;

    while (temp != NULL) {
		nextTemp = temp->next;

        moveSpaceship(temp->closerEnemy, 1, 0, sc);                                    
		printf("mem: %p\n", temp->closerEnemy);

        if (temp->closerEnemy->x == temp->closerEnemy->side / 2) {
			removeFromEnemyList(&head, temp->closerEnemy);
        }
        
        temp = nextTemp;
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
