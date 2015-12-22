#pragma once
#include "../Types.hpp"

namespace Galatea
{
	namespace Display
	{
		struct Color
		{
			UInt8
				red,
				green,
				blue,
				alpha;

			Color();
			Color(UInt8 red, UInt8 green, UInt8 blue);
			Color(UInt8 red, UInt8 green, UInt8 blue, UInt8 alpha);

			static Color White();
			static Color Black();
			static Color Red();
			static Color Green();
			static Color Blue();
			static Color Teal();
			static Color Pink();
			static Color Yellow();
			static Color Gray();

			static Color Random();
		};
	}
}
