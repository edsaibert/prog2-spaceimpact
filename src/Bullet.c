#include "Bullet.h"

BULLET* createBulletNode(int x, int y, unsigned char trajectory){
	BULLET* node = (BULLET*) malloc(sizeof(BULLET));
	node->x = x;
	node->y = y;
	node->trajectory = trajectory;
	node->next = NULL;

	return node;
}

BULLET* createBulletList(){
	BULLET* head = NULL;
	return head;
}

void insertIntoBulletList(BULLET** head, int x, int y, unsigned char trajectory){
	BULLET* node = createBulletNode(x, y, trajectory);

	if (*head == NULL)
		*head = node;
	else {
		BULLET* temp = *head;
		while (temp->next != NULL){
			temp = temp->next;
		}
		temp->next = node;
	}
}

void removeFromBulletList(BULLET** head, BULLET* bullet) {
    if (!head || !*head || !bullet) {
        return; 
    }

    BULLET* current = *head;
    BULLET* prev = NULL;

    while (current != NULL) {
        if (current == bullet) {
            if (prev == NULL) {
                *head = current->next;
            } else {
                prev->next = current->next;
            }

            free(current);
            return;
        }

        prev = current;
        current = current->next;
    }
}


void updateSreenForBullet(BULLET* head){
	BULLET* temp = head;

	while (temp->next != NULL){
		if (!temp->trajectory) temp->x = temp->x + BULLET_MOVE;
		if (temp->trajectory == 1) temp->x = temp->x - BULLET_MOVE;	
		if (temp->trajectory == 2) temp->y = temp->y + BULLET_MOVE;
		if (temp->trajectory == 3) temp->y = temp->y - BULLET_MOVE;
		temp = temp->next;
	}
}

void destroyBulletList(BULLET* head){
	BULLET* current = head;
	BULLET* aux;

	while (current != NULL) {
		aux = current->next;
		free(current);
		current = aux;
	}	

}
