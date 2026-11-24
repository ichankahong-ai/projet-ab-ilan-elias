#pragma once

#include "CameraManager.h"
#include "raylib.h"

class ICameraController
{
public:
	ICameraController(Vector3 pos, float radius, float zoom);

	void update(float dt, bool clic, Vector2 pos, float zooming);

	Camera3D getCamera() { return manager.getCamera(); };
private:
	CameraManager manager;
	Vector2 oldpos = {0,0};
};

