#pragma once
#include "../Types.hpp"

namespace Galatea
{
	namespace Timing
	{
		class Clock
		{
			private:
			Int64 _last_tick;

			public:
			Clock();
			Int32 Tick();
			void Reset();
		};
	}
}
