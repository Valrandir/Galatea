#include "Thread.Win32.hpp"

namespace Core
{
	namespace System
	{
		namespace Threading
		{
			Thread::Thread(ThreadFonc ThreadEntry, VoidPtr ThreadParam) : IThread(ThreadEntry, ThreadParam)
			{
			}

			VoidPtr Thread::Join()
			{
				WaitForSingleObject(hThread, INFINITE);
				return GetReturnValue();
			}

			DWORD WINAPI Thread::NativeThreadEntry(VoidPtr ThreadParam)
			{
				((IThread*)ThreadParam)->Execute();
				return 0U;
			}

			IThread* CreateThread(ThreadFonc ThreadEntry, VoidPtr ThreadParam)
			{
				HANDLE hThread;
				DWORD ThreadID;
				Thread* thread = new Thread(ThreadEntry, ThreadParam);

				hThread = ::CreateThread(0, 0, Thread::NativeThreadEntry, (LPVOID)thread, CREATE_SUSPENDED, &ThreadID);

				if(hThread)
				{
					thread->hThread = hThread;
					thread->ThreadID = ThreadID;
					ResumeThread(hThread);
					return thread;
				}

				return 0;
			}
		}
	}
}
