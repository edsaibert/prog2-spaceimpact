#include "Level.h"

LEVEL* beginGame(SPACESHIP* sp, ENEMIES* enemies, SCREEN* sc, ITEM* items, BACKGROUND* bg){
	LEVEL* game = (LEVEL*) malloc(sizeof(LEVEL));

    if (!game) return NULL;

    game->currentLevel = BEGIN_FIRST;
    game->sp = sp;
    game->enemies = enemies;
    game->sc = sc;
    game->items = items;
    game->bg = bg;
    game->animation = 30 * 10;

    return game;
}

void showText(LEVEL* game, ALLEGRO_TIMER* timer, ALLEGRO_FONT* font, int* y, LEVEL_ID nextLevel, const char* text){
	if (game->animation == 0){	

        game->currentLevel = nextLevel;
		game->animation = 30 * 10;
		*y = game->sc->max_y + 10;

		return;
	}

    char* buffer = strdup(text);
    char* line = strtok(buffer, "\n");
    int line_height = al_get_font_line_height(font);
    int newY = *y; 

    while (line) {
        al_draw_text(font, al_map_rgb(255, 255, 255), game->sc->max_x / 2, newY, ALLEGRO_ALIGN_CENTER, line);
        newY += line_height + 5;
        line = strtok(NULL, "\n");
    }
    if (*y <= (game->sc->max_y - 150)/2) {
		game->animation--;
	}
	else (*y)--;

    free(buffer);

	// al_draw_text(font, al_map_rgb(255, 255, 255), game->sc->max_x / 2, *y, ALLEGRO_ALIGN_CENTER, text);
}

int loadLevel(LEVEL* game, ALLEGRO_TIMER* timer, ALLEGRO_FONT* font, SPACESHIP* enemyCollision, int *thunder){
   
	if (game->currentLevel == FIRST || game->currentLevel == LAST){
		addEnemy(&(game->enemies), game->sc, timer, game->currentLevel);
	}
	addItem(&(game->items), game->sc, timer);

	// Verifica colisão com inimigos e atualiza a posição dos inimigos
	enemyCollision = checkCollisionFromEnemies(game->enemies, game->sp->x, game->sp->y, game->sp->side);
	checkCollisionFromItem(&(game->items), game->sp);
	updateSpaceshipPosition(game->sp, enemyCollision, game->sc, moveSpaceship, compareFunctionPlayer);

	enemiesShoot(game->enemies, game->sc);
	shootSpaceship(game->sp);

	if (game->sp->gun->isLightning) *thunder = 30 * 3;

	if (al_get_timer_count(timer)/30 == 15){
	}

	hitPlayer(&(game->enemies), game->sp, game->sc);

	updateScreenForBullet(&(game->sp->gun->shots), game->sc);	
	updateScreenForBackground(game->bg);
	updateScreenForEnemies(&(game->enemies), game->sp, game->sc);

	drawBackground(game->bg, game->sc);
	drawItem(game->items);
	drawSpaceship(game->sp);
	drawEnemies(game->enemies);
	drawEnemyBullets(game->enemies);
	drawBullet(game->sp->gun->shots);
	drawHealthShieldAndScore(game->sp, game->sc, font);	

    if (game->currentLevel == FIRST && game->sp->score >= 100){
        //game->currentLevel = LAST;
		game->currentLevel = FIRST_BOSS;
	}

	if (game->currentLevel == LAST && game->sp->score >= 280){
		game->currentLevel = LAST_BOSS;
	}

    return 1;
}

void loadBoss(LEVEL* game, BOSS** boss, ALLEGRO_TIMER* timer, ALLEGRO_FONT* font, SPACESHIP* enemyCollision, int *thunder){
	if (checkCollision(game->sp->x, game->sp->y, (*boss)->sp->x, (*boss)->sp->y, game->sp->side, (*boss)->sp->side)){
		enemyCollision = (*boss)->sp;
	}

	// updateSpaceshipPosition(game->sp, enemyCollision, game->sc, moveSpaceship, compareFunctionPlayer);	
	updateScreenForBoss(boss, timer,game->sp, game->sc);	

	hitPlayerBoss(boss, game->sp, game->sc);

	drawBossHealth((*boss)->sp, game->sc, font, "");
	bossShoot(game->currentLevel, (*boss), game->sc);

	updateScreenForBullet(&((*boss)->sp->gun->shots), game->sc);
	drawBullet((*boss)->sp->gun->shots);
	drawSpaceship((*boss)->sp);

	if (checkIfSpaceshipIsDead((*boss)->sp)){
		if (game->currentLevel == FIRST_BOSS) {
			game->currentLevel = END_FIRST_BOSS;
			changeBackground(game->bg, "./sprites/background/last/foreground.png", "./sprites/background/last/background.png", "./sprites/background/last/middleground.png");
		}
		else if (game->currentLevel == LAST_BOSS) game->currentLevel = END_LAST_BOSS;
		destroyBoss(*boss);
	}
	
}

