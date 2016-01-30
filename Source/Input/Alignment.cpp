#include "Alignment.hpp"

namespace Galatea
{
	namespace Input
	{
		using namespace Geometry;

		Alignment::Alignment(int max_power, int sensibility) :
			max_power{max_power},
			sensibility{sensibility},
			center{},
			power{}
		{}

		Alignment::Alignment(int max_power, int sensibility, const Point& center) :
			max_power{max_power},
			sensibility{sensibility},
			center{center},
			power{}
		{}

		Alignment& Alignment::Reset(const Point& center)
		{
			this->center = center;
			power = 0;
			return *this;
		}

		Alignment& Alignment::Update(const Point& position)
		{
			Point offset = position - center;
			power = offset / sensibility;

			if(power.x > max_power) power.x = max_power;
			if(power.x < -max_power) power.x = -max_power;
			if(power.y > max_power) power.y = max_power;
			if(power.y < -max_power) power.y = -max_power;

			return *this;
		}
	}
}
