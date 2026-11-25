#pragma once

#include "raylib.h"

class CameraManager
{
public:
	CameraManager(Vector3 pos, float radius, float zoom);

	Camera3D getCamera() { return camera; };
	Camera3D* getCamerastar() { return &camera; };
	float getzoom() { return Xzoom; }
	void setZoom(float zoom) { Xzoom = zoom; }
	float getFovy() { return fovy; }
	void setFovy(float newy) { camera.fovy = newy; };
private:
	Camera3D camera{};
	float Xzoom;
	float fovy;
};

