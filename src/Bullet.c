#include "Bullet.h"

BULLET* createBulletNode(int x, int y, unsigned char trajectory, BULLET_TYPE bulletType){
	BULLET* node = (BULLET*) malloc(sizeof(BULLET));
	node->x = x;
	node->y = y;
	node->trajectory = trajectory;
	node->next = NULL;
	node->bulletType = bulletType;

	if (bulletType == SPECIAL){
		node->side = 15;
		node->sprite = al_load_bitmap("./sprites/others/spark1.png");
	}
	else if (bulletType == SPECIAL_MAJOR_FIRST){
		node->side = 20;
		node->sprite = al_load_bitmap("./sprites/others/eye.png");
	}
	else if (bulletType == SPECIAL_MINOR_FIRST){
		node->side = 20;
		node->sprite = al_load_bitmap("./sprites/others/special_attack.png");
	}
	else if (bulletType == SPECIAL_MAJOR_LAST){
		node->side = 20;
		node->sprite = al_load_bitmap("./sprites/others/bolt.png");
	}
	else if (bulletType == SPECIAL_MINOR_LAST){
		node->side = 20;
		node->sprite = al_load_bitmap("./sprites/others/fireball.png");
	}
	else {
		node->side = 10;
		node->sprite = al_load_bitmap("./sprites/others/spark.png");
	};

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

        if (checkCollision(temp->x, temp->y, x, y, temp->side, side)) {

			switch (temp->bulletType){
				case SIMPLE:
					damage += 1;
					break;
				case SPECIAL:
					damage += 3;
					break;
				case SPECIAL_MINOR_FIRST: 
				case SPECIAL_MINOR_LAST:
					damage += 5;
					break;
				case SPECIAL_MAJOR_FIRST:
				case SPECIAL_MAJOR_LAST:
					damage += 10;
					break;
				default:
					break;
			}
			removeFromBulletList(head, temp);            

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
		al_draw_scaled_bitmap(
			current->sprite,           
			0, 0,                      
			al_get_bitmap_width(current->sprite),   
			al_get_bitmap_height(current->sprite),  
			current->x - current->side/2, current->y - current->side/2,    
			current->side, current->side,
			0                          
		);

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
