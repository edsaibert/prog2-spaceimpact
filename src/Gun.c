#include "Gun.h"

GUN* createGun(){
	GUN* gun = (GUN*) malloc(sizeof(GUN));
		
	if (!gun) return NULL;

	gun->shots = NULL;	// Inicializado em NULL
	gun->timer = 0;
	gun->specialAttack = 0;
	gun->isLightning = 0;
	gun->specialMinor = 0;
	gun->specialMajor = 0;
	
	return gun;
}

void shotGunBoss(LEVEL_ID level, int x, int y, unsigned char trajectory, GUN* gun){
	if (!gun) return;

	if (gun->timer > 0){
		gun->timer -= 1;
		return;
	}

	if (level == FIRST_BOSS){
		if (gun->specialMinor){
			insertIntoBulletList(&(gun->shots), x, y, trajectory, SPECIAL_MINOR_FIRST);
		}
		else if (gun->specialMajor){
			insertIntoBulletList(&(gun->shots), x, y, trajectory, SPECIAL_MAJOR_FIRST);
		}
		else {
			insertIntoBulletList(&(gun->shots), x, y, trajectory, SIMPLE);
		}
	}
	else if (level == LAST_BOSS){
		if (gun->specialMinor){
			insertIntoBulletList(&(gun->shots), x, y, trajectory, SPECIAL_MINOR_LAST);
			gun->specialMinor--;
		}
		else if (gun->specialMajor){
			insertIntoBulletList(&(gun->shots), x, y, trajectory, SPECIAL_MAJOR_LAST);
			gun->specialMajor--;
		}
		else {
			insertIntoBulletList(&(gun->shots), x, y, trajectory, SIMPLE);
		}
	}
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
	else if (gun->isLightning){
		insertIntoBulletList(&(gun->shots), x, y, trajectory, THUNDER);
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



