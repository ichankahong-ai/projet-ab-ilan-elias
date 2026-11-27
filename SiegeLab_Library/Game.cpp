#include "pch.h"
#include "framework.h"

#include "Game.h"

#include "raylib.h"
#include "raymath.h"

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

	Launcher launcher;
	InputController input;

	bool locked = false;
	int mode = CAMERA_FREE;


	// game loop
	while (!WindowShouldClose())		// run the loop until the user presses ESCAPE or presses the Close button on the window
	{
		const LauncherInput inputs = input.captureLauncher();

		if (IsKeyPressed(KEY_UP)) mode = CAMERA_FREE;
		/*else if (IsKeyPressed(KEY_LEFT)) mode = CAMERA_FIRST_PERSON;
		else if (IsKeyPressed(KEY_RIGHT)) mode = CAMERA_ORBITAL;*/
		UpdateCamera(camera, mode);


		orbit.update(GetFrameTime(), IsMouseButtonDown(MOUSE_BUTTON_RIGHT),
			GetMouseDelta(), GetMouseWheelMove());

		if (inputs.cameraspin) {
			locked = !locked;  
			locked ? EnableCursor(): DisableCursor();
		}
		if (locked) { 
			camera->target = Vector3{ 0.0f, 0.0f, 0.0f };
			launcher.aim(inputs, GetFrameTime());
		}
		else { DisableCursor(); }

		const ShotSettings shot = launcher.shotSettings();

		// drawing
		BeginDrawing();
		ClearBackground(RAYWHITE);
		BeginMode3D(orbit.getCamera());
		DrawGrid(20, 1.0f);
		DrawCube({ 0.0f, 0.0f, 0.0f }, 2.0f, 2.0f, 2.0f, RED);

		DrawSphere(shot.origin, shot.projectileKind == ProjectileKind::Heavy ? 0.36f : 0.28f, shot.projectileKind == ProjectileKind::Heavy ? DARKPURPLE : BLUE);
		DrawLine3D(shot.origin, shot.tip, RED);
		DrawSphere(shot.tip, 0.1f, RED);

		EndMode3D();

		//DrawText("Mode:", 20, 20, 10, BLACK);
		//DrawText("Locked rotation:", 20, 40, 10, DARKGRAY);
		DrawText(TextFormat("Azimut    : %.1f deg", launcher.azimuthDeg()), 10, 10, 20, DARKGRAY);
		DrawText(TextFormat("Elevation : %.1f deg", launcher.elevationDeg()), 10, 34, 20, DARKGRAY);
		DrawText(TextFormat("Vitesse   : %.1f m/s", launcher.speed()), 10, 58, 20, DARKGRAY);
		DrawText(TextFormat("Projectile: %s", shot.projectileKind == ProjectileKind::Heavy ? "Heavy" : "Standard"), 10, 82, 20, DARKGRAY);

		if (locked){ DrawText("Shoot Mode", 110, 540, 20, RED); }
		else { DrawText("Spectator Mode", 110, 540, 20, GREEN); }

		EndDrawing();
	}

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
}
