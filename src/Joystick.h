#ifndef JOYSTICK_H
#define JOYSTICK_H

#include "../main.h"

typedef struct joystick JOYSTICK;
struct joystick {
	unsigned char right;
	unsigned char left;
	unsigned char up;
	unsigned char down;
	unsigned char shoot;
};

JOYSTICK* createJoystick();					// constutor

void destroyJoystick(JOYSTICK* jt);			// destrutor

void updateJoystickRight(JOYSTICK* jt);		// muda o estado de jt->right

void updateJoystickLeft(JOYSTICK* jt);		// muda o estado de jt->left

void updateJoystickUp(JOYSTICK* jt);		// muda o estado de jt->up

void updateJoystickDown(JOYSTICK* jt);		// muda o estado de jt->down

void updateJoystickShoot(JOYSTICK* jt);

void destroyJoystick(JOYSTICK* jt);

#endif
