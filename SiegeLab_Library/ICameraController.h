#pragma once

#include "CameraManager.h"
#include "../packages/raylib.6.2.0/build/native/include/raylib.h"

class ICameraController
{
public:
	ICameraController(Vector3 pos, float radius, float zoom);

	Camera3D getCamera() { return manager.getCamera(); };
private:
	CameraManager manager;
};

