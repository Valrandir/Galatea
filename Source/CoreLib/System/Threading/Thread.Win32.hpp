#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "Thread.hpp"

namespace Core
{
	namespace System
	{
		namespace Threading
		{
			class ThreadImpl : public Thread
			{
				ThreadFonc _threadEntry;
				VoidPtr _threadParam;
				VoidPtr _returnValue;
				HANDLE _threadHandle;

				static DWORD WINAPI NativeThreadEntry(LPVOID threadParam);
				ThreadImpl(ThreadFonc threadEntry, VoidPtr threadParam);

				public:
				static ThreadImpl* CreateInstance(ThreadFonc threadEntry, VoidPtr threadParam);
				VoidPtr Join();
			};
		}
	}
}
