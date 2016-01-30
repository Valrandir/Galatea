#pragma once
#include "../Types.hpp"
#include "Clock.hpp"
#include "Rate.hpp"

namespace Galatea
{
	namespace Timing
	{
		Int64 GetTickCount();
		void Sleep(UInt32 milliseconds);
	};
}
