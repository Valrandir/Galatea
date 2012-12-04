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

				static DWORD WINAPI NativeThreadEntry(void* ThreadParam);
				friend IThread* CreateThread(ThreadFonc ThreadEntry, void* ThreadParam);

				public:
				void Join(void** ReturnValue);
			};
		}
	}
}
