#pragma once

#include <Dragon/Generic/Random/Random.h>
#include <Dragon/Generic/Random/XorShift.h>

#include <Dragon/Generic/Random/SquirrelNoise.h>
#include <Dragon/Generic/Random/PerlinNoise.h>

namespace dragon
{

	using Random = _Random<XorShift>;

	template<typename RandImpl>
	using Rand = _Random<RandImpl>;

}