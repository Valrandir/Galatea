#pragma once
#include "Point.hpp"

namespace Galatea
{
	namespace Geometry
	{
		struct Center : public Point
		{
			Center() : Point() {}
			Center(int x, int y) : Point(x, y) {}
		};
	}
}
