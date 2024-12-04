#include "Item.h"

ITEM* createItemNode(int x, int y, ITEM_TYPE type, int value, const char* path){
    ITEM* node = (ITEM*) malloc(sizeof(ITEM));
    node->x = x;
    node->y = y;
    node->type = type;
    node->value = value;
    node->next = NULL;
    node->side = 24;

    node->sprite = al_load_bitmap(path);
    if (!node->sprite) return NULL;

    return node;
}

int checkIfSlotAvailable(ITEM* head, int x, int y, ITEM_TYPE type){
    if (!head) return 1;
    ITEM* temp = head;

    while (temp != NULL){
        if (checkCollision(temp->x, temp->y, x, y, 3, 3) || temp->type == type)
            return 0;
        temp = temp->next;
    }
    return 1;
}

void insertIntoItemList(ITEM** head, int x, int y, ITEM_TYPE type, int value, const char* path){
    if (!checkIfSlotAvailable(*head, x, y, type)) return;

    ITEM* node = createItemNode(x, y, type, value, path);

    if (*head == NULL)
        *head = node;
    else {
        ITEM* temp = *head;
        while (temp->next != NULL){
            temp = temp->next; 
            }
        temp->next = node;
    }
}

void addItem(ITEM** head, SCREEN* sc, ALLEGRO_TIMER* timer ){
 
	int randomY = 0 + (rand() % (sc->max_y + 1));
    int randomX = 0 + (rand() % (sc->max_x + 1));

    int randomN = rand() % 100;

    switch ((al_get_timer_count(timer) /30) % 10){
        case 0:
            if (randomN == 0)
                insertIntoItemList(head, randomX, randomY, HEALTH, 10, "./sprites/others/life.png");
            break;
        case 3:
             if (randomN == 0)
                insertIntoItemList(head, randomX, randomY, SHIELD, 10, "./sprites/others/shield.png");
            break;
        case 5:
            if (randomN == 0)
                insertIntoItemList(head, randomX, randomY, FLAMES, 10, "./sprites/others/barreado.png");
            break;
        case 7:
            if (randomN == 0)
                insertIntoItemList(head, randomX, randomY, LIGHTNING, 1, "./sprites/others/lightning.png");
            break;
        default:
            break;
    }
}

void doItemAction(SPACESHIP* sp, ITEM* item){
	switch (item->type){
		case HEALTH:
            if (sp->health += item->value > 20){
                sp->health = 20;
                break;
            }
            sp->health += item->value;
			break;
		case SHIELD:
            sp->shield = item->value;
			break;
		case FLAMES:
			sp->gun->specialAttack = item->value;
			break;
		case LIGHTNING:
			break;
	}
}

void checkCollisionFromItem(ITEM** head, SPACESHIP* sp){
    if (!head || !*head || !sp) return;

    ITEM* temp = *head;
    ITEM* prev = NULL;
    
    while (temp != NULL) {
        ITEM* nextTemp = temp->next;

        if (checkCollision(temp->x, temp->y, sp->x, sp->y, 2, sp->side)) {
            doItemAction(sp, temp);
            removeFromItemList(head, temp);
            if (prev) {
                prev->next = nextTemp;
            }
            temp = nextTemp;
            continue;
        }

        prev = temp;
        temp = nextTemp;
    }

}

void drawItem(ITEM* item){
    if (!item) return;
	ITEM* current = item;

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

void removeFromItemList(ITEM** head, ITEM* item){
    if (!head || !*head || !item) {
        return; 
    }

    ITEM* current = *head;
    ITEM* prev = NULL;

    while (current != NULL) {
        if (current == item) {
            if (prev == NULL) {
                *head = current->next;
            } else {
                prev->next = current->next;
            }

            al_destroy_bitmap(current->sprite);
            free(current);
            return;
        }

        prev = current;
        current = current->next;
    }
}

void updateScreenForItems(ITEM** head, SCREEN* sc){
    ITEM* temp = *head;
    ITEM* prev = NULL;

    while (temp != NULL){
        ITEM* nextTemp = temp->next;

        if (temp->x < -50 || temp->x > sc->max_x + 50 || temp->y < -50 || temp->y > sc->max_y + 50) { // tolerancia
            removeFromItemList(head, temp);
            if (prev) {
                prev->next = nextTemp;
            }
            temp = nextTemp; 
            continue;
        }

        temp->x += ITEM_MOVE; //direita

        prev = temp;
        temp = nextTemp;
    }
}

void destroyItemList(ITEM* head){
    ITEM* current = head;
    ITEM* aux;

    while (current != NULL) {
        aux = current->next;
        al_destroy_bitmap(current->sprite);
        free(current);
        current = aux;
    }
}

