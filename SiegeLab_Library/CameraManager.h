#pragma once

#include "raylib.h"

class CameraManager
{
public:
	CameraManager(Vector3 pos, float radius, float zoom);

	Camera3D getCamera() { return camera; };
	float getzoom() { return Xzoom; }
	void setZoom(float zoom) { Xzoom = zoom; }
private:
	Camera3D camera{};
	float Xzoom;
};

