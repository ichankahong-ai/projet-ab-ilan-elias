#pragma once
#include <raylib.h>

class InputController
{
	struct Input
	{
		bool key_a;
		bool key_d;
	};

	Input capture() const;
};

