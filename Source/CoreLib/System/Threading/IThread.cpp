#include "IThread.hpp"

namespace Core
{
	namespace System
	{
		namespace Threading
		{
			IThread::IThread(ThreadLink Link)
			{
				this->Link = Link;
			}

			IThread::ThreadLink* IThread::GetLink()
			{
				return &Link;
			}
		}
	}
}
