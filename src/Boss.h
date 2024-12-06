#include "../main.h"
#include "Position.h"
#include "Enemy.h"

typedef struct boss {
    SPACESHIP* sp;
    int originX;
    int originY;
    MOVEMENT_PATTERN movement_pattern;
    LEVEL_ID currentLevel;

} BOSS;

BOSS* addBoss(int x, int y, int side, int health, MOVEMENT_PATTERN movement_pattern, LEVEL_ID currentLevel, const char* path, SCREEN* sc);

void updateScreenForBoss(BOSS** boss, SPACESHIP* sp, SCREEN* sc);

void doRoutineBoss(BOSS* boss);

