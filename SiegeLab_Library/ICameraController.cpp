#include "ICameraController.h"
#include <iostream>

ICameraController::ICameraController(Vector3 pos, float radius, float zoom): manager(pos, radius, zoom)
{
}

void ICameraController::update(float dt, bool clic, Vector2 pos, float zooming)
{
	if (zooming!=0) {
		manager.setZoom(manager.getzoom() + zooming);
		std::cout << zooming<<std::endl;
	}
}
