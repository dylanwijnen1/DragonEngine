#pragma once

#include <Dragon/Generic/Random/SquirrelNoise.h>

namespace dragon
{
	/// TODO: Create static accessor methods with seed overrides. Just like SquirrelNoise.
	class PerlinNoise
	{
		unsigned int m_seed;

	public:
		static const unsigned int kDefaultNoiseSeed = 87852469; // Random Prime Number

		PerlinNoise() : m_seed(kDefaultNoiseSeed) {}
		~PerlinNoise() = default;

		PerlinNoise(const PerlinNoise&) = default;
		PerlinNoise(PerlinNoise&&) = default;
		PerlinNoise& operator=(const PerlinNoise&) = default;
		PerlinNoise& operator=(PerlinNoise&&) = default;

		void Seed(unsigned int seed) { m_seed = seed; }
		unsigned int GetSeed() const { m_seed; }

		static float NormalizedNoise(float x, float y, unsigned int seedOverride);
		float NormalizedNoise(float x, float y) const;

		// Compute Perlin noise at coordinates x, y 
		static float Noise(float x, float y, unsigned int seed);
		float Noise(float x, float y) const;

	private:

		// Computes the dot product of the distance and gradient vectors.
		static float DotProductGradient(int ix, int iy, float x, float y, unsigned int seed);

	};
}