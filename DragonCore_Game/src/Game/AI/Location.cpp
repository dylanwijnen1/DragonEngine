#include "Location.h"

#include <Dragon/Generic/Math/MathFunctions.h>

void Location::SetOrientationFromDirection(Vector2f dir)
{
	orientation = std::atan2f(dir.y, dir.x) + dragon::math::kPi / 2.0f;
}

Vector2f Location::GetDirectionFromOrientation() const
{
    Vector2f vec;
    vec.x = std::cosf(orientation);
    vec.y = std::sinf(orientation);
    return vec;
}
