#include "InputController.h"

#include "raylib.h"

LauncherInput InputController::captureLauncher() const
{
    LauncherInput in;

    in.azimuthNegative = IsKeyDown(KEY_A);
    in.azimuthPositive = IsKeyDown(KEY_D);
    in.elevationUp = IsKeyDown(KEY_W);
    in.elevationDown = IsKeyDown(KEY_S);
    in.speedUp = IsKeyDown(KEY_E);
    in.speedDown = IsKeyDown(KEY_Q);

    in.selectStandard = IsKeyPressed(KEY_ONE);
    in.selectHeavy = IsKeyPressed(KEY_TWO);

    return in;
}