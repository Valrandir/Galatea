#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "Timing.hpp"

namespace Galatea
{
	namespace Timing
	{
		Int64 GetTickCount()
		{
			static LARGE_INTEGER frequency;
			LARGE_INTEGER counter;

			if(!frequency.QuadPart)
			{
				QueryPerformanceFrequency(&frequency); //counts per second
				frequency.QuadPart /= 1000; //counts per milliseconds
			}

			QueryPerformanceCounter(&counter);

			return counter.QuadPart / frequency.QuadPart;
		}

		void Sleep(UInt32 milliseconds)
		{
			::Sleep(milliseconds);
		}
	}
}
