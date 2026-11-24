#include "CameraManager.h"


CameraManager::CameraManager(Vector3 pos, float radius, float zoom)
{
	camera.position = pos;
	camera.target = { 0,0,0 };
	camera.up = { 0, 1, 1 };
	camera.fovy = 20;
	camera.projection = CAMERA_ORBITAL;
	Xzoom = zoom;
}
