#pragma once

namespace dragon
{

	/// TODO:	This class could like the XorShift/Random can have multiple implementations.
	///			Essentially Squirrel Noise is a Random Engine it just allows it to do so with a key entry and reproduce the same value.
	class SquirrelNoise
	{
		unsigned int m_seed;

	public:

		/// <summary>
		/// Create a new SquirrelNoise, Random Noise Generator.
		/// </summary>
		/// <param name="seed"></param>
		/// <returns></returns>
		constexpr SquirrelNoise(unsigned int seed = 0) noexcept : m_seed(seed) { }

		/// <summary>
		/// Generate 1-Dimensional noise value from the given point and seed.
		/// </summary>
		/// <param name="x">Point in 1 dimensional space.</param>
		/// <param name="seedOverride">The seed to use.</param>
		static constexpr unsigned int Get1DNoise(int x, unsigned int seedOverride) noexcept
		{
			// This algorithm (called SquirrelNoise3) was originally written by Squirrel Eiserloh and was presented in 
			// his 2017 GDC talk titled Math for Game Programmers: Noise-Based RNG, which can be found here:
			// https://www.gdcvault.com/play/1024365/Math-for-Game-Programmers-Noise

			constexpr unsigned int kBitNoise1 = 0x68e31da4;
			constexpr unsigned int kBitNoise2 = 0xb5297a4d;
			constexpr unsigned int kBitNoise3 = 0x1b56c4e9;

			unsigned int mangledBits = static_cast<unsigned int>(x);
			mangledBits *= kBitNoise1;
			mangledBits += seedOverride;
			mangledBits ^= (mangledBits >> 8);
			mangledBits *= kBitNoise2;
			mangledBits ^= (mangledBits << 8);
			mangledBits *= kBitNoise3;
			mangledBits ^= (mangledBits >> 8);
			return mangledBits;
		}

		/// <summary>
		/// Generate 1-Dimensional noise value from the given point.
		/// </summary>
		/// <param name="x">Point in 1 dimensional space.</param>
		constexpr unsigned int Get1DNoise(int x) const noexcept { return Get1DNoise(x, m_seed); }

		/// <summary>
		/// Generate a 2-Dimensional noise value from the given point and seed.
		/// </summary>
		/// <param name="x">Point X in 2-Dimensional Space.</param>
		/// <param name="y">Point Y in 2-Dimensional Space.</param>
		/// <param name="seedOverride">The given seed to use.</param>
		static constexpr unsigned int Get2DNoise(int x, int y, unsigned int seedOverride) noexcept
		{
			constexpr unsigned int kPrime = 198491317; // Literal copy from the GDC talk.
			return Get1DNoise(x + (kPrime * y), seedOverride);
		}

		/// <summary>
		/// Generate a 2-Dimensional noise value from the given point.
		/// </summary>
		/// <param name="x">Point X in 2-Dimensional Space.</param>
		/// <param name="y">Point Y in 2-Dimensional Space.</param>
		constexpr unsigned int Get2DNoise(int x, int y) const noexcept { return Get2DNoise(x, y, m_seed); }

		/// <summary>
		/// Generate a 3-Dimensional noise value from the given point and seed.
		/// </summary>
		/// <param name="x">Point X in 3-Dimensional Space.</param>
		/// <param name="y">Point Y in 3-Dimensional Space.</param>
		/// <param name="z">Point Z in 3-Dimensional Space.</param>
		/// <param name="seedOverride">The given seed to use.</param>
		static constexpr unsigned int Get3DNoise(int x, int y, int z, unsigned int seedOverride) noexcept
		{
			constexpr unsigned int kPrime1 = 198491317;
			constexpr unsigned int kPrime2 = 6543989;
			return Get1DNoise(x + (kPrime1 * y) + (kPrime2 * z), seedOverride);
		}

		/// <summary>
		/// Generate a 3-Dimensional noise value from the given point.
		/// </summary>
		/// <param name="x">Point X in 3-Dimensional Space.</param>
		/// <param name="y">Point Y in 3-Dimensional Space.</param>
		/// <param name="z">Point Z in 3-Dimensional Space.</param>
		constexpr unsigned int Get3DNoise(int x, int y, int z) const noexcept { return Get3DNoise(x, y, z, m_seed); }

		/// <summary>
		/// Get the current seed.
		/// </summary>
		constexpr unsigned int GetSeed() const noexcept { return m_seed; }

		/// <summary>
		/// Set the seed of the random noise generator.
		/// </summary>
		/// <param name="seed">The seed to set.</param>
		void SetSeed(unsigned int seed) noexcept { m_seed = seed; }
	};

}