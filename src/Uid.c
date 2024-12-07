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

void drawBossHealth(SPACESHIP* sp, SCREEN* sc, ALLEGRO_FONT* font, const char* bossName){
    al_draw_filled_rounded_rectangle(sc->max_x - 400 - 10, 9, sc->max_x -9, 21, 5, 5, al_map_rgb(255, 255, 255));
    al_draw_filled_rounded_rectangle(sc->max_x - (5*sp->health) - 9, 10, sc->max_x - 10, 20, 5, 5, al_map_rgb(105, 22, 25));
}

void playerText(SCREEN* sc, LEVEL_ID currentLevel, ALLEGRO_FONT* font, int* timer, ALLEGRO_BITMAP* profile) {
    (*timer)--;
    if (*timer <= 0) return;

    int left = 10, right = 310; 
    int top = sc->max_y - 100, bottom = sc->max_y - 10;

    al_draw_filled_rounded_rectangle(left - 2, top - 2, right + 2, bottom + 2, 7, 7, al_map_rgb(155, 215, 232));
    al_draw_filled_rounded_rectangle(left, top, right, bottom, 7, 7, al_map_rgb(25, 37, 54));

    int portraitSize = 90; 
    int portraitX = right + 10; 
    int portraitY = top + (bottom - top - portraitSize) / 2; 

    al_draw_scaled_bitmap(
        profile,
        0, 0,                               
        al_get_bitmap_width(profile),      
        al_get_bitmap_height(profile),      
        portraitX, portraitY,              
        portraitSize, portraitSize,       
        0
    );

    const char* playerMessage = "Amarelo...";
    int textX = (left + right) / 2; 
    int textY = top + 35;         
    al_draw_text(font, al_map_rgb(255, 255, 255), textX, textY, ALLEGRO_ALIGN_CENTER, playerMessage);
}

void bossText(SCREEN* sc, LEVEL_ID currentLevel, ALLEGRO_FONT* font, int* timer, ALLEGRO_BITMAP* profile) {
    (*timer)--;
    if (*timer <= 0) return;

    int left = sc->max_x - 310, right = sc->max_x - 10;
    int top = sc->max_y - 100, bottom = sc->max_y - 10;

    al_draw_filled_rounded_rectangle(left - 2, top - 2, right + 2, bottom + 2, 7, 7, al_map_rgb(155, 215, 232));
    al_draw_filled_rounded_rectangle(left, top, right, bottom, 7, 7, al_map_rgb(25, 37, 54));

    int portraitSize = 90; 
    int portraitX = left - portraitSize - 10; 
    int portraitY = top + (bottom - top - portraitSize) / 2; 

    al_draw_scaled_bitmap(
        profile,
        0, 0,                             
        al_get_bitmap_width(profile),   
        al_get_bitmap_height(profile),   
        portraitX, portraitY,           
        portraitSize, portraitSize,    
        0                             
    );

    const char* bossMessage;
    if (currentLevel == FIRST_BOSS)
        bossMessage = "Rick, o que você está fazendo?!";

    else if (currentLevel == LAST_BOSS)
        bossMessage = "Por favor Rick, não faça isso!";

    int textX = (left + right) / 2;
    int textY = top + 35;         
    al_draw_text(font, al_map_rgb(255, 255, 255), textX, textY, ALLEGRO_ALIGN_CENTER, bossMessage);
}
