#include "Thread.Linux.hpp"
#include <pthread.h>

namespace Core
{
	namespace System
	{
		namespace Threading
		{
			Thread::Thread(pthread_t ThreadID) : ThreadID(ThreadID)
			{
			}

			UInt32 Thread::Join()
			{
				void* ExitCode;
				pthread_join(ThreadID, &ExitCode);
				return *((UInt32*)ExitCode);
			}

			IThread* CreateThread(ThreadFonc ThreadEntry, void* ThreadParam)
			{
				int ErrCode;
				pthread_attr_t Attributes;
				pthread_t ThreadID;

				if(!pthread_attr_init(&Attributes))
				{
					ErrCode = pthread_create(&ThreadID, &Attributes, ThreadEntry, &ThreadParam);
					pthread_attr_destroy(&Attributes);
				}

				return ErrCode == 0 ? new Thread(ThreadID) : NULL;
			}
		}
	}
}
