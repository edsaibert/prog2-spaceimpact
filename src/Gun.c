#include "Gun.h"

GUN* createGun(){
	GUN* gun = (GUN*) malloc(sizeof(GUN));
		
	if (!gun) return NULL;

	gun->shots = NULL;	// Inicializado em NULL
	gun->timer = 0;
	gun->specialAttack = 0;
	
	return gun;
}

BULLET* shotGun (int x, int y, unsigned char trajectory, GUN* gun) {
	if (!gun) return NULL;

	if (gun->timer > 0){
		gun->timer -= 1;
		return NULL;
	}

	if (gun->specialAttack){
		insertIntoBulletList(&(gun->shots), x, y, trajectory, SPECIAL);
		gun->specialAttack -= 1;
	}
	else 
		insertIntoBulletList(&(gun->shots), x, y, trajectory, SIMPLE);

	gun->timer = PISTOL_COOLDOWN;	

	return gun->shots;
}


void destroyGun(GUN* gun){
	if (!gun) return;

	if (gun->shots)
		destroyBulletList(gun->shots);
	free(gun);
}



