#include "Level.h"

LEVEL* beginGame(SPACESHIP* sp, ENEMIES* enemies, SCREEN* sc, ITEM* items, BACKGROUND* bg){
	LEVEL* game = (LEVEL*) malloc(sizeof(LEVEL));

    if (!game) return NULL;

    game->currentLevel = FIRST;
    game->sp = sp;
    game->enemies = enemies;
    game->sc = sc;
    game->items = items;
    game->bg = bg;
    game->animation = 30 * 5;

    return game;
}

int loadLevel(LEVEL* game, ALLEGRO_TIMER* timer, ALLEGRO_FONT* font, SPACESHIP* enemyCollision, int *thunder){
   
	if (game->currentLevel == FIRST || game->currentLevel == LAST){
		addEnemy(&(game->enemies), game->sc, timer, game->currentLevel);
		updateSpaceshipPosition(game->sp, enemyCollision, game->sc, moveSpaceship, compareFunctionPlayer);	
	}
	addItem(&(game->items), game->sc, timer);

	// Verifica colisão com inimigos e atualiza a posição dos inimigos
	enemyCollision = checkCollisionFromEnemies(game->enemies, game->sp->x, game->sp->y, game->sp->side);
	checkCollisionFromItem(&(game->items), game->sp);

	enemiesShoot(game->enemies, game->sc);
	shootSpaceship(game->sp);

	if (game->sp->gun->isLightning) *thunder = 30 * 3;

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

    if (game->currentLevel == FIRST && game->sp->score >= 10){
        //changeBackground(game->bg, "./sprites/background/last/foreground.png", "./sprites/background/last/background.png", "./sprites/background/last/middleground.png");
        //game->currentLevel = LAST;
		game->currentLevel = FIRST_BOSS;
	}

    return 1;
}

void loadFirstBoss(LEVEL* game, BOSS** boss, ALLEGRO_TIMER* timer, ALLEGRO_FONT* font, SPACESHIP* enemyCollision, int *thunder){
	// if (checkCollision(game->sp->x, game->sp->y, (*boss)->sp->x, (*boss)->sp->y, game->sp->side, (*boss)->sp->side)){
	// 	enemyCollision = (*boss)->sp;
	// 	game->sp->health -= 1;
	// }
	updateSpaceshipPosition(game->sp, enemyCollision, game->sc, moveSpaceship, compareFunctionPlayer);	
	updateScreenForBoss(boss, timer,game->sp, game->sc);	

	hitPlayerBoss(boss, game->sp, game->sc);

	drawBossHealth((*boss)->sp, game->sc, font, "");
	drawSpaceship((*boss)->sp);

	if (checkIfSpaceshipIsDead((*boss)->sp)){
		game->currentLevel = LAST;
	}
}
