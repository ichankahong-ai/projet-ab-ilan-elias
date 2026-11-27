#include "InputController.h"

#include "raylib.h"

LauncherInput InputController::captureLauncher() const
{
    LauncherInput in;

    in.pitchUp = IsKeyDown(KEY_SPACE);
    in.pitchDown = IsKeyDown(KEY_LEFT_CONTROL);
    in.cameraForward = IsKeyDown(KEY_W);
    in.cameraBackward = IsKeyDown(KEY_S);
    in.yawRight = IsKeyDown(KEY_D);
    in.yawLeft = IsKeyDown(KEY_A);
    in.cameraLeanLeft = IsKeyDown(KEY_Q);
    in.cameraLeanRight = IsKeyDown(KEY_E);

    in.cameraspin = IsKeyDown(KEY_ENTER);

    in.azimuthNegative = IsKeyDown(KEY_K);
    in.azimuthPositive = IsKeyDown(KEY_SEMICOLON);
    in.elevationUp = IsKeyDown(KEY_O);
    in.elevationDown = IsKeyDown(KEY_L);
    in.speedUp = IsKeyDown(KEY_P);
    in.speedDown = IsKeyDown(KEY_I);

    in.selectStandard = IsKeyPressed(KEY_ONE);
    in.selectHeavy = IsKeyPressed(KEY_TWO);

    return in;
}