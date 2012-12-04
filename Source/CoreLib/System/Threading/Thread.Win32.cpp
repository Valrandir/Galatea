#include "Thread.Win32.hpp"

namespace Core
{
	namespace System
	{
		namespace Threading
		{
			Thread::Thread(IThread::ThreadLink Link) : IThread(Link)
			{
			}

			void Thread::Join(void** ReturnValue)
			{
				WaitForSingleObject(hThread, INFINITE);
				if(ReturnValue)
					*ReturnValue = GetLink()->ReturnValue;
			}

			DWORD WINAPI Thread::NativeThreadEntry(void* ThreadParam)
			{
				IThread* th = (IThread*)ThreadParam;
				ThreadLink * link = th->GetLink();
				link->ReturnValue = link->ThreadEntry(link->ThreadParam);
				return 0U;
			}

			IThread* CreateThread(ThreadFonc ThreadEntry, void* ThreadParam)
			{
				HANDLE hThread;
				DWORD ThreadID;
				IThread::ThreadLink link = {ThreadEntry, ThreadParam, 0};
				Thread* thread = new Thread(link);

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
