#include "OrbitCamera.hpp"

OrbitCamera::OrbitCamera(Vector3 pos, float radius, float zoom) :controller(pos,radius,zoom)
{

}

void OrbitCamera::update(float dt, bool clic, Vector2 pos, float zooming)
{
	stillclick = clic;

	controller.update(dt, clic, pos, zooming);
}
