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
				ThreadFonc ThreadEntry;
				VoidPtr ThreadParam;
				VoidPtr ReturnValue;
				HANDLE ThreadHandle;

				ThreadImpl(ThreadFonc ThreadEntry, VoidPtr ThreadParam);
				static DWORD WINAPI NativeThreadEntry(VoidPtr ThreadParam);
				friend Thread* CreateThread(ThreadFonc ThreadEntry, VoidPtr ThreadParam);

				public:
				VoidPtr Join();
			};
		}
	}
}
