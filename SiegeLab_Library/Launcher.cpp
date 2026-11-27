#include "Launcher.h"

void Launcher::setRates(float angularDegPerSec, float speedPerSec)
{
    angularRate_ = angularDegPerSec;
    speedRate_ = speedPerSec;
}

void Launcher::aim(const LauncherInput& in, float dt)
{
    if (in.azimuthPositive) setAzimuthDeg(azimuthDeg_ + angularRate_ * dt);
    if (in.azimuthNegative) setAzimuthDeg(azimuthDeg_ - angularRate_ * dt);
    if (in.elevationUp)     setElevationDeg(elevationDeg_ + angularRate_ * dt);
    if (in.elevationDown)   setElevationDeg(elevationDeg_ - angularRate_ * dt);
    if (in.speedUp)         setSpeed(speed_ + speedRate_ * dt);
    if (in.speedDown)       setSpeed(speed_ - speedRate_ * dt);

    if (in.selectStandard)  kind_ = ProjectileKind::Standard;
    if (in.selectHeavy)     kind_ = ProjectileKind::Heavy;
}

Vector3 Launcher::direction() const
{
    const float a = azimuthDeg_ * kDegToRad;
    const float e = elevationDeg_ * kDegToRad;
    const float ce = std::cos(e);
    return { ce * std::cos(a), std::sin(e), ce * std::sin(a) };
}
