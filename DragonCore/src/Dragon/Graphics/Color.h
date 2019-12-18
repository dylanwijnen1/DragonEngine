#pragma once

#include <stdint.h>

#include <Dragon/Generic/Math.h>
#include <Dragon/Generic/Random.h>

namespace dragon
{
	struct Color
	{
	public:
		constexpr Color()
			: Color(0.0f, 0.0f, 0.0f)
		{}

		constexpr Color(float r, float g, float b, float a)
			: r(r)
			, g(g)
			, b(b)
			, a(a)
		{}

		constexpr Color(float r, float g, float b)
			: Color(r, g, b, 1.0f)
		{}

		///// <summary>
		///// Lerp between two colors.
		///// </summary>
		///// <param name="left">Beginning color</param>
		///// <param name="right">Ending color</param>
		///// <param name="weight">Percentage/Weight between the two colors.</param>
		///// <returns>The lerped color.</returns>
		//static constexpr Color Lerp(Color left, Color right, float weight)
		//{
		//	Color lerpedColor;
		//	lerpedColor.r = dragon::math::Lerp(left.r, right.r, weight);
		//	lerpedColor.g = dragon::math::Lerp(left.g, right.g, weight);
		//	lerpedColor.b = dragon::math::Lerp(left.b, right.b, weight);
		//	lerpedColor.a = dragon::math::Lerp(left.a, right.a, weight);
		//}

		static constexpr Color FromHex(uint32_t hex)
		{
			Color color;
			color.r = ((hex >> 16) & 0xFF) / 255.0f;
			color.g = ((hex >> 8) & 0xFF) / 255.0f;
			color.b = (hex & 0xFF) / 255.0f;
			color.a = 1.0f;
			return color;
		}

		/// <summary>
		/// Conversion from: https://www.rapidtables.com/convert/color/hsv-to-rgb.html
		/// TODO: When fmodf and fabsf are made constexpr make this function constexpr.
		/// </summary>
		/// <param name="hue">[0.f, 360.f]</param>
		/// <param name="sat">[0.0f, 1.0f]</param>
		/// <param name="val">[0.0f, 1.0f]</param>
		/// <returns></returns>
		static Color FromHSV(float hue, float sat, float val)
		{
			Color color;

			float c = val * sat;
			float hh = hue / 60.f;
			float hueMod = std::fmodf(hh, 2.0f);
			float x = c * (1.0f - std::fabsf(hueMod - 1.0f));
			float m = val - c;

			if (hh >= 0.f && hh < 1.f)
			{
				color.r = c;
				color.g = x;
			}
			else if (hh >= 1.f && hh < 2.f)
			{
				color.r = x;
				color.g = c;
			}
			else if (hh >= 2.f && hh < 3.f)
			{
				color.g = c;
				color.b = x;
			}
			else if (hh >= 3.f && hh < 4.f)
			{
				color.g = x;
				color.b = c;
			}
			else if (hh >= 4.f && hh < 5.f)
			{
				color.r = x;
				color.b = c;
			}
			else
			{
				color.r = c;
				color.b = x;
			}

			m = val - c;
			color.r += m;
			color.g += m;
			color.b += m;

			return color;
		}

