#include "Thread.Win32.hpp"

namespace Core
{
	namespace System
	{
		namespace Threading
		{
			Thread::Thread(HANDLE hThread, DWORD ThreadID) : hThread(hThread), ThreadID(ThreadID)
			{
			}

			UInt32 Thread::Join()
			{
				DWORD ExitCode;
				WaitForSingleObject(hThread, INFINITE);
				GetExitCodeThread(hThread, &ExitCode);
				return ExitCode;
			}

			IThread* CreateThread(ThreadFonc ThreadEntry, void* ThreadParam)
			{
				HANDLE hThread;
				DWORD ThreadID;

				hThread = ::CreateThread(0, 0, ThreadEntry, ThreadParam, 0, &ThreadID);

				return hThread ? new Thread(hThread, ThreadID) : 0;
			}
		}
	}
}
