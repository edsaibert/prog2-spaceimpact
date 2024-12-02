#include "Item.h"

ITEM* createItemNode(int x, int y, ITEM_TYPE type, int value, const char path){
    ITEM* node = (ITEM*) malloc(sizeof(ITEM));
    node->x = x;
    node->y = y;
    node->type = type;
    node->value = value;
    node->next = NULL;

    node->sprite = al_load_bitmap(path);
    if (!node->sprite) return NULL;

    return node;
}

void insertIntoItemList(ITEM** head, int x, int y, ITEM_TYPE type, int value, const char path){
    ITEM* node = createItemNode(x, y, type, value, sprite);

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

void doItemAction(SPACESHIP* sp, ITEM* item){}

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

    al_draw_bitmap(item->sprite, item->x, item->y, 0);
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

