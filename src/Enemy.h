#ifndef ENEMY_H
#define ENEMY_H

#include "Spaceship.h"
#include "Position.h"

#define NUMBER_OF_ENEMIES 5


typedef struct enemies {
    SPACESHIP* closerEnemy;

	MOVEMENT_PATTERN movement_pattern;
	int originY;
	int originX;

    struct enemies* next;
} ENEMIES;

// Cria a lista de inimigos
ENEMIES* createEnemyList(SCREEN* sc);
// Checa se existe uma colisão entre as coordenadas dadas e algum inimigo e caso tenha, retorna o inimigo com o qual o as coordenadas colidiram
SPACESHIP* checkCollisionFromEnemies(ENEMIES* enemies, int x, int y, int side);

void hitPlayer(ENEMIES** enemies, SPACESHIP* sp, SCREEN* sc);

ENEMIES* createEnemyNode(SPACESHIP* enemy, MOVEMENT_PATTERN movement_pattern);

void insertIntoEnemyList(ENEMIES** head, SPACESHIP* enemy, MOVEMENT_PATTERN movement_pattern);

// Atualiza a lista de inimigos caso uma bala tenha tido colisão com um inimigo
void hitEnemies(ENEMIES* enemies, SPACESHIP* enemy);

void enemiesShoot(ENEMIES* head, SCREEN* sc);

void drawEnemyBullets(ENEMIES* head);

void addEnemy(ENEMIES** head, SCREEN* sc, ALLEGRO_TIMER *timer, LEVEL_ID currentLevel);

void removeFromEnemyList(ENEMIES** head, SPACESHIP* enemy);

void updateScreenForEnemies(ENEMIES** head, SPACESHIP* sp, SCREEN* sc);

void drawEnemies(ENEMIES* enemies);

void destroyEnemyList(ENEMIES* enemies);



#endif
