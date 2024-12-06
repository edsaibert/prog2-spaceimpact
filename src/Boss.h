#include "../main.h"
#include "Position.h"
#include "Enemy.h"
#include "Gun.h"

typedef struct boss {
    SPACESHIP* sp;
    int originX;
    int originY;
    MOVEMENT_PATTERN movement_pattern;
    LEVEL_ID currentLevel;
    int lastSeconds;

} BOSS;

BOSS* addBoss(int x, int y, int side, int health, MOVEMENT_PATTERN movement_pattern, LEVEL_ID currentLevel, const char* path, SCREEN* sc);

void hitPlayerBoss(BOSS** boss, SPACESHIP* sp, SCREEN* sc);

void destroyBoss(BOSS* boss);

void bossShoot(LEVEL_ID level, BOSS* boss, SCREEN* sc);

void updateScreenForBoss(BOSS** boss, ALLEGRO_TIMER* timer, SPACESHIP* sp, SCREEN* sc);

void doRoutineBoss(BOSS* boss);

