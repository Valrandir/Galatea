#pragma once
#include "../Timing/Timing.hpp"

namespace Galatea
{
	namespace Input
	{
		class Command
		{
			Timing::Rate rate;
			bool triggered;

			public:
			Command(Int32 updates_per_second);
			bool Trigger();
			bool IsTriggered();
			void Reset();
		};
	}
}
