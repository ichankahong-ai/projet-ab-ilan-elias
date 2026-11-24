#include "pch.h"
#include "framework.h"

#include "Game.h"

#include "raylib.h"

void Game::Run()
{
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(800, 600, "Hello Raylib");

	Camera3D camera{};
	camera.position = { 0, 5, 10 }; camera.target = { 0.0, 0.0 ,0.0 }; camera.up = { 0 ,1 ,0 }; camera.fovy = 100; camera.projection = CAMERA_ORTHOGRAPHIC;

	// game loop
	while (!WindowShouldClose())		// run the loop until the user presses ESCAPE or presses the Close button on the window
	{
		// drawing
		BeginDrawing();

		// Setup the back buffer for drawing (clear color and depth buffers)
		ClearBackground(BLACK);

		// draw some text using the default font
		DrawText("Hello Raylib", 200, 200, 20, WHITE);

		BeginMode3D(camera);
		DrawCircle3D(Vector3(0, 0, 0), 50, Vector3(0, 0, 0), 10, RED);
		DrawSphere(Vector3(0, 0, 0), 10, RED);
		EndMode3D();
		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		EndDrawing();
	}

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
}
