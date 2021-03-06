#include "Color.hpp"
#include "../Math/Math.hpp"

namespace Galatea
{
	namespace Display
	{
		Color::Color() : red{}, green{}, blue{}, alpha{0xff} {}
		Color::Color(UInt8 red, UInt8 green, UInt8 blue) : red{red}, green{green}, blue{blue}, alpha{0xff} {}
		Color::Color(UInt8 red, UInt8 green, UInt8 blue, UInt8 alpha) : red{red}, green{green}, blue{blue}, alpha{alpha} {}

		Color Color::White = {0xff, 0xff, 0xff};
		Color Color::Black = {0x0, 0x0, 0x0};
		Color Color::Red = {0xff, 0x0, 0x0};
		Color Color::Green = {0x0, 0xff, 0x0};
		Color Color::Blue = {0x0, 0x0, 0xff};
		Color Color::Teal = {0x00, 0xff, 0xff};
		Color Color::Pink = {0xff, 0x0, 0xff};
		Color Color::Yellow = {0xff, 0xff, 0x00};
		Color Color::Gray = {0x7f, 0x7f, 0x7f};

		Color Color::Random()
		{
			int red = Math::Random(0, 0xff);
			int green = Math::Random(0, 0xff);
			int blue = Math::Random(0, 0xff);

			return Color(red, green, blue);
		}
	}
}
