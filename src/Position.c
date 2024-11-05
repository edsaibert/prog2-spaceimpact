#include "Position.h"


float* normalizedDistance(int x1, int y1, int x2, int y2){
	/*
		d significa o vetor normalizado entre o objeto 1 e objeto 2
		d[0] : eixo x
		d[1] : eixo y
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
	}
	else {
		d[0] = 0;
		d[1] = 0;
	}
	
	return d;
}

// Checa a colisão entre objetos utilizando a função da circunferência e distância euclidiana
short int checkCollision(int x1, int y1, int x2, int y2, int side1, int side2){
	int euclidianDistance = (x2-x1)*(x2-x1) + (y2-y1)*(y2-y1);
	euclidianDistance = sqrt(euclidianDistance);

	if (euclidianDistance <= ((side1/2) + (side2/2))) 
		return 1;
	return 0;
}

void updateSpaceshipPosition(SPACESHIP* sp, SPACESHIP* enemy, SCREEN* sc, void (*positionFunction) (SPACESHIP*, int, unsigned char, SCREEN*)){
	float* d = NULL;

	if (enemy){
		d = normalizedDistance(sp->x, sp->y, enemy->x, enemy->y);	
	}

	float epsilon = (float) 1/(SPACESHIP_SIDE + SPACESHIP_STEP);

	/*
		Um desvio no eixo x
			- positivo: o inimigo está a direita
			- negativo: o inimigo está a esquerda
		Um desvio no eixo y
			- positivo: o inimigo está para baixo
			- negativo: o inimigo está para cima 
	*/	

	if (sp->control->left){
		if (d[0] > -epsilon)
			positionFunction(sp, 1, 0, sc);
	}
	if (sp->control->right){
		if (d[0] < epsilon)
			positionFunction(sp, 1, 1, sc);
	}
	if (sp->control->up){
		if (d[1] > -epsilon)
			positionFunction(sp, 1, 2, sc);
	}
	if (sp->control->down){
		if (d[1] < epsilon)
			positionFunction(sp, 1, 3, sc);
	}
}
