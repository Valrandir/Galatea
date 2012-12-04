#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "IThread.hpp"

namespace Core
{
	namespace System
	{
		namespace Threading
		{
			class Thread : public IThread
			{
				HANDLE hThread;
				DWORD ThreadID;

				Thread(Thread const &);
				Thread(IThread::ThreadLink Link);

				static DWORD WINAPI NativeThreadEntry(VoidPtr ThreadParam);
				friend IThread* CreateThread(ThreadFonc ThreadEntry, VoidPtr ThreadParam);

				public:
				void Join(VoidPtr* ReturnValue);
			};
		}
	}
}
