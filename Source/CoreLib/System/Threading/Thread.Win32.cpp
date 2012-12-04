#include "Thread.Win32.hpp"

namespace Core
{
	namespace System
	{
		namespace Threading
		{
			ThreadImpl::ThreadImpl(ThreadFonc ThreadEntry, VoidPtr ThreadParam) : ThreadEntry(ThreadEntry), ThreadParam(ThreadParam)
			{
			}

			DWORD WINAPI ThreadImpl::NativeThreadEntry(VoidPtr ThreadParam)
			{
				ThreadImpl& ThreadRef = *(ThreadImpl*)ThreadParam;
				ThreadRef.ReturnValue = ThreadRef.ThreadEntry(ThreadRef.ThreadParam);
				return 0U;
			}

			Thread* CreateThread(ThreadFonc ThreadEntry, VoidPtr ThreadParam)
			{
				HANDLE hThread;
				DWORD ThreadID;
				ThreadImpl* thread = new ThreadImpl(ThreadEntry, ThreadParam);

				hThread = ::CreateThread(0, 0, ThreadImpl::NativeThreadEntry, (LPVOID)thread, CREATE_SUSPENDED, &ThreadID);

				if(hThread)
				{
					thread->hThread = hThread;
					thread->ThreadID = ThreadID;
					ResumeThread(hThread);
					return thread;
				}

				return 0;
			}

			VoidPtr ThreadImpl::Join()
			{
				WaitForSingleObject(hThread, INFINITE);
				return ReturnValue;
			}
		}
	}
}
