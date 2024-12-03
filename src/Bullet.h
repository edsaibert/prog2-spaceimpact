#ifndef BULLET_H
#define BULLET_H

#include "../main.h"
#include "Screen.h"
#include "Position.h"

#define BULLET_MOVE 8

typedef enum {
	SIMPLE,
	SPECIAL_1,
	SPECIAL_2,
} BULLET_TYPE;

typedef struct bullet {
	int x;
	int y;
	ALLEGRO_BITMAP* sprite;
	unsigned char trajectory;
	
	BULLET_TYPE bulletType;

	struct bullet *next;
} BULLET;

/*
	trajectory:
	0: para direita
	1: para esquerda
	2: para baixo
	3: para cima
*/

BULLET* createBulletNode(int x, int y, unsigned char trajectory);

void insertIntoBulletList(BULLET** head, int x, int y, unsigned char trajectory);

void drawBullet(BULLET* bullet);

void removeFromBulletList(BULLET** head, BULLET* bullet);

/*
	Checa se houve colisão com as balas e retorna a quantidade de dano causado
*/
int checkCollisionFromBullet(BULLET** head, int x, int y, int side);

void updateScreenForBullet(BULLET** head, SCREEN* sc);

void destroyBulletList(BULLET* head);

#endif
