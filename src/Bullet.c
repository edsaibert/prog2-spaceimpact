#include "Bullet.h"

BULLET* createBulletNode(int x, int y, unsigned char trajectory, BULLET_TYPE bulletType){
	BULLET* node = (BULLET*) malloc(sizeof(BULLET));
	node->x = x;
	node->y = y;
	node->trajectory = trajectory;
	node->next = NULL;
	node->bulletType = bulletType;

	if (bulletType == SPECIAL)
		node->sprite = al_load_bitmap("./sprites/others/special_attack.png");
	else node->sprite = NULL;

	return node;
}

BULLET* createBulletList(){
	BULLET* head = NULL;
	return head;
}

void insertIntoBulletList(BULLET** head, int x, int y, unsigned char trajectory, BULLET_TYPE bulletType){
	BULLET* node = createBulletNode(x, y, trajectory, bulletType);

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

/*
	Checa colisão e se encontrada, remove a bala colidida da lista de balas
*/
int checkCollisionFromBullet(BULLET** head, int x, int y, int side) {
    if (!head || !*head) return 0;

    BULLET* temp = *head;
	BULLET* prev = NULL;
	int damage = 0;

    while (temp != NULL) {
		BULLET* nextTemp = temp->next;

        if (checkCollision(temp->x, temp->y, x, y, 2, side)) {
			removeFromBulletList(head, temp);            

			switch (temp->bulletType){
				case SIMPLE:
					damage += 1;
					break;
				case SPECIAL:
					damage += 3;
					break;
			}

			if (prev){
				prev->next = nextTemp;
			}
			temp = nextTemp;
			continue;
		}
           
		prev = temp;
		temp = nextTemp;
    }

    return damage; 
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

        if (!(temp->trajectory)) temp->x += BULLET_MOVE;		//direita
        if (temp->trajectory == 1) temp->x -= BULLET_MOVE;	//esquerda
        if (temp->trajectory == 2) temp->y += BULLET_MOVE;	//baixo
        if (temp->trajectory == 3) temp->y -= BULLET_MOVE;	//cima	

        prev = temp; 
        temp = nextTemp; 
    }
}

void drawBullet(BULLET* bullet){
	if (!bullet) return;

	BULLET* current = bullet;
	
	while (current != NULL){
		// desenha uma linha preta em volta da bola branca (ajuda na visualização)
		switch (bullet->bulletType){
			case SIMPLE:
				al_draw_filled_circle(current->x, current->y, 2, al_map_rgb(0, 0, 0));
				al_draw_filled_circle(current->x, current->y, 1, al_map_rgb(255, 255, 255));
				break;

			case SPECIAL:
				al_draw_bitmap(current->sprite, current->x, current->y, 0);
				break;
				
		}
		current = current->next;
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
