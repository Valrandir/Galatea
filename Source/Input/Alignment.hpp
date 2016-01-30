#pragma once
#include "../Geometry/Point.hpp"

namespace Galatea
{
	namespace Input
	{
		class Alignment
		{
			//Range is how many levels of power are allowed.
			//If max range is 1, there are two possible power: 0 or 1.
			//If max range is 9, there are ten possible power, from 0 to 9.
			int max_power;

			//Sensibility means how much distance the mouse must move before the power change.
			int sensibility;

			//Position considered to be zero. Offset is calculated from this;
			Geometry::Point center;

			//Current power
			Geometry::Point power;

			public:
			Alignment(int max_power, int sensibility);
			Alignment(int max_power, int sensibility, const Geometry::Point& center);
			Alignment& Reset(const Geometry::Point& center);
			Alignment& Update(const Geometry::Point& position);

			inline int MaxPower() const { return max_power; }
			inline int Sensibility() const { return sensibility; }
			inline Geometry::Point Center() const { return center; }
			inline Geometry::Point Power() const { return power; }
		};
	}
}
