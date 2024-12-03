#include "Background.h"

BACKGROUND* createBackground(const char* foreground, const char* background, const char* middleground, int width, int height){
	BACKGROUND* bg = (BACKGROUND*) malloc(sizeof(BACKGROUND));

	if (!bg) return NULL;

	bg->x = 0;
	bg->y = 0;
	bg->width = width;
	bg->height = height;	
	
	if (foreground) bg->foreground = al_load_bitmap(foreground);
	else bg->foreground = NULL;

	if (background) bg->background = al_load_bitmap(background);
	else bg->background = NULL;

	if (middleground) bg->middleground = al_load_bitmap(middleground);
	else bg->middleground = NULL;

	return bg;
}

void changeBackground(BACKGROUND* prev, const char* foreground, const char* background, const char* middleground){
	al_destroy_bitmap(prev->foreground);
	al_destroy_bitmap(prev->background);
	al_destroy_bitmap(prev->middleground);
	
	if (foreground) prev->foreground = al_load_bitmap(foreground);
	else prev->foreground = NULL;

	if (background) prev->background = al_load_bitmap(background);
	else prev->background = NULL;

	if (middleground) prev->middleground = al_load_bitmap(middleground);
	else prev->middleground = NULL;
	
}

void updateScreenForBackground(BACKGROUND* bg){
	bg->x = bg->x + PARALLAX_SPEED;
}

void drawBackground(BACKGROUND* bg, SCREEN* sc){
	if (!bg) return;
	
	if (bg->background){
		float offset = fmod(bg->x, bg->width);
		float part1_width = bg->width - offset;

		al_draw_bitmap_region(bg->background, offset, 0, part1_width, bg->height, 0, 0, 0);

		if (bg->width > part1_width) {
			float part2_width = bg->width - part1_width;

			al_draw_bitmap_region(bg->background, 0, 0, part2_width, bg->height, part1_width, 0, 0);
		}
	}

	if (bg->foreground){
		al_draw_bitmap(bg->foreground, 0, 0, 0);	
	}
}

void destroyBackground(BACKGROUND* bg){
	al_destroy_bitmap(bg->foreground);
	al_destroy_bitmap(bg->background);
	al_destroy_bitmap(bg->middleground);
	free(bg);
}
