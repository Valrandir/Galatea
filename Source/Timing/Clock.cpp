#include "Clock.hpp"
#include "Timing.hpp"

namespace Galatea
{
	namespace Timing
	{
		Clock::Clock()
		{
			_last_tick = Timing::GetTickCount();
		}

		Int32 Clock::Tick()
		{
			Int64 tick = Timing::GetTickCount();
			Int64 elapsed = tick - _last_tick;
			_last_tick = tick;
			return static_cast<Int32>(elapsed);
		}
	}
}
