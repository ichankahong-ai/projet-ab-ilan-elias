#pragma once

#include <algorithm>
#include <cmath>
#include <numbers>

struct Vec3
{
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
};

enum class ProjectileKind { Standard, Heavy };

struct ShotSettings
{
    Vec3 origin;
    Vec3 direction;
    float speed = 0.0f;
    ProjectileKind projectileKind = ProjectileKind::Standard;
};

struct LauncherInput
{
    bool azimuthNegative = false;
    bool azimuthPositive = false;
    bool elevationUp = false;
    bool elevationDown = false;
    bool speedUp = false;
    bool speedDown = false;
    bool selectStandard = false;
    bool selectHeavy = false;
};

class Launcher
{
public:
    static constexpr float kMinAzimuthDeg = -30.0f;
    static constexpr float kMaxAzimuthDeg = 30.0f;
    static constexpr float kMinElevationDeg = 5.0f;
    static constexpr float kMaxElevationDeg = 55.0f;
    static constexpr float kMinSpeed = 8.0f;
    static constexpr float kMaxSpeed = 22.0f;

    explicit Launcher(Vec3 origin = { -8.0f, 1.0f, 0.0f })
        : origin_(origin)
    {
    }

    void setAzimuthDeg(float deg) { azimuthDeg_ = std::clamp(deg, kMinAzimuthDeg, kMaxAzimuthDeg); }
    void setElevationDeg(float deg) { elevationDeg_ = std::clamp(deg, kMinElevationDeg, kMaxElevationDeg); }
    void setSpeed(float speed) { speed_ = std::clamp(speed, kMinSpeed, kMaxSpeed); }
    void setKind(ProjectileKind k) { kind_ = k; }

    float azimuthDeg() const { return azimuthDeg_; }
    float elevationDeg() const { return elevationDeg_; }
    float speed() const { return speed_; }
    ProjectileKind kind() const { return kind_; }

    void setRates(float angularDegPerSec, float speedPerSec)
    {
        angularRate_ = angularDegPerSec;
        speedRate_ = speedPerSec;
    }

    void aim(const LauncherInput& in, float dt)
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

    Vec3 direction() const
    {
        const float a = azimuthDeg_ * kDegToRad;
        const float e = elevationDeg_ * kDegToRad;
        const float ce = std::cos(e);
        return { ce * std::cos(a), std::sin(e), ce * std::sin(a) };
    }

    ShotSettings shotSettings() const
    {
        return { origin_, direction(), speed_, kind_ };
    }

    Vec3 initialVelocity() const
    {
        const Vec3 d = direction();
        return { d.x * speed_, d.y * speed_, d.z * speed_ };
    }

private:
    static constexpr float kDegToRad = std::numbers::pi_v<float> / 180.0f;

    Vec3 origin_;
    float azimuthDeg_ = 0.0f;
    float elevationDeg_ = 30.0f;
    float speed_ = 16.0f;
    ProjectileKind kind_ = ProjectileKind::Standard;

    float angularRate_ = 30.0f;
    float speedRate_ = 6.0f;    
};