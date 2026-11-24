#pragma once

#include "../packages/raylib.6.2.0/build/native/include/raylib.h"

class CameraManager
{
public:
	CameraManager(Vector3 pos, float radius, float zoom);

	Camera3D getCamera() { return camera; };
private:
	Camera3D camera{};
	float Xzoom;
};

