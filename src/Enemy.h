#ifndef ENEMY_H
#define ENEMY_H

#include "Spaceship.h"
#include "Position.h"

#define NUMBER_OF_ENEMIES 5

typedef enum {
	LINEAR,
	UP_DOWN,
	FOLLOW_X,
	RANDOM,
	FOLLOW_ALL
} MOVEMENT_PATTERN;

typedef struct enemies {
    SPACESHIP* closerEnemy;
	MOVEMENT_PATTERN movement_pattern;
    struct enemies* next;
} ENEMIES;

// Cria a lista de inimigos
ENEMIES* createEnemyList(SCREEN* sc);
// Checa se existe uma colisão entre as coordenadas dadas e algum inimigo e caso tenha, retorna o inimigo com o qual o as coordenadas colidiram
SPACESHIP* checkCollisionFromEnemies(ENEMIES* enemies, int x, int y, int side);

void hitPlayer(ENEMIES** enemies, SPACESHIP* sp);

ENEMIES* createEnemyNode(SPACESHIP* enemy);

void insertIntoEnemyList(ENEMIES** head, SPACESHIP* enemy);

// Atualiza a lista de inimigos caso uma bala tenha tido colisão com um inimigo
void hitEnemies(ENEMIES* enemies, SPACESHIP* enemy);

void enemiesShoot(ENEMIES* head, SCREEN* sc);

void drawEnemyBullets(ENEMIES* head);

void addEnemy(ENEMIES** head, SCREEN* sc);

void removeFromEnemyList(ENEMIES** head, SPACESHIP* enemy);

void updateScreenForEnemies(ENEMIES** head, SPACESHIP* sp, SCREEN* sc);

void drawEnemies(ENEMIES* enemies);

void destroyEnemyList(ENEMIES* enemies);



#endif
