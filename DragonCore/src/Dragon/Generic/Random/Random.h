#pragma once

#include <cstdint>
#include <EASTL/type_traits.h>

namespace dragon
{

	/// <summary>
	/// Interface for Randomizers.
	/// </summary>
	template<typename RandImpl>
	class _Random
	{
		RandImpl impl;

	public:
		using SeedType = typename RandImpl::SeedType;

		_Random() = default;
		_Random(std::nullptr_t) {}
		_Random(typename RandImpl::SeedType seed)
		{
			impl.Seed(seed);
		}

		/// <summary>
		/// Seed the randomizer through an unsigned int.
		/// </summary>
		/// <param name="seed"></param>
		void Seed(unsigned int seed)
		{
			impl.Seed(seed);
		}

		/// <summary>
		/// Seed the randomizer with the seed type of the engine.
		/// </summary>
		template<typename _SeedType = RandImpl::SeedType>
		void Seed(_SeedType seed)
		{
			impl.Seed(seed);
		}

		/// <summary>
		/// Get the current seed "state" of the randomizer.
		/// </summary>
		/// <returns>SeedState of the engine.</returns>
		typename RandImpl::SeedType GetSeed() const
		{
			return impl.GetSeed();
		}

		/// <summary>
		/// Generate a random number for the type.
		/// </summary>
		/// <returns>An number from minimum to maximum value of the type.</returns>
		template<typename Type, typename Decayed = eastl::decay_t<Type>>
		Decayed Random()
		{
			return impl.Random<Decayed>();
		}

		/// <summary>
		/// Generate a random number between low and high.
		/// </summary>
		/// <param name="low">The minimum value to generate.</param>
		/// <param name="high">The maximum value to generate.</param>
		template<typename Type, typename Decayed = eastl::decay_t<Type>>
		Decayed RandomRange(Type low, Type high)
		{
			// Can't divide by 0, This makes sure that never happens.
			if (low == high)
				return low;

			return Random<Decayed>() % (high - low) + low;
		}

		/// <summary>
		/// RandomRange on floating point.
		/// </summary>
		/// <param name="low">Minimum float value.</param>
		/// <param name="high">Maximum float value.</param>
		float RandomRange(float low, float high)
		{
			float rand = impl.RandomUniform();
			float diff = high - low;
			return low + (rand * diff);
		}

		/// <summary>
		/// Generate a number between [0.f, 1.f]
		/// </summary>
		float RandomUniform()
		{
			return impl.RandomUniform();
		}

		/// <summary>
		/// Generates a random number to index an element in an array.
		/// </summary>
		/// <param name="size">The size of the array</param>
		size_t RandomIndex(size_t size)
		{
			return impl.Random<size_t>() % size;
		}

		/// <summary>
		/// Equal chance boolean, As high precision the platform can support.
		/// </summary>
		/// <returns>true or false</returns>
		bool RandomBool()
		{
			constexpr size_t kMax = std::numeric_limits<size_t>::max();
			constexpr size_t kHalfMax = kMax / 2;
			return impl.Random<size_t>() % kMax > kHalfMax ? true : false;
		}

	};

}