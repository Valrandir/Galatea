#include "Thread.Linux.hpp"

namespace Core
{
	namespace Threading
	{
		void* ThreadImpl::NativeThreadEntry(void* threadParam)
		{
			ThreadImpl& threadRef = *(ThreadImpl*)threadParam;
			threadRef._returnValue = threadRef._threadEntry(threadRef._threadParam);
			return (void*)0U;
		}

		ThreadImpl::ThreadImpl(ThreadFonc threadEntry, VoidPtr threadParam) :
			_threadEntry(threadEntry),
			_threadParam(threadParam),
			_returnValue(0),
			_threadID(0)
		{}

		ThreadImpl* ThreadImpl::CreateInstance(ThreadFonc threadEntry, VoidPtr threadParam)
		{
			Int32 errCode;
			pthread_t threadID;
			ThreadImpl* thread = new ThreadImpl(threadEntry, threadParam);

			errCode = pthread_create(&threadID, NULL, NativeThreadEntry, (void*)thread);

			if(!errCode)
			{
				thread->_threadID = threadID;
				return thread;
			}
			else
			{
				SetErrCode((UInt32)errCode);
				DeletePtr(thread);
				return NULL;
			}
		}

		Thread* CreateThread(ThreadFonc threadEntry, VoidPtr threadParam)
		{
			return ThreadImpl::CreateInstance(threadEntry, threadParam);
		}

		VoidPtr ThreadImpl::Join()
		{
			if(_threadID)
			{
				pthread_join(_threadID, NULL);
				_threadID = 0;
			}
			return _returnValue;
		}
	}
}
