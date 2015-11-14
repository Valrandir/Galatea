#include "../Timing/Timing.hpp"
#include <stdint.h>
#include <stdlib.h>

namespace Galatea
{
	namespace Math
	{
		Int32 Random(Int32 min, Int32 max)
		{
			static bool initialized;

			if(!initialized)
			{
				srand(static_cast<UInt32>(Timing::GetTickCount()));
				initialized = true;
			}

			return (rand() % (max - min)) + min;
		}
	}
}
