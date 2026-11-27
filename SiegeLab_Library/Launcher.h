#pragma once

#include <algorithm>
#include <cmath>
#include <numbers>
#include "raylib.h"

//struct Vec3
//{
//    float x = 0.0f;
//    float y = 0.0f;
//    float z = 0.0f;
//};

enum class ProjectileKind { Standard, Heavy };

struct ShotSettings
{
    Vector3 origin;
    Vector3 direction;
    float speed = 0.0f;
    ProjectileKind projectileKind = ProjectileKind::Standard;

    //const bool heavy = (shot.projectileKind == ProjectileKind::Heavy);
    //const Vector3 origin = { origin.x, origin.y, origin.z };

    const float length = speed * 0.4f;
    const Vector3 tip = {
        origin.x + direction.x * length,
        origin.y + direction.y * length,
        origin.z + direction.z * length
    };
};

struct LauncherInput
{
    //camera base control
    bool pitchUp = false;
    bool pitchDown = false;
    bool cameraForward = false;
    bool cameraBackward = false;
    bool yawRight = false;
    bool yawLeft = false;
    bool cameraLeanLeft = false;
    bool cameraLeanRight = false;

    //camera secondary control
    bool cameraspin = false;

    //cannon base control
    bool azimuthNegative = false;
    bool azimuthPositive = false;
    bool elevationUp = false;
    bool elevationDown = false;
    bool speedUp = false;
    bool speedDown = false;

    //bullet base control
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

    explicit Launcher(Vector3 origin = { -8.0f, 1.0f, 0.0f })
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
    ShotSettings shotSettings() const { return { origin_, direction(), speed_, kind_ }; }
    Vector3 initialVelocity() const { return { direction().x * speed_, direction().y * speed_, direction().z * speed_ }; }

    void setRates(float angularDegPerSec, float speedPerSec);

    void aim(const LauncherInput& in, float dt);

    Vector3 direction() const;

private:
    static constexpr float kDegToRad = std::numbers::pi_v<float> / 180.0f;

    Vector3 origin_;
    float azimuthDeg_ = 0.0f;
    float elevationDeg_ = 30.0f;
    float speed_ = 16.0f;
    ProjectileKind kind_ = ProjectileKind::Standard;

    float angularRate_ = 30.0f;
    float speedRate_ = 6.0f;    


};