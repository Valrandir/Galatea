#include "IThread.hpp"

namespace Core
{
	namespace System
	{
		namespace Threading
		{
			IThread::IThread(ThreadFonc ThreadEntry, VoidPtr ThreadParam) : ThreadEntry(ThreadEntry), ThreadParam(ThreadParam)
			{
			}

			void IThread::Execute()
			{
				ReturnValue = ThreadEntry(ThreadParam);
			}

			VoidPtr IThread::GetReturnValue()
			{
				return ReturnValue;
			}
		}
	}
}
