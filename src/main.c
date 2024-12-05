#include "../main.h"
#include "Spaceship.h"
#include "Joystick.h"
#include "Screen.h"
#include "Position.h"
#include "Enemy.h"
#include "Background.h"
#include "Item.h"
#include "Uid.h"
#include "Level.h"

int main(void){
    al_init();
    al_install_keyboard();

	srand(time(NULL));

	al_init_primitives_addon();
	al_init_image_addon();
	al_init_font_addon();

    ALLEGRO_TIMER* timer = al_create_timer(FPS);
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();

	SCREEN* sc = createScreen(800, 400);

    ALLEGRO_DISPLAY* disp = al_create_display(sc->max_x, sc->max_y);

    al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
    ALLEGRO_FONT* font = al_create_builtin_font();

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    al_start_timer(timer);
    ALLEGRO_EVENT e;

	const char* sprite = "./sprites/spaceships/player/ship_1/";

	SPACESHIP* sp = createSpaceship(20, 20, 0, 20, 50, sprite);
	if (!sp) return 1;

	BACKGROUND* bg = createBackground("./sprites/background/first/foreground.png", "./sprites/background/first/background.png", NULL, sc->max_x, sc->max_y);
	BACKGROUND* bg_end = createBackground("./sprites/background/end/text.png", "./sprites/background/end/end.png", "./sprites/background/end/planet.png", sc->max_x, sc->max_y);

	SPACESHIP* enemyCollision = NULL;
	ENEMIES* enemies = createEnemyList(sc); 
	ITEM* items = NULL;

	LEVEL* game = beginGame(sp, enemies, sc, items, bg);

	int thunder = 0;

	int end = 0;
		
	while(1){
        al_wait_for_event(queue, &e);

		// Caso o evento seja de relógio
		if (e.type == 30){
			al_clear_to_color(al_map_rgb(0, 0, 0));

			if (!checkIfSpaceshipIsDead(sp)){

				if (thunder){
					if (thunder % 10 < 5)
						drawBackground(bg, sc);
					else
						al_draw_filled_rectangle(0, 0, sc->max_x, sc->max_y, al_map_rgb(255, 255, 255));

					thunder -= 1;

					continue;
				}

				loadLevel(game, timer, font, enemyCollision, &thunder);

			}
			else {
				updateScreenForBackground(bg_end);
				drawBackground(bg_end, sc);	
				end = 1;
			}


			al_flip_display();
		}

		
	
		// Verifica eventos do teclado
		else if ((e.type == 10) || (e.type == 12)){
			// Tecla 'A'
			if (e.keyboard.keycode == 1) updateJoystickLeft(sp->control);	
			// Tecla 'D'
			else if (e.keyboard.keycode == 4) updateJoystickRight(sp->control);
			// Tecla 'W'
			else if (e.keyboard.keycode == 23) updateJoystickUp(sp->control);
			// Tecla 'S'
			else if (e.keyboard.keycode == 19) updateJoystickDown(sp->control);

			else if (e.keyboard.keycode == ALLEGRO_KEY_SPACE) updateJoystickShoot(sp->control);
	
			else if (e.keyboard.keycode == ALLEGRO_KEY_ENTER) if (end) break;

		}

	}

	destroyScreen(sc);
	destroySpaceship(sp);
	destroyEnemyList(enemies);
	destroyBackground(bg);
	destroyBackground(bg_end);

    al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    return 0;

}
