#include "Sprite.h"


SPRITE* createSprite(const char* basePath) {
    SPRITE* sprite = (SPRITE*)malloc(sizeof(SPRITE));
    if (!sprite) return NULL;

    char fullPath[256];

    snprintf(fullPath, sizeof(fullPath), "%sfront.png", basePath);
    sprite->front = al_load_bitmap(fullPath);

    snprintf(fullPath, sizeof(fullPath), "%sleft.png", basePath);
    sprite->left = al_load_bitmap(fullPath);

    snprintf(fullPath, sizeof(fullPath), "%sright.png", basePath);
    sprite->right = al_load_bitmap(fullPath);

    snprintf(fullPath, sizeof(fullPath), "%sleft_left.png", basePath);
    sprite->diagonalLeft = al_load_bitmap(fullPath);

    snprintf(fullPath, sizeof(fullPath), "%sright_right.png", basePath);
    sprite->diagonalRight = al_load_bitmap(fullPath);

    sprite->active = sprite->front;

    return sprite;
}

void changeActiveSprite(SPRITE* sprite, int number){
	if (number == 0) sprite->active = sprite->front;
	else if (number == 1) sprite->active = sprite->left;
	else if (number == 2) sprite->active = sprite->right;
	else if (number == 3) sprite->active = sprite->diagonalLeft;
	else if (number == 4) sprite->active = sprite->diagonalRight;
}

void destroySprite(SPRITE* sprite){
	al_destroy_bitmap(sprite->front);
	al_destroy_bitmap(sprite->left);
	al_destroy_bitmap(sprite->right);
	al_destroy_bitmap(sprite->diagonalLeft);
	al_destroy_bitmap(sprite->diagonalRight);

	sprite->active = NULL;
	sprite->front = NULL;
	sprite->left = NULL;
	sprite->right = NULL;
	sprite->diagonalLeft = NULL;
	sprite->diagonalRight = NULL;

	free(sprite);
}
