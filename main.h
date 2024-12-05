#ifndef MAIN_H
#define MAIN_H

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_color.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define FPS 1.0/30.0
#define EPSILON 1/(SPACESHIP_SIDE + SPACESHIP_STEP)

typedef enum {
    FIRST,
    FIRST_BOSS,
    LAST,
    LAST_BOSS
} LEVEL_ID;

typedef enum {
	LINEAR,
	UP_DOWN,
	FOLLOW_X,
	DOWN,
	FOLLOW_ALL,
	DODGE,
	SPECIAL_ATTACK
} MOVEMENT_PATTERN;


#endif
