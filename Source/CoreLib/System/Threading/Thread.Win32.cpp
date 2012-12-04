#include "Thread.Win32.hpp"

namespace Core
{
	namespace System
	{
		namespace Threading
		{
			Thread::Thread(ThreadFonc ThreadEntry, VoidPtr ThreadParam) : ThreadEntry(ThreadEntry), ThreadParam(ThreadParam)
			{
			}

			DWORD WINAPI Thread::NativeThreadEntry(VoidPtr ThreadParam)
			{
				Thread& ThreadRef = *(Thread*)ThreadParam;
				ThreadRef.ReturnValue = ThreadRef.ThreadEntry(ThreadRef.ThreadParam);
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

			VoidPtr Thread::Join()
			{
				WaitForSingleObject(hThread, INFINITE);
				return ReturnValue;
			}
		}
	}
}
