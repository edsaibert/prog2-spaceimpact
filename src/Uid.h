#ifndef UID_H
#define UID_H

#include "../main.h"
#include "Spaceship.h"

void drawHealthShieldAndScore(SPACESHIP* sp, SCREEN* sc, ALLEGRO_FONT* font);

void drawBossHealth(SPACESHIP* sp, SCREEN* sc, ALLEGRO_FONT* font, const char* bossName);

void bossText(SCREEN* sc, LEVEL_ID currentLevel, ALLEGRO_FONT* font, int* timer, ALLEGRO_BITMAP* profile);

void playerText(SCREEN* sc, LEVEL_ID currentLevel, ALLEGRO_FONT* font, int* timer, ALLEGRO_BITMAP* profile);

#endif