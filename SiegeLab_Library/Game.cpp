#include "pch.h"
#include "framework.h"

#include "Game.h"

#include "../packages/raylib.6.2.0/build/native/include/raylib.h"

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

	bool locked = false;
	int mode = CAMERA_FREE;

	//DisableCursor();
	//SetMouseCursor();

	// game loop
	while (!WindowShouldClose())		// run the loop until the user presses ESCAPE or presses the Close button on the window
	{

		if (IsKeyPressed(KEY_UP)) mode = CAMERA_FREE;
		else if (IsKeyPressed(KEY_LEFT)) mode = CAMERA_FIRST_PERSON;
		else if (IsKeyPressed(KEY_RIGHT)) mode = CAMERA_ORBITAL;
		UpdateCamera(camera, mode);


		orbit.update(GetFrameTime(), IsMouseButtonDown(MOUSE_BUTTON_RIGHT),
			GetMouseDelta(), GetMouseWheelMove());


		if (IsKeyPressed(KEY_DOWN)) locked = !locked;
		if (locked) {
			camera->target = Vector3{ 0.0f, 0.0f, 0.0f };
		}
		else {

		}

		// drawing
		BeginDrawing();
		ClearBackground(RAYWHITE);
		BeginMode3D(orbit.getCamera());
		DrawGrid(20, 1.0f);
		DrawCube({ 0.0f, 0.0f, 0.0f }, 2.0f, 2.0f, 2.0f, RED);
		EndMode3D();
		EndDrawing();

		//DrawText("Mode:", 20, 20, 10, BLACK);
		//DrawText("Locked rotation:", 20, 40, 10, DARKGRAY);
		if (locked){ DrawText("Shoot Mode", 110, 40, 20, RED); }
		else { DrawText("Aim Mode", 110, 40, 20, GREEN); }
	}

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
}
