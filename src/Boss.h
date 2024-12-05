#include "../main.h"
#include "Position.h"
#include "Enemy.h"

void addBoss(ENEMIES** head, int x, int y, int side, int health, MOVEMENT_PATTERN movement_pattern, const char* path);

void updateScreenForBoss(ENEMIES** head, SPACESHIP* sp, SCREEN* sc);

void doRoutineBoss(ENEMIES* head);

