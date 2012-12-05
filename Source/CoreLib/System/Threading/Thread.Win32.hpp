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

				static DWORD WINAPI NativeThreadEntry(VoidPtr ThreadParam);
				ThreadImpl(ThreadFonc ThreadEntry, VoidPtr ThreadParam);

				public:
				static ThreadImpl* CreateInstance(ThreadFonc ThreadEntry, VoidPtr ThreadParam);
				VoidPtr Join();
			};
		}
	}
}
