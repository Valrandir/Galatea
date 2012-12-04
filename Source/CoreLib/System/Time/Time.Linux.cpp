#include <time.h>
#include "Time.hpp"

namespace Core
{
	namespace System
	{
		namespace Time
		{
			void Sleep(UInt32 Milliseconds)
			{
				timespec req = {Milliseconds / 1000, Milliseconds % 1000 * 1000000};
				nanosleep(&req, NULL);
			}
		}
	}
}
