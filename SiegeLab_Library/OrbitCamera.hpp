#pragma once

#include "ICameraController.h"
#include "raylib.h"

class OrbitCamera
{
public:
	OrbitCamera(Vector3 pos, float radius, float zoom);

	void update(float dt, bool clic, Vector2 pos, float zooming);

	Camera3D getCamera() { return controller.getCamera(); };
private:
	ICameraController controller;

	bool stillclick = false;
};

