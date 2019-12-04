#include "PerlinNoise.h"

#include <Dragon/Generic/Math.h>

namespace dragon
{
	float PerlinNoise::NormalizedNoise(float x, float y, unsigned int seedOverride)
	{
		return dragon::math::Normalize(Noise(x, y, seedOverride), -.707f, .707f);
	}

	float PerlinNoise::NormalizedNoise(float x, float y) const
	{
		return NormalizedNoise(x, y, m_seed);
	}

	float PerlinNoise::Noise(float x, float y, unsigned int seed)
	{
		// Determine grid cell coordinates
		int x0 = (int)x;
		int x1 = x0 + 1;
		int y0 = (int)y;
		int y1 = y0 + 1;

		// Determine interpolation weights
		float sx = dragon::math::SmootherStep(x - (float)x0);
		float sy = dragon::math::SmootherStep(y - (float)y0);

		// Interpolate between grid point gradients
		float n0 = DotProductGradient(x0, y0, x, y, seed);
		float n1 = DotProductGradient(x1, y0, x, y, seed);
		float ix0 = dragon::math::Lerp(n0, n1, sx);

		n0 = DotProductGradient(x0, y1, x, y, seed);
		n1 = DotProductGradient(x1, y1, x, y, seed);
		float ix1 = dragon::math::Lerp(n0, n1, sx);

		float value = dragon::math::Lerp(ix0, ix1, sy);
		return value;
	}

	float PerlinNoise::Noise(float x, float y) const
	{
		return Noise(x, y, m_seed);
	}

	float PerlinNoise::AverageNoise(float x, float y, float range, size_t octaves, float persistance, unsigned int seedOverride)
	{
		if (octaves <= 0)
			return 0.f;

		float noise = 0.f;
		float currentAmp = 1.f;
		float totalAmp = 0.f;

		for (size_t i = octaves; i > 0; --i)
		{
			totalAmp += currentAmp;

			float localNoise = Noise(x, y, SquirrelNoise::Get1DNoise(i, seedOverride));
			noise += localNoise * currentAmp;

			currentAmp *= persistance;
			range *= 2;
		}

		noise /= totalAmp;

		return noise;
	}

	float PerlinNoise::AverageNoise(float x, float y, float range, size_t octaves, float persistance)
	{
		return AverageNoise(x, y, range, octaves, persistance, m_seed);
	}


	float PerlinNoise::DotProductGradient(int ix, int iy, float x, float y, unsigned int seed)
	{
		// Distance between points.
		float dx = x - (float)ix;
		float dy = y - (float)iy;

		float rx = SquirrelNoise::Get3DNoiseUniform(iy, ix, 0, seed);
		float ry = SquirrelNoise::Get3DNoiseUniform(iy, ix, 1, seed);

		// Dot product of the value.
		return (dx * rx + dy * ry);
	}

}