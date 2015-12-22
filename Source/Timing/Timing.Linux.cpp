#include <time.h>
#include "Time.hpp"

namespace Core
{
	namespace Timing
	{
		void Sleep(UInt32 Milliseconds)
		{
			Int32 msecs = (Int32)Milliseconds;
			timespec req = {msecs / 1000, msecs % 1000 * 1000000};
			nanosleep(&req, NULL);
		}
	}
}
