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
   
    addEnemy(&(game->enemies), game->sc, timer, game->currentLevel);
    addItem(&(game->items), game->sc, timer);

    updateSpaceshipPosition(game->sp, enemyCollision, game->sc, moveSpaceship, compareFunctionPlayer);	

    // Verifica colisão com inimigos e atualiza a posição dos inimigos
    enemyCollision = checkCollisionFromEnemies(game->enemies, game->sp->x, game->sp->y, game->sp->side);
    checkCollisionFromItem(&(game->items), game->sp);

    enemiesShoot(game->enemies, game->sc);
    shootSpaceship(game->sp);

    if (game->sp->gun->isLightning) *thunder = 30 * 3;

    hitPlayer(&(game->enemies), game->sp, game->sc);

    updateScreenForBullet(&(game->sp->gun->shots), game->sc);	
    updateScreenForEnemies(&(game->enemies), game->sp, game->sc);
    updateScreenForBackground(game->bg);

    drawBackground(game->bg, game->sc);
    drawItem(game->items);
    drawSpaceship(game->sp);
    drawEnemies(game->enemies);
    drawEnemyBullets(game->enemies);
    drawBullet(game->sp->gun->shots);
    drawHealthShieldAndScore(game->sp, game->sc, font);

    if (game->currentLevel == FIRST && game->sp->score >= 50){
        changeBackground(game->bg, "./sprites/background/last/foreground.png", "./sprites/background/last/background.png", NULL);
        game->currentLevel = LAST;
    }

    return 1;
}
