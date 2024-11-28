#include "Gun.h"

GUN* createGun(){
	GUN* gun = (GUN*) malloc(sizeof(GUN));
		
	if (!gun) return NULL;

	gun->shots = NULL;	// Inicializado em NULL
	gun->timer = 0;
	
	return gun;
}

BULLET* shotGun (int x, int y, unsigned char trajectory, GUN* gun) {
	if (!gun) return NULL;

	if (gun->timer > 0){
		gun->timer -= 1;
		return NULL;
	}

	insertIntoBulletList(&(gun->shots), x, y, trajectory);
	gun->timer = PISTOL_COOLDOWN;	

	return gun->shots;
}


void destroyGun(GUN* gun){
	if (!gun) return;

	if (gun->shots)
		destroyBulletList(gun->shots);
	free(gun);
}



