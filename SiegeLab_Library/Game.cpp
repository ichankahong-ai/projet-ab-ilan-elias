#include "pch.h"
#include "framework.h"

#include "Game.h"

#include "../packages/raylib.6.2.0/build/native/include/raylib.h"

#include "InputController.h"
#include "Launcher.h"
#include "OrbitCamera.hpp" // To implement

void Game::Run()
{
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(800, 600, "Hello Raylib");

	OrbitCamera orbit({ 2.0f, 1.5f, 0.0f }, 12.0f, 90.0f);
	Camera3D* camera = orbit.getCamerastar();
	/*Camera3D camera{};
	camera.position = { 0, 5, 10 }; camera.target = { 0.0, 0.0 ,0.0 }; camera.up = { 0 ,1 ,0 }; camera.fovy = 100; camera.projection = CAMERA_ORTHOGRAPHIC;*/
	Launcher launcher;        
	InputController input;
	DisableCursor();

	// game loop
	while (!WindowShouldClose())		// run the loop until the user presses ESCAPE or presses the Close button on the window
	{
		UpdateCamera(camera, CAMERA_FREE);
		//UpdateCamera(camera, CAMERA_FREE);

		orbit.update(GetFrameTime(), IsMouseButtonDown(MOUSE_BUTTON_RIGHT),
			GetMouseDelta(), GetMouseWheelMove());

		launcher.aim(input.captureLauncher(), GetFrameTime());

		const ShotSettings shot = launcher.shotSettings();
		const bool heavy = (shot.projectileKind == ProjectileKind::Heavy);

		const Vector3 origin = { shot.origin.x, shot.origin.y, shot.origin.z };
		const float length = shot.speed * 0.4f;
		const Vector3 tip = {
			origin.x + shot.direction.x * length,
			origin.y + shot.direction.y * length,
			origin.z + shot.direction.z * length
		};

		if (IsKeyDown(KEY_DOWN)) camera->target = Vector3{0.0f, 0.0f, 0.0f};
		// drawing
		BeginDrawing();
		ClearBackground(RAYWHITE);
		BeginMode3D(orbit.getCamera());
		DrawGrid(20, 1.0f);
		DrawCube({ 0.0f, 0.0f, 0.0f }, 2.0f, 2.0f, 2.0f, RED);

		DrawSphere(origin, heavy ? 0.36f : 0.28f, heavy ? DARKPURPLE : BLUE);
		DrawLine3D(origin, tip, RED);
		DrawSphere(tip, 0.1f, RED);

		EndMode3D();

		DrawText(TextFormat("Azimut    : %.1f deg", launcher.azimuthDeg()), 10, 10, 20, DARKGRAY);
		DrawText(TextFormat("Elevation : %.1f deg", launcher.elevationDeg()), 10, 34, 20, DARKGRAY);
		DrawText(TextFormat("Vitesse   : %.1f m/s", launcher.speed()), 10, 58, 20, DARKGRAY);
		DrawText(TextFormat("Projectile: %s", heavy ? "Heavy" : "Standard"), 10, 82, 20, DARKGRAY);

		EndDrawing();
	}

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
}
