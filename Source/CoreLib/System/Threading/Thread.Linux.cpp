#include "Thread.Linux.hpp"

namespace Core
{
	namespace System
	{
		namespace Threading
		{
			void* ThreadImpl::NativeThreadEntry(void* ThreadParam)
			{
				ThreadImpl& ThreadRef = *(ThreadImpl*)ThreadParam;
				ThreadRef.ReturnValue = ThreadRef.ThreadEntry(ThreadRef.ThreadParam);
				return (void*)0U;
			}

			ThreadImpl::ThreadImpl(ThreadFonc ThreadEntry, VoidPtr ThreadParam) :
				ThreadEntry(ThreadEntry),
				ThreadParam(ThreadParam),
				ReturnValue(0),
				ThreadID(0)
			{}

			ThreadImpl* ThreadImpl::CreateInstance(ThreadFonc ThreadEntry, VoidPtr ThreadParam)
			{
				Int32 ErrCode;
				pthread_t ThreadID;
				ThreadImpl* Thread = new ThreadImpl(ThreadEntry, ThreadParam);

				ErrCode = pthread_create(&ThreadID, NULL, NativeThreadEntry, (void*)Thread);

				if(!ErrCode)
				{
					Thread->ThreadID = ThreadID;
					return Thread;
				}
				else
				{
					System::SetErrCode((UInt32)ErrCode);
					DeletePtr(Thread);
					return NULL;
				}
			}

			Thread* CreateThread(ThreadFonc ThreadEntry, VoidPtr ThreadParam)
			{
				return ThreadImpl::CreateInstance(ThreadEntry, ThreadParam);
			}

			VoidPtr ThreadImpl::Join()
			{
				if(ThreadID)
				{
					pthread_join(ThreadID, NULL);
					ThreadID = 0;
				}
				return ReturnValue;
			}
		}
	}
}
