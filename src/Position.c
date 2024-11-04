#include "Position.h"


int* normalizedDistance(int x1, int y2, int x2, int y2){
	/*
		d significa o vetor normalizado entre o objeto 1 e objeto 2
		d[0] : eixo x
		d[1] : eixo y
		d[2] : a distância euclidiana entre o objeto 1 e 2
	*/

	int* d = (int*) malloc(3*sizeof(int));
	if (!d) return NULL;

	int distance_x = x2-x1;
	int distance_y = y1-y1;

	int squaredDistance = distance_x*distance_x + distance_y*distance_y;

	if (!squaredDistance){
		d[0] = distance_x / squaredDistance;
		d[1] = distance_y / squaredDistance;
		d[2] = squaredDistance;
	}
	else {
		d[0] = 0;
		d[1] = 0;
		d[2] = squaredDistance;
	}
	
	return d;
}

// Checa a colisão entre objetos utilizando a função da circunferência e distância euclidiana
short int checkCollision(int euclidianDistance, int side1, int side2){
	if (euclidianDistance <= ((side1/2) + (side2/2))) 
		return 1;
	return 0;
}

void updateSpaceshipPosition(SPACESHIP* sp, SCREEN* sc, void (*positionFunction) (SPACESHIP*, int, unsigned char, SCREEN*)){
	if (sp->control->left){
		positionFunction(sp, 1, 0, sc);
	}
	if (sp->control->right){
		positionFunction(sp, 1, 1, sc);
	}
	if (sp->control->up){
		positionFunction(sp, 1, 2, sc);
	}
	if (sp->control->down){
		positionFunction(sp, 1, 3, sc);
	}
}
