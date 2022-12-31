#include "controls.h"

u32 kdr() {
	return keysHeld();
}

/* Controls section */
bool btn_up() {
	return kdr() & KEY_UP;
}

bool btn_down() {
	return kdr() & KEY_DOWN;
}

bool btn_left() {
	return kdr() & KEY_LEFT;
}

bool btn_right() {
	return kdr() & KEY_RIGHT;
}

bool btn_lbump() {
  return kdr() & KEY_L;
}

bool btn_rbump() {
  return kdr() & KEY_R;
}