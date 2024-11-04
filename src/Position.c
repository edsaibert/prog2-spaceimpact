#include "Position.h"


float* normalizedDistance(int x1, int y1, int x2, int y2){
	/*
		d significa o vetor normalizado entre o objeto 1 e objeto 2
		d[0] : eixo x
		d[1] : eixo y
		d[2] : a distância euclidiana entre o objeto 1 e 2
	*/

	float* d = (float*) malloc(2*sizeof(float));
	if (!d) return NULL;

	int distance_x = x2 - x1;
	int distance_y = y2 - y1;

	float squaredDistance = (float) (distance_x * distance_x + distance_y * distance_y);

	if (squaredDistance != 0){
		d[0] = distance_x / squaredDistance;
		d[1] = distance_y / squaredDistance;
		printf("d[0]: %f, d[1]: %f\n", d[0], d[1]);
	//d[2] = squaredDistance;
	}
	else {
		d[0] = 0;
		d[1] = 0;
		//d[2] = squaredDistance;
	}
	
	return d;
}

// Checa a colisão entre objetos utilizando a função da circunferência e distância euclidiana
short int checkCollision(int euclidianDistance, int side1, int side2){
	if (euclidianDistance <= ((side1/2) + (side2/2))) 
		return 1;
	return 0;
}

void updateSpaceshipPosition(SPACESHIP* sp, SPACESHIP* enemy, SCREEN* sc, void (*positionFunction) (SPACESHIP*, int, unsigned char, SCREEN*)){
	int collision = 0;
	float* d = NULL;

	if (enemy){
		d = normalizedDistance(sp->x, sp->y, enemy->x, enemy->y);	
		//collision = checkCollision(d[2], sp->side, enemy->side);
	}

	printf("x: %f, y: %f\n", d[0], d[1]);

	if (sp->control->left){
		if (d[0] < 0)
			positionFunction(sp, 1, 0, sc);
	}
	if (sp->control->right){
		if (d[0] > 0)
			positionFunction(sp, 1, 1, sc);
	}
	if (sp->control->up){
		if (d[1] < 0)
			positionFunction(sp, 1, 2, sc);
	}
	if (sp->control->down){
		if (d[1] > 0)
			positionFunction(sp, 1, 3, sc);
	}
}
