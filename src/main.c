#include "../main.h"
#include "Spaceship.h"

int main(void){
    al_init();
    al_install_keyboard();

	al_init_primitives_addon();

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();

    ALLEGRO_DISPLAY* disp = al_create_display(500, 300);

    al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
    ALLEGRO_FONT* font = al_create_builtin_font();

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    al_start_timer(timer);
    ALLEGRO_EVENT event;

	SPACESHIP* sp = createSpaceship(50, 50);

    while(1){
        al_wait_for_event(queue, &event);
        al_clear_to_color(al_map_rgb(255, 255, 255));

		updateSpaceshipPos(sp, 5, 1);
		drawSpaceship(sp);
    }

    al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    return 0;

}
