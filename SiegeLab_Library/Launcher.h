#pragma once
#include "ShotSettings.h"
#include "InputController.h"
class Launcher
{
public:
	float yaw;
	float pitch;
	float speed;

	void aim(InputController& input);

	
};
