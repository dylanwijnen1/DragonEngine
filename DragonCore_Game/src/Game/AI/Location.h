#pragma once

#include <Game/Vector2.h>

struct Location
{
	Vector2f position;
	float orientation;

	void SetOrientationFromDirection(Vector2f dir);
	Vector2f GetDirectionFromOrientation() const;
};