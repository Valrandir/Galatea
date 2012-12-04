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

				Thread(HANDLE hThread, DWORD ThreadID);
				Thread(Thread const &);

				friend IThread* CreateThread(ThreadFonc ThreadEntry, void* ThreadParam);

				public:
				UInt32 Join();
			};
		}
	}
}
