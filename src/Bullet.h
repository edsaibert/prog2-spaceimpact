#ifndef BULLET_H
#define BULLET_H

#include "../main.h"

#define BULLET_MOVE 5

typedef struct bullet {
	int x;
	int y;
	unsigned char trajectory;
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

void removeFromBulletList(BULLET** head, BULLET* bullet);

void updateScreenForBullet(BULLET* head);

void destroyBulletList(BULLET* head);

#endif
