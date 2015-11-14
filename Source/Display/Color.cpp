#include "Color.hpp"
#include "../Math/Math.hpp"

namespace Galatea
{
	namespace Display
	{
		Color::Color() : red{}, green{}, blue{}, alpha{} {}
		Color::Color(UInt8 red, UInt8 green, UInt8 blue) : red{red}, green{green}, blue{blue}, alpha{0xff} {}
		Color::Color(UInt8 red, UInt8 green, UInt8 blue, UInt8 alpha) : red{red}, green{green}, blue{blue}, alpha{alpha} {}

		Color Color::White() { return Color{0xff, 0xff, 0xff}; }
		Color Color::Black() { return Color{0x0, 0x0, 0x0}; }
		Color Color::Red() { return Color{0xff, 0x0, 0x0}; }
		Color Color::Green() { return Color{0x0, 0xff, 0x0}; }
		Color Color::Blue() { return Color{0x0, 0x0, 0xff}; }
		Color Color::Teal() { return Color{0x00, 0xff, 0xff}; }
		Color Color::Pink() { return Color{0xff, 0x0, 0xff}; }
		Color Color::Yellow() { return Color{0xff, 0xff, 0x00}; }
		Color Color::Gray() { return Color{0x7f, 0x7f, 0x7f}; }

		Color Color::Random()
		{
			int red = Math::Random(0, 0xff);
			int green = Math::Random(0, 0xff);
			int blue = Math::Random(0, 0xff);

			return Color(red, green, blue);
		}
	}
}
