#include "Joystick.h"

JOYSTICK* createJoystick(){
	JOYSTICK* jt = (JOYSTICK*) malloc(sizeof(JOYSTICK));
	if (!jt) return NULL;
	
	jt->right = 0;
	jt->left = 0;
	jt->up = 0;
	jt->down = 0;

	return jt;	
}

void updateJoystickRight(JOYSTICK* jt){
	jt->right = jt->right ^ 1;
}

void updateJoystickLeft(JOYSTICK* jt){
	jt->left = jt->left ^ 1;
}

void updateJoystickUp(JOYSTICK* jt){
	jt->up = jt->up ^ 1;
}

void updateJoystickDown(JOYSTICK* jt){
	jt->down = jt->down ^ 1;
}

void destroyJoystick(JOYSTICK* jt){
	free(jt);
}
