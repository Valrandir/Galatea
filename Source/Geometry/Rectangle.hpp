#pragma once
#include "Point.hpp"

namespace Galatea
{
	namespace Geometry
	{
		struct Rectangle
		{
			Point position;
			Point size;

			Rectangle();
			Rectangle(const Point& position, const Point& size);

			Rectangle(const Rectangle& src);
			Rectangle& operator=(const Rectangle& src);
			bool operator==(const Rectangle& src) const;
			bool Intersect(const Rectangle& src) const;
		};
	}
}
