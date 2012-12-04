#pragma once
#include <pthread.h>
#include "IThread.hpp"

namespace Core
{
	namespace System
	{
		namespace Threading
		{
			class Thread : public IThread
			{
				pthread_t ThreadID;

				Thread(pthread_t ThreadID);
				Thread(Thread const &);

				friend IThread* CreateThread(ThreadFonc ThreadEntry, void* ThreadParam);

				public:
				UInt32 Join();
			};
		}
	}
}
