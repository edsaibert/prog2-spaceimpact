#ifndef ENEMY_H
#define ENEMY_H

#include "Spaceship.h"
#include "Position.h"

#define NUMBER_OF_ENEMIES 5

typedef struct enemies {
    SPACESHIP* closerEnemy;
    struct enemies* next;
} ENEMIES;

// Cria a lista de inimigos
ENEMIES* createEnemyList(SCREEN* sc);
// Checa se existe uma colisão entre as coordenadas dadas e algum inimigo e caso tenha, retorna o inimigo com o qual o as coordenadas colidiram
SPACESHIP* checkCollisionFromEnemies(ENEMIES* enemies, int x, int y, int side);
// Atualiza a lista de inimigos caso uma bala tenha tido colisão com um inimigo
void hitEnemy(ENEMIES* enemies, SPACESHIP* enemy);

void drawEnemies(ENEMIES* enemies);

void destroyEnemyList(ENEMIES* enemies);



#endif
