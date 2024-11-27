#include "Bullet.h"

BULLET* createBulletNode(int x, int y, unsigned char trajectory){
	BULLET* node = (BULLET*) malloc(sizeof(BULLET));
	node->x = x;
	node->y = y;
	node->trajectory = trajectory;
	node->next = NULL;
	node->sprite = NULL;
	// node->sprite = al_load_bitmap("./sprites/explosions/explosion-1-g/");

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


void updateScreenForBullet(BULLET** head, SCREEN* sc) {
    BULLET* temp = *head;
    BULLET* prev = NULL; 

    while (temp != NULL) {
        BULLET* nextTemp = temp->next;  

		// Caso a bala tenha saído da tela
        if (temp->x < -50 || temp->x > sc->max_x + 50 || temp->y < -50 || temp->y > sc->max_y + 50) { // tolerancia
            removeFromBulletList(head, temp);
            if (prev) {
                prev->next = nextTemp;
            }
            temp = nextTemp; 
            continue;
        }

        if (!temp->trajectory) temp->x += BULLET_MOVE;
        if (temp->trajectory == 1) temp->x -= BULLET_MOVE;
        if (temp->trajectory == 2) temp->y += BULLET_MOVE;
        if (temp->trajectory == 3) temp->y -= BULLET_MOVE;

        prev = temp; 
        temp = nextTemp; 
    }
}

int checkCollisionFromBullet(BULLET** head, int x, int y, int side){
	if (!head || !*head) return 0;

	BULLET* temp = *head;
	BULLET* prev = NULL;

	int damage = 0;

	while (temp != NULL){
		BULLET* nextTemp = temp->next;

		if (checkCollision(temp->x, temp->y, x, y, 2, side)){
			removeFromBulletList(head, temp);
			if (prev) {
				prev->next = nextTemp;
			}
			temp = nextTemp;

			damage += 1;
			continue;
		}

		prev = temp;
		temp = nextTemp;
	}

	return damage;
}

void drawBullet(BULLET* bullet){
	if (!bullet) return;

	al_draw_filled_circle(bullet->x, bullet->y, 2, al_map_rgb(0, 0, 0));
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
