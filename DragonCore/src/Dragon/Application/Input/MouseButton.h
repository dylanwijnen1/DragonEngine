#pragma once

#include <EASTL/numeric_limits.h>

enum struct MouseButton : unsigned char
{
	Unknown = 255,
	Left = 0,
	Middle,
	Right,

	// Must always be last.
	kCount
};