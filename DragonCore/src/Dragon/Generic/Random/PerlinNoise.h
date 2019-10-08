#pragma once

#include <Dragon/Generic/Random/SquirrelNoise.h>
#include <algorithm>
#include <cmath>

namespace dragon
{
	class PerlinNoise
	{
		const unsigned int kDefaultNoiseSeed = 87852469; // Random Prime Number

		SquirrelNoise m_grid;

	public:
		PerlinNoise() : m_grid(kDefaultNoiseSeed) {}
		~PerlinNoise() = default;

		PerlinNoise(const PerlinNoise&) = default;
		PerlinNoise(PerlinNoise&&) = default;
		PerlinNoise& operator=(const PerlinNoise&) = default;
		PerlinNoise& operator=(PerlinNoise&&) = default;

		void Seed(unsigned int seed) { m_grid.SetSeed(seed); }
		unsigned int GetSeed() const { m_grid.GetSeed(); }

		// Compute Perlin noise at coordinates x, y
		float Noise(float x, float y)
		{
			// Determine grid cell coordinates
			int x0 = std::floorf(x);
			int x1 = x0 + 1;
			int y0 = std::floorf(y);
			int y1 = y0 + 1;

			// Determine interpolation weights
			float sx = SmootherStep(x - (float)x0);
			float sy = SmootherStep(y - (float)y0);

			// Interpolate between grid point gradients
			float n0 = DotProductGradient(x0, y0, x, y);
			float n1 = DotProductGradient(x1, y0, x, y);
			float ix0 = Lerp(n0, n1, sx);

			n0 = DotProductGradient(x0, y1, x, y);
			n1 = DotProductGradient(x1, y1, x, y);
			float ix1 = Lerp(n0, n1, sx);

			float value = Lerp(ix0, ix1, sy);
			return value;
		}

	private:

		// Computes the dot product of the distance and gradient vectors.
		float DotProductGradient(int ix, int iy, float x, float y)
		{
			// Distance between points.
			float dx = x - (float)ix;
			float dy = y - (float)iy;

			// Dot product of the value.
			return 0.f;
		}

		// TODO: Possibly use Clamp, Lerp and SmootherStep from <Dragon/Generic/Math.h> (Has not been created yet.)

		/// <summary>
		/// Interpolate between a start and goal point.
		/// </summary>
		/// <example>
		///	Lerp(0.0f, 80.0f, 0.5f) ~= 40.f
		/// </example>
		/// <param name="start">The starting value to lerp in between.</param>
		/// <param name="goal">The goal value to lerp to.</param>
		/// <param name="weight">The current weight we are at.</param>
		constexpr inline float Lerp(float start, float goal, float weight) {
			return (1.0f - weight) * start + weight * goal;
		}

		/// <summary>
		/// Curve the value of x to be closer to 0.f or 1.f, Expects x to be in range of [0.f, 1.f]
		/// </summary>
		/// <param name="x">Value between range of [0.f, 1.f]</param>
		/// <returns></returns>
		constexpr inline float SmootherStep(float x)
		{
			x = std::clamp(x, 0.f, 1.f);
			return x * x * x * (x * (x * 6 - 15) + 10);
		}
	};
}