#ifndef SPRITE_H
#define SPRITE_H

#include "../main.h"

typedef struct sprite SPRITE;
struct sprite {
	ALLEGRO_BITMAP* active;				// sprite ativo no momento

	ALLEGRO_BITMAP* front;				// number 0
	ALLEGRO_BITMAP* left;				// number 1
	ALLEGRO_BITMAP* right;				// number 2
	ALLEGRO_BITMAP* diagonalLeft;		// number 3
	ALLEGRO_BITMAP* diagonalRight;		// number 4
};

/*
struct specialSprite {
	ALLEGRO_BITMAP* active;

	ALLEGRO_BITMAP** spriteList;
}
*/

SPRITE* createSprite(const char* basePath);

void changeActiveSprite(SPRITE* sprite, int number);

void destroySprite(SPRITE* sprite);

#endif

