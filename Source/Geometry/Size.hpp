#pragma once
#include "Point.hpp"

namespace Galatea
{
	namespace Geometry
	{
		struct Size : public Point
		{
			Size() : Point() {}
			Size(int x, int y) : Point(x, y) {}
		};
	}
}
