#ifndef ITEM_H
#define ITEM_H

#include "../main.h"
#include "Spaceship.h"
#include "Screen.h"
#include "Position.h"

#define ITEM_MOVE 1

typedef enum {
    HEALTH,
    SHIELD,
    FLAMES,
    LIGHTNING,
} ITEM_TYPE;

typedef struct item {
    int x;
    int y;
    int value;
    int side;

    struct item* next;

    ITEM_TYPE type;
    ALLEGRO_BITMAP* sprite;
} ITEM;

ITEM* createItemNode(int x, int y, ITEM_TYPE type, int value, const char* path);

void insertIntoItemList(ITEM** head, int x, int y, ITEM_TYPE type, int value, const char* path);

void addItem(ITEM** head, SCREEN* sc, ALLEGRO_TIMER* timer );

void doItemAction(SPACESHIP* sp, ITEM* item);

void checkCollisionFromItem(ITEM** head, SPACESHIP* sp);

void drawItem(ITEM* item);

void removeFromItemList(ITEM** head, ITEM* item);

void updateScreenForItems(ITEM** head, SCREEN* sc);

void destroyItemList(ITEM* head);


#endif
