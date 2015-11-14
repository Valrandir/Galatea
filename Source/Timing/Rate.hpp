#pragma once
#include "../Types.hpp"
#include "Clock.hpp"

namespace Galatea
{
	namespace Timing
	{
		class Rate
		{
			private:
			Clock _clock;
			Int32 _updates_per_second;
			Double _update_per_milliseconds;
			Double _accumulated_milliseconds;

			public:
			Rate(Int32 updates_per_second);
			Int32 Update();
		};
	}
}
