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
	BEGIN_FIRST,
    FIRST,
    FIRST_BOSS,
	END_FIRST_BOSS,
    LAST,
    LAST_BOSS,
	END_LAST_BOSS
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
