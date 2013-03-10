#pragma once
#include <pthread.h>
#include "../System.hpp"
#include "Thread.hpp"

namespace Core
{
	namespace Threading
	{
		class ThreadImpl : public Thread
		{
			ThreadFonc _threadEntry;
			VoidPtr _threadParam;
			VoidPtr _returnValue;
			pthread_t _threadID;

			static void* NativeThreadEntry(void* threadParam);
			ThreadImpl(ThreadFonc threadEntry, VoidPtr threadParam);

			public:
			static ThreadImpl* CreateInstance(ThreadFonc threadEntry, VoidPtr threadParam);
			VoidPtr Join();
		};
	}
}
