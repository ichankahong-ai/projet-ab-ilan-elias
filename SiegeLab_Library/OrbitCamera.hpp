#pragma once

#include "ICameraController.h"
#include "../packages/raylib.6.2.0/build/native/include/raylib.h"

class OrbitCamera
{
public:
	OrbitCamera(Vector3 pos, float radius, float zoom);

	Camera3D getCamera() { return controller.getCamera(); };
private:
	ICameraController controller;
};

