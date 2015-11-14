#include "Thread.Win32.hpp"

namespace Galatea
{
	namespace Threading
	{
		DWORD WINAPI ThreadImpl::NativeThreadEntry(LPVOID threadParam)
		{
			ThreadImpl& threadRef = *(ThreadImpl*)threadParam;
			threadRef._returnValue = threadRef._threadEntry(threadRef._threadParam);
			return (DWORD)0U;
		}

		ThreadImpl::ThreadImpl(ThreadFonc threadEntry, VoidPtr threadParam) :
			_threadEntry(threadEntry),
			_threadParam(threadParam),
			_returnValue(0),
			_threadHandle(0)
		{}

		ThreadImpl* ThreadImpl::CreateInstance(ThreadFonc threadEntry, VoidPtr threadParam)
		{
			HANDLE threadHandle;
			ThreadImpl* Thread = new ThreadImpl(threadEntry, threadParam);

			threadHandle = ::CreateThread(NULL, 0, NativeThreadEntry, (LPVOID)Thread, 0, NULL);

			if(threadHandle)
			{
				Thread->_threadHandle = threadHandle;
				return Thread;
			}
			else
			{
				DeletePtr(Thread);
				return NULL;
			}
		}

		VoidPtr ThreadImpl::Join()
		{
			if(_threadHandle)
			{
				WaitForSingleObject(_threadHandle, INFINITE);
				_threadHandle = 0;
			}
			return _returnValue;
		}

		Thread* CreateThread(ThreadFonc threadEntry, VoidPtr threadParam)
		{
			return ThreadImpl::CreateInstance(threadEntry, threadParam);
		}

		//Thread* GetCurrentThread()
		//{
		//}
	}
}
