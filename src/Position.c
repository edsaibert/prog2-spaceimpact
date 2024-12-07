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

	if (squaredDistance < 1e-6){
		d[0] = 0;
		d[1] = 1;
	}
	else {
		float magnitude = sqrtf(squaredDistance);	
		d[0] = distance_x / magnitude;
		d[1] = distance_y / magnitude;
	}
	
	return d;

	/*
	   Um desvio no eixo x
	   - positivo: o inimigo está a direita
	   - negativo: o inimigo está a esquerda
	   Um desvio no eixo y
	   - positivo: o inimigo está para baixo
	   - negativo: o inimigo está para cima 
	 */	
}




// Checa a colisão entre objetos utilizando a função da circunferência e distância euclidiana
short int checkCollision(int x1, int y1, int x2, int y2, int side1, int side2){
	int euclidianDistance = (x2-x1)*(x2-x1) + (y2-y1)*(y2-y1);
	// euclidianDistance = sqrt(euclidianDistance);

	if (euclidianDistance <= (((side1 / 2) + (side2 / 2)) * ((side1 / 2) + (side2 / 2)))) 
		return 1;
	return 0;
}

