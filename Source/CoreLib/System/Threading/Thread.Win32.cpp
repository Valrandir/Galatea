#include "Thread.Win32.hpp"

namespace Core
{
	namespace System
	{
		namespace Threading
		{
			ThreadImpl::ThreadImpl(ThreadFonc ThreadEntry, VoidPtr ThreadParam) :
				ThreadEntry(ThreadEntry),
				ThreadParam(ThreadParam),
				ReturnValue(0),
				ThreadHandle(0)
			{}

			DWORD WINAPI ThreadImpl::NativeThreadEntry(VoidPtr ThreadParam)
			{
				ThreadImpl& ThreadRef = *(ThreadImpl*)ThreadParam;
				ThreadRef.ReturnValue = ThreadRef.ThreadEntry(ThreadRef.ThreadParam);
				return 0U;
			}

			Thread* CreateThread(ThreadFonc ThreadEntry, VoidPtr ThreadParam)
			{
				HANDLE ThreadHandle;
				ThreadImpl* Thread = new ThreadImpl(ThreadEntry, ThreadParam);

				ThreadHandle = ::CreateThread(NULL, 0, ThreadImpl::NativeThreadEntry, (LPVOID)Thread, 0, NULL);

				if(ThreadHandle)
				{
					Thread->ThreadHandle = ThreadHandle;
					return Thread;
				}
				else
				{
					Delete(Thread);
					return NULL;
				}
			}

			VoidPtr ThreadImpl::Join()
			{
				if(ThreadHandle)
				{
					WaitForSingleObject(ThreadHandle, INFINITE);
					ThreadHandle = 0;
				}
				return ReturnValue;
			}
		}
	}
}
