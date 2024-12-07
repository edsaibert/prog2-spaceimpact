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

int main(void)
{
	al_init();
	al_install_keyboard();

	srand(time(NULL));

	al_init_primitives_addon();
	al_init_image_addon();
	al_init_font_addon();

	ALLEGRO_TIMER *timer = al_create_timer(FPS);
	ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();

	SCREEN *sc = createScreen(800, 400);

	ALLEGRO_DISPLAY *disp = al_create_display(sc->max_x, sc->max_y);

	al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
	ALLEGRO_FONT *font = al_create_builtin_font();

	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_display_event_source(disp));
	al_register_event_source(queue, al_get_timer_event_source(timer));

	al_start_timer(timer);
	ALLEGRO_EVENT e;

	const char *sprite = "./sprites/spaceships/player/ship_1/";

	SPACESHIP *sp = createSpaceship(20, 20, 0, 20, 50, sprite);
	if (!sp)
		return 1;

	BACKGROUND *bg = createBackground("./sprites/background/first/foreground.png", "./sprites/background/first/background.png", NULL, sc->max_x, sc->max_y);
	BACKGROUND *bg_end = createBackground("./sprites/background/end/text.png", "./sprites/background/end/end.png", "./sprites/background/end/planet.png", sc->max_x, sc->max_y);

	SPACESHIP *enemyCollision = NULL;
	ENEMIES *enemies = createEnemyList(sc);
	ITEM *items = NULL;

	BOSS *firstBoss = addBoss(sc->max_x + 80 / 2, sc->max_y / 2, 80, 5, LINEAR, FIRST_BOSS, "./sprites/spaceships/enemy/boss-01/", sc);
	BOSS *lastBoss = addBoss(sc->max_x + 80 / 2, sc->max_y / 2, 80, 80, LINEAR, LAST_BOSS, "./sprites/spaceships/enemy/boss-02/", sc);

	LEVEL *game = beginGame(sp, enemies, sc, items, bg);

	int thunder = 0;

	// timer para o texto
	int textY = sc->max_y + 10;

	// timers para as falas do jogo
	int timerFirstLevel = 30 * 10;
	int timerFirstBoss = 30 * 10;
	int timerLastLevel = 30 * 10;
	int timerLastBoss = 30 * 10;

	// portraits dos personagens
	ALLEGRO_BITMAP *portrait_1 = al_load_bitmap("./sprites/others/portrait_1.png");
	ALLEGRO_BITMAP* portrait_2 = al_load_bitmap("./sprites/others/portrait_2.png");
	ALLEGRO_BITMAP* portrait_3 = al_load_bitmap("./sprites/others/portrait_3.png");
	ALLEGRO_BITMAP* portrait_4 = al_load_bitmap("./sprites/others/portrait_4.png");


	const char *beginText = "Fragmentos de mensagens codificadas, \nsinais incomuns, \ne breves visões o convenceram de uma terrível verdade: \nos inimigos finalmente encontraram uma forma de infiltrar a frota.\n Estão disfarçados, escondidos entre seus aliados, \naguardando o momento certo para atacar. \nAgora, em sua nave de combate, \nvocê voa sozinho pelas estrelas,\n determinado a eliminar a ameaça antes que seja tarde demais.\n Um a um, antigos camaradas caem sob seu fogo incansável.\n Para você, eles não são mais humanos —\n são impostores que precisam ser destruídos a qualquer custo.\n No entanto, o vazio do espaço esconde segredos perigosos,\n e a linha entre inimigo e aliado se torna cada vez mais tênue.\n Você é a última esperança contra uma invasão iminente...\n ou algo muito mais sombrio?";

	int end = 0;

	while (1)
	{
		al_wait_for_event(queue, &e);

		// Caso o evento seja de relógio
		if (e.type == 30)
		{
			al_clear_to_color(al_map_rgb(0, 0, 0));
			printf("currentLevel: %d\n", game->currentLevel);

			if (!checkIfSpaceshipIsDead(sp) &&
				(game->currentLevel == FIRST ||
				 game->currentLevel == LAST ||
				 game->currentLevel == FIRST_BOSS ||
				 game->currentLevel == LAST_BOSS))
			{

				if (thunder)
				{
					if (thunder % 10 < 5)
						drawBackground(bg, sc);
					else
						al_draw_filled_rectangle(0, 0, sc->max_x, sc->max_y, al_map_rgb(255, 255, 255));

					thunder -= 1;

					continue;
				}

				loadLevel(game, timer, font, enemyCollision, &thunder);

				if (game->currentLevel == FIRST && al_get_timer_count(timer)/30 > 25)
				{
					playerText(sc, game->currentLevel, font, &timerFirstLevel, portrait_3);
				}
    
				if (game->currentLevel == FIRST_BOSS){
					bossText(sc, game->currentLevel, font, &timerFirstBoss, portrait_2);
				}

				if (game->currentLevel == LAST_BOSS){
					bossText(sc, game->currentLevel, font, &timerLastBoss, portrait_2);
				}	

				if (game->currentLevel == FIRST_BOSS && countEnemies(game->enemies) == 0)
				{
					loadBoss(game, &firstBoss, timer, font, enemyCollision, &thunder);
				}

				if (game->currentLevel == LAST_BOSS && countEnemies(game->enemies) == 0)
				{
					loadBoss(game, &lastBoss, timer, font, enemyCollision, &thunder);
				}
			}
			else if (game->currentLevel == BEGIN_FIRST)
			{
				showText(game, timer, font, &textY, FIRST, beginText);
			}
			else if (game->currentLevel == END_FIRST_BOSS)
			{
				showText(game, timer, font, &textY, LAST, "Cada transmissão é uma ameaça. \nCada nave, um inimigo em potencial.\nVocê precisa agir. \nPrecisa acabar com todos eles antes que eles acabem com você.");
			}
			else
			{
				updateScreenForBackground(bg_end);
				drawBackground(bg_end, sc);
				end = 1;
			}

			al_flip_display();
		}

		// Verifica eventos do teclado
		else if ((e.type == 10) || (e.type == 12))
		{
			// Tecla 'A'
			if (e.keyboard.keycode == 1)
				updateJoystickLeft(sp->control);
			// Tecla 'D'
			else if (e.keyboard.keycode == 4)
				updateJoystickRight(sp->control);
			// Tecla 'W'
			else if (e.keyboard.keycode == 23)
				updateJoystickUp(sp->control);
			// Tecla 'S'
			else if (e.keyboard.keycode == 19)
				updateJoystickDown(sp->control);

			else if (e.keyboard.keycode == ALLEGRO_KEY_SPACE)
				updateJoystickShoot(sp->control);

			else if (e.keyboard.keycode == ALLEGRO_KEY_ENTER)
				if (end)
					break;
		}
	}

	destroyScreen(sc);
	destroySpaceship(sp);
	destroyEnemyList(enemies);
	destroyBackground(bg);
	destroyBackground(bg_end);
	// destroyBoss(firstBoss);
	// destroyBoss(lastBoss);

	al_destroy_bitmap(portrait_1);
	al_destroy_bitmap(portrait_2);
	al_destroy_bitmap(portrait_3);
	al_destroy_bitmap(portrait_4);
	al_destroy_font(font);
	al_destroy_display(disp);
	al_destroy_timer(timer);
	al_destroy_event_queue(queue);

	return 0;
}