		// Properties
		float r;
		float g;
		float b;
		float a;

	};

#pragma region Predefined Colors Definition
	namespace Colors
	{
		inline constexpr Color AliceBlue(0.94f, 0.97f, 1.00f, 1.0f);
		inline constexpr Color AntiqueWhite(0.98f, 0.92f, 0.84f, 1.0f);
		inline constexpr Color Aqua(0.00f, 1.00f, 1.00f, 1.0f);
		inline constexpr Color Aquamarine(0.50f, 1.00f, 0.83f, 1.0f);
		inline constexpr Color Azure(0.94f, 1.00f, 1.00f, 1.0f);
		inline constexpr Color Beige(0.96f, 0.96f, 0.86f, 1.0f);
		inline constexpr Color Bisque(1.00f, 0.89f, 0.77f, 1.0f);
		inline constexpr Color Black(0.00f, 0.00f, 0.00f, 1.0f);
		inline constexpr Color BlanchedAlmond(1.00f, 0.92f, 0.80f, 1.0f);
		inline constexpr Color Blue(0.00f, 0.00f, 1.00f, 1.0f);
		inline constexpr Color BlueViolet(0.54f, 0.17f, 0.89f, 1.0f);
		inline constexpr Color Brown(0.65f, 0.16f, 0.16f, 1.0f);
		inline constexpr Color BurlyWood(0.87f, 0.72f, 0.53f, 1.0f);
		inline constexpr Color CadetBlue(0.37f, 0.62f, 0.63f, 1.0f);
		inline constexpr Color Chartreuse(0.50f, 1.00f, 0.00f, 1.0f);
		inline constexpr Color Chocolate(0.82f, 0.41f, 0.12f, 1.0f);
		inline constexpr Color Coral(1.00f, 0.50f, 0.31f, 1.0f);
		inline constexpr Color CornflowerBlue(0.39f, 0.58f, 0.93f, 1.0f);
		inline constexpr Color Cornsilk(1.00f, 0.97f, 0.86f, 1.0f);
		inline constexpr Color Crimson(0.86f, 0.08f, 0.24f, 1.0f);
		inline constexpr Color Cyan(0.00f, 1.00f, 1.00f, 1.0f);
		inline constexpr Color DarkBlue(0.00f, 0.00f, 0.55f, 1.0f);
		inline constexpr Color DarkCyan(0.00f, 0.55f, 0.55f, 1.0f);
		inline constexpr Color DarkGoldenRod(0.72f, 0.53f, 0.04f, 1.0f);
		inline constexpr Color DarkGray(0.66f, 0.66f, 0.66f, 1.0f);
		inline constexpr Color DarkGrey(0.66f, 0.66f, 0.66f, 1.0f);
		inline constexpr Color DarkGreen(0.00f, 0.39f, 0.00f, 1.0f);
		inline constexpr Color DarkKhaki(0.74f, 0.72f, 0.42f, 1.0f);
		inline constexpr Color DarkMagenta(0.55f, 0.00f, 0.55f, 1.0f);
		inline constexpr Color DarkOliveGreen(0.33f, 0.42f, 0.18f, 1.0f);
		inline constexpr Color DarkOrange(1.00f, 0.55f, 0.00f, 1.0f);
		inline constexpr Color DarkOrchid(0.60f, 0.20f, 0.80f, 1.0f);
		inline constexpr Color DarkRed(0.55f, 0.00f, 0.00f, 1.0f);
		inline constexpr Color DarkSalmon(0.91f, 0.59f, 0.48f, 1.0f);
		inline constexpr Color DarkSeaGreen(0.56f, 0.74f, 0.56f, 1.0f);
		inline constexpr Color DarkSlateBlue(0.28f, 0.24f, 0.55f, 1.0f);
		inline constexpr Color DarkSlateGray(0.18f, 0.31f, 0.31f, 1.0f);
		inline constexpr Color DarkSlateGrey(0.18f, 0.31f, 0.31f, 1.0f);
		inline constexpr Color DarkTurquoise(0.00f, 0.81f, 0.82f, 1.0f);
		inline constexpr Color DarkViolet(0.58f, 0.00f, 0.83f, 1.0f);
		inline constexpr Color DeepPink(1.00f, 0.08f, 0.58f, 1.0f);
		inline constexpr Color DeepSkyBlue(0.00f, 0.75f, 1.00f, 1.0f);
		inline constexpr Color DimGray(0.41f, 0.41f, 0.41f, 1.0f);
		inline constexpr Color DimGrey(0.41f, 0.41f, 0.41f, 1.0f);
		inline constexpr Color DodgerBlue(0.12f, 0.56f, 1.00f, 1.0f);
		inline constexpr Color FireBrick(0.70f, 0.13f, 0.13f, 1.0f);
		inline constexpr Color FloralWhite(1.00f, 0.98f, 0.94f, 1.0f);
		inline constexpr Color ForestGreen(0.13f, 0.55f, 0.13f, 1.0f);
		inline constexpr Color Fuchsia(1.00f, 0.00f, 1.00f, 1.0f);
		inline constexpr Color Gainsboro(0.86f, 0.86f, 0.86f, 1.0f);
		inline constexpr Color GhostWhite(0.97f, 0.97f, 1.00f, 1.0f);
		inline constexpr Color Gold(1.00f, 0.84f, 0.00f, 1.0f);
		inline constexpr Color GoldenRod(0.85f, 0.65f, 0.13f, 1.0f);
		inline constexpr Color Gray(0.50f, 0.50f, 0.50f, 1.0f);
		inline constexpr Color Grey(0.50f, 0.50f, 0.50f, 1.0f);
		inline constexpr Color Green(0.00f, 0.50f, 0.00f, 1.0f);
		inline constexpr Color GreenYellow(0.68f, 1.00f, 0.18f, 1.0f);
		inline constexpr Color HoneyDew(0.94f, 1.00f, 0.94f, 1.0f);
		inline constexpr Color HotPink(1.00f, 0.41f, 0.71f, 1.0f);
		inline constexpr Color IndianRed(0.80f, 0.36f, 0.36f, 1.0f);
		inline constexpr Color Indigo(0.29f, 0.00f, 0.51f, 1.0f);
		inline constexpr Color Ivory(1.00f, 1.00f, 0.94f, 1.0f);
		inline constexpr Color Khaki(0.94f, 0.90f, 0.55f, 1.0f);
		inline constexpr Color Lavender(0.90f, 0.90f, 0.98f, 1.0f);
		inline constexpr Color LavenderBlush(1.00f, 0.94f, 0.96f, 1.0f);
		inline constexpr Color LawnGreen(0.49f, 0.99f, 0.00f, 1.0f);
		inline constexpr Color LemonChiffon(1.00f, 0.98f, 0.80f, 1.0f);
		inline constexpr Color LightBlue(0.68f, 0.85f, 0.90f, 1.0f);
		inline constexpr Color LightCoral(0.94f, 0.50f, 0.50f, 1.0f);
		inline constexpr Color LightCyan(0.88f, 1.00f, 1.00f, 1.0f);
		inline constexpr Color LightGoldenRodYellow(0.98f, 0.98f, 0.82f, 1.0f);
		inline constexpr Color LightGray(0.83f, 0.83f, 0.83f, 1.0f);
		inline constexpr Color LightGrey(0.83f, 0.83f, 0.83f, 1.0f);
		inline constexpr Color LightGreen(0.56f, 0.93f, 0.56f, 1.0f);
		inline constexpr Color LightPink(1.00f, 0.71f, 0.76f, 1.0f);
		inline constexpr Color LightSalmon(1.00f, 0.63f, 0.48f, 1.0f);
		inline constexpr Color LightSeaGreen(0.13f, 0.70f, 0.67f, 1.0f);
		inline constexpr Color LightSkyBlue(0.53f, 0.81f, 0.98f, 1.0f);
		inline constexpr Color LightSlateGray(0.47f, 0.53f, 0.60f, 1.0f);
		inline constexpr Color LightSlateGrey(0.47f, 0.53f, 0.60f, 1.0f);
		inline constexpr Color LightSteelBlue(0.69f, 0.77f, 0.87f, 1.0f);
		inline constexpr Color LightYellow(1.00f, 1.00f, 0.88f, 1.0f);
		inline constexpr Color Lime(0.00f, 1.00f, 0.00f, 1.0f);
		inline constexpr Color LimeGreen(0.20f, 0.80f, 0.20f, 1.0f);
		inline constexpr Color Linen(0.98f, 0.94f, 0.90f, 1.0f);
		inline constexpr Color Magenta(1.00f, 0.00f, 1.00f, 1.0f);
		inline constexpr Color Maroon(0.50f, 0.00f, 0.00f, 1.0f);
		inline constexpr Color MediumAquaMarine(0.40f, 0.80f, 0.67f, 1.0f);
		inline constexpr Color MediumBlue(0.00f, 0.00f, 0.80f, 1.0f);
		inline constexpr Color MediumOrchid(0.73f, 0.33f, 0.83f, 1.0f);
		inline constexpr Color MediumPurple(0.58f, 0.44f, 0.86f, 1.0f);
		inline constexpr Color MediumSeaGreen(0.24f, 0.70f, 0.44f, 1.0f);
		inline constexpr Color MediumSlateBlue(0.48f, 0.41f, 0.93f, 1.0f);
		inline constexpr Color MediumSpringGreen(0.00f, 0.98f, 0.60f, 1.0f);
		inline constexpr Color MediumTurquoise(0.28f, 0.82f, 0.80f, 1.0f);
		inline constexpr Color MediumVioletRed(0.78f, 0.08f, 0.52f, 1.0f);
		inline constexpr Color MidnightBlue(0.10f, 0.10f, 0.44f, 1.0f);
		inline constexpr Color MintCream(0.96f, 1.00f, 0.98f, 1.0f);
		inline constexpr Color MistyRose(1.00f, 0.89f, 0.88f, 1.0f);
		inline constexpr Color Moccasin(1.00f, 0.89f, 0.71f, 1.0f);
		inline constexpr Color NavajoWhite(1.00f, 0.87f, 0.68f, 1.0f);
		inline constexpr Color Navy(0.00f, 0.00f, 0.50f, 1.0f);
		inline constexpr Color OldLace(0.99f, 0.96f, 0.90f, 1.0f);
		inline constexpr Color Olive(0.50f, 0.50f, 0.00f, 1.0f);
		inline constexpr Color OliveDrab(0.42f, 0.56f, 0.14f, 1.0f);
		inline constexpr Color Orange(1.00f, 0.65f, 0.00f, 1.0f);
		inline constexpr Color OrangeRed(1.00f, 0.27f, 0.00f, 1.0f);
		inline constexpr Color Orchid(0.85f, 0.44f, 0.84f, 1.0f);
		inline constexpr Color PaleGoldenRod(0.93f, 0.91f, 0.67f, 1.0f);
		inline constexpr Color PaleGreen(0.60f, 0.98f, 0.60f, 1.0f);
		inline constexpr Color PaleTurquoise(0.69f, 0.93f, 0.93f, 1.0f);
		inline constexpr Color PaleVioletRed(0.86f, 0.44f, 0.58f, 1.0f);
		inline constexpr Color PapayaWhip(1.00f, 0.94f, 0.84f, 1.0f);
		inline constexpr Color PeachPuff(1.00f, 0.85f, 0.73f, 1.0f);
		inline constexpr Color Peru(0.80f, 0.52f, 0.25f, 1.0f);
		inline constexpr Color Pink(1.00f, 0.75f, 0.80f, 1.0f);
		inline constexpr Color Plum(0.87f, 0.63f, 0.87f, 1.0f);
		inline constexpr Color PowderBlue(0.69f, 0.88f, 0.90f, 1.0f);
		inline constexpr Color Purple(0.50f, 0.00f, 0.50f, 1.0f);
		inline constexpr Color RebeccaPurple(0.40f, 0.20f, 0.60f, 1.0f);
		inline constexpr Color Red(1.00f, 0.00f, 0.00f, 1.0f);
		inline constexpr Color RosyBrown(0.74f, 0.56f, 0.56f, 1.0f);
		inline constexpr Color RoyalBlue(0.25f, 0.41f, 0.88f, 1.0f);
		inline constexpr Color SaddleBrown(0.55f, 0.27f, 0.07f, 1.0f);
		inline constexpr Color Salmon(0.98f, 0.50f, 0.45f, 1.0f);
		inline constexpr Color SandyBrown(0.96f, 0.64f, 0.38f, 1.0f);
		inline constexpr Color SeaGreen(0.18f, 0.55f, 0.34f, 1.0f);
		inline constexpr Color SeaShell(1.00f, 0.96f, 0.93f, 1.0f);
		inline constexpr Color Sienna(0.63f, 0.32f, 0.18f, 1.0f);
		inline constexpr Color Silver(0.75f, 0.75f, 0.75f, 1.0f);
		inline constexpr Color SkyBlue(0.53f, 0.81f, 0.92f, 1.0f);
		inline constexpr Color SlateBlue(0.42f, 0.35f, 0.80f, 1.0f);
		inline constexpr Color SlateGray(0.44f, 0.50f, 0.56f, 1.0f);
		inline constexpr Color SlateGrey(0.44f, 0.50f, 0.56f, 1.0f);
		inline constexpr Color Snow(1.00f, 0.98f, 0.98f, 1.0f);
		inline constexpr Color SpringGreen(0.00f, 1.00f, 0.50f, 1.0f);
		inline constexpr Color SteelBlue(0.27f, 0.51f, 0.71f, 1.0f);
		inline constexpr Color Tan(0.82f, 0.71f, 0.55f, 1.0f);
		inline constexpr Color Teal(0.00f, 0.50f, 0.50f, 1.0f);
		inline constexpr Color Thistle(0.85f, 0.75f, 0.85f, 1.0f);
		inline constexpr Color Tomato(1.00f, 0.39f, 0.28f, 1.0f);
		inline constexpr Color Turquoise(0.25f, 0.88f, 0.82f, 1.0f);
		inline constexpr Color Violet(0.93f, 0.51f, 0.93f, 1.0f);
		inline constexpr Color Wheat(0.96f, 0.87f, 0.70f, 1.0f);
		inline constexpr Color White(1.00f, 1.00f, 1.00f, 1.0f);
		inline constexpr Color WhiteSmoke(0.96f, 0.96f, 0.96f, 1.0f);
		inline constexpr Color Yellow(1.00f, 1.00f, 0.00f, 1.0f);
		inline constexpr Color YellowGreen(0.60f, 0.80f, 0.20f, 1.0f);

	}

#pragma endregion

}