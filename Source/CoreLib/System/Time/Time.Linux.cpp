#include <time.h>
#include "Time.hpp"

namespace Core
{
	namespace Time
	{
		void Time::Sleep(UInt32 milliseconds)
		{
			timespec req = {milliseconds / 1000, milliseconds % 1000 * 1000000};
			nanosleep(&req, NULL);
		}
	}
}
