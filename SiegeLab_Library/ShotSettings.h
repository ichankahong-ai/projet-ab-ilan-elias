#pragma once
#include <raylib.h>

enum ProjKind
{
	HEAVY,
	STANDARD
};

class ShotSettings {
	Vector3 origin{ 0 ,0 ,0 };
	Vector3 direction{ 1 ,0 ,0 };

	float speed = 0;

	ProjKind proj = ProjKind::STANDARD;
};
