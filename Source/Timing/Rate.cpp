#include "Rate.hpp"

namespace Galatea
{
	namespace Timing
	{
		Rate::Rate(Int32 updates_per_second) :
			_updates_per_second{updates_per_second},
			_update_per_milliseconds{updates_per_second / 1000.0},
			_accumulated_milliseconds{}
		{}

		Int32 Rate::Update()
		{
			Double milliseconds_elapsed = _clock.Tick() + _accumulated_milliseconds;
			Double update_count = milliseconds_elapsed * _update_per_milliseconds;
			Int32 rounded_update_count = static_cast<Int32>(update_count);
			_accumulated_milliseconds = (update_count - rounded_update_count) / _update_per_milliseconds;
			return rounded_update_count;
		}

		void Rate::Reset()
		{
			_clock.Reset();
			_accumulated_milliseconds = 0;
		}
	}
}
