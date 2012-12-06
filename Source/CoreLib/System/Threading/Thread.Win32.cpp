#include "Thread.Win32.hpp"

namespace Core
{
	namespace System
	{
		namespace Threading
		{
			DWORD WINAPI ThreadImpl::NativeThreadEntry(LPVOID ThreadParam)
			{
				ThreadImpl& ThreadRef = *(ThreadImpl*)ThreadParam;
				ThreadRef.ReturnValue = ThreadRef.ThreadEntry(ThreadRef.ThreadParam);
				return (DWORD)0U;
			}

			ThreadImpl::ThreadImpl(ThreadFonc ThreadEntry, VoidPtr ThreadParam) :
				ThreadEntry(ThreadEntry),
				ThreadParam(ThreadParam),
				ReturnValue(0),
				ThreadHandle(0)
			{}

			ThreadImpl* ThreadImpl::CreateInstance(ThreadFonc ThreadEntry, VoidPtr ThreadParam)
			{
				HANDLE ThreadHandle;
				ThreadImpl* Thread = new ThreadImpl(ThreadEntry, ThreadParam);

				ThreadHandle = ::CreateThread(NULL, 0, NativeThreadEntry, (LPVOID)Thread, 0, NULL);

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

			Thread* CreateThread(ThreadFonc ThreadEntry, VoidPtr ThreadParam)
			{
				return ThreadImpl::CreateInstance(ThreadEntry, ThreadParam);
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
