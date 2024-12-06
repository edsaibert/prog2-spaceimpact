#ifndef LEVEL_H
#define LEVEL_H

#include "../main.h"
#include "Spaceship.h"
#include "Joystick.h"
#include "Screen.h"
#include "Position.h"
#include "Enemy.h"
#include "Background.h"
#include "Item.h"
#include "Uid.h"
#include "Boss.h"

typedef struct level {
    LEVEL_ID currentLevel;    
    SPACESHIP* sp;
    ENEMIES* enemies;
    SCREEN* sc;
    ITEM* items;
    BACKGROUND* bg;

    int animation;
} LEVEL;

LEVEL* beginGame(SPACESHIP* sp, ENEMIES* enemies, SCREEN* sc, ITEM* items, BACKGROUND* bg);

int loadLevel(LEVEL* game, ALLEGRO_TIMER* timer, ALLEGRO_FONT* font, SPACESHIP* enemyCollision, int* thunder);

void loadFirstBoss(LEVEL* game, BOSS** boss, ALLEGRO_TIMER* timer, ALLEGRO_FONT* font, SPACESHIP* enemyCollision, int *thunder);

void endFirstBoss(LEVEL* game);

void loadLastBoss(LEVEL* game);

void endLastBoss(LEVEL* game);

void destroyLevel(LEVEL* game);

#endif
