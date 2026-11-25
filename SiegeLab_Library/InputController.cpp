#include "InputController.h"

InputController::Input InputController::capture() const
{
	Input key;
	key.key_a = false;
	key.key_d = false;

	if (IsKeyReleased(KEY_A)) key.key_a = true;
	if (IsKeyReleased(KEY_D)) key.key_d = true;

	return key;
}
