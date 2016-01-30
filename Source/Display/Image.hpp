#pragma once
#include "Color.hpp"
#include "../Geometry/Point.hpp"
#include "../Geometry/Rectangle.hpp"

namespace Galatea
{
	namespace Display
	{
		class Image
		{
			public:
			virtual ~Image();

			virtual void Clear(Color color = Color()) const = 0;
			virtual void DrawRect(const Geometry::Rectangle& rectangle, Color color) const = 0;
			virtual void DrawImage(const Geometry::Point& position, const Image* image, Color color = {0xff, 0xff, 0xff}, bool horizontal_flip = false, bool vertical_flip = false) const = 0;
			virtual void DrawImage(const Geometry::Point& position, Geometry::Rectangle source, const Image* image, Color color = {0xff, 0xff, 0xff}, bool horizontal_flip = false, bool vertical_flip = false) const = 0;

			virtual int Width() const = 0;
			virtual int Height() const = 0;
		};
	}
}
