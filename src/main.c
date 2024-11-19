#include "../main.h"
#include "Spaceship.h"
#include "Joystick.h"
#include "Screen.h"
#include "Position.h"
#include "Enemy.h"

int main(void){
    al_init();
    al_install_keyboard();

	srand(time(NULL));

	al_init_primitives_addon();
	al_init_image_addon();

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();

	SCREEN* sc = createScreen(500, 300);
	if (!sc) return 1;

    ALLEGRO_DISPLAY* disp = al_create_display(sc->max_x, sc->max_y);

    al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
    ALLEGRO_FONT* font = al_create_builtin_font();

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    al_start_timer(timer);
    ALLEGRO_EVENT e;

	const char* sprite = "./sprites/spaceships/player/ship_1/";

	SPACESHIP* sp = createSpaceship(20, 20, 0, sprite);
	if (!sp) return 1;

	SPACESHIP* enemy = createSpaceship(100, 50, 1, sprite);
	SPACESHIP* collision;
	ENEMIES* enemies = createEnemyList(sc);

    while(1){
        al_wait_for_event(queue, &e);

		// Caso o evento seja de relógio
		if (e.type == 30){
			collision = checkCollisionFromEnemies(enemies, sp->x, sp->y, sp->side);			
			if (collision) printf("collision with enemy\n");
			
			//printf("colisao: %d", checkCollision(sp->x, sp->y, enemy->x, enemy->y, sp->side, enemy->side));
			updateSpaceshipPosition(sp, collision, sc, moveSpaceship);	
			al_clear_to_color(al_map_rgb(255, 255, 255));
			drawSpaceship(sp);
			drawSpaceship(enemy);
			drawEnemies(enemies);
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
		}
    }

	destroyScreen(sc);

    al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    return 0;

}
