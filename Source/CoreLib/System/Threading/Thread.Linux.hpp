#pragma once
#include <pthread.h>
#include "../System.hpp"
#include "Thread.hpp"

namespace Core
{
	namespace System
	{
		namespace Threading
		{
			class ThreadImpl : public Thread
			{
				ThreadFonc ThreadEntry;
				VoidPtr ThreadParam;
				VoidPtr ReturnValue;
				pthread_t ThreadID;

				static void* NativeThreadEntry(void* ThreadParam);
				ThreadImpl(ThreadFonc ThreadEntry, VoidPtr ThreadParam);

				public:
				static ThreadImpl* CreateInstance(ThreadFonc ThreadEntry, VoidPtr ThreadParam);
				VoidPtr Join();
			};
		}
	}
}
