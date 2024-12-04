#include "Uid.h"

void drawHealthShieldAndScore(SPACESHIP* sp, SCREEN* sc, ALLEGRO_FONT* font){
    // Vida 
    al_draw_filled_rounded_rectangle(9, 9, 111, 21, 5, 5, al_map_rgb(255, 255, 255));
    al_draw_filled_rounded_rectangle(10, 10, 5*sp->health + 10, 20, 5, 5, al_map_rgb(105, 22, 25));

    // Shield
    al_draw_filled_rounded_rectangle(9, 29, 61, 41, 5, 5, al_map_rgb(255, 255, 255));
    if (sp->shield)
        al_draw_filled_rounded_rectangle(10, 30, 5*sp->shield + 10, 40, 5, 5, al_map_rgb(80, 111, 161));

    // Score
    char text[50]; 
    snprintf(text, sizeof(text), "Score: %d", sp->score);
    al_draw_text(font, al_map_rgb(255, 255, 255), 10, 50, 0, text);
}