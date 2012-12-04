#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "Time.hpp"

namespace Core
{
	namespace System
	{
		namespace Time
		{
			void Sleep(UInt32 milliseconds)
			{
				::Sleep(milliseconds);
			}
		}
	}
}
