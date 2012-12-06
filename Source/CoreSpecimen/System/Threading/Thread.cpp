#include "../../Core.hpp"
using namespace Core;

VoidPtr ThreadEntry(VoidPtr ThreadParam)
{
	UInt32& value = *(UInt32*)ThreadParam;
	value *= value;
	return ThreadParam;
}

void ThreadTest()
{
	UInt32 Param = 55U;
	VoidPtr ThreadParam = (VoidPtr)&Param;
	VoidPtr ReturnValue;
	System::Threading::Thread* Thread;

	Thread = System::Threading::CreateThread(ThreadEntry, ThreadParam);

	if(Thread)
	{
		ReturnValue = Thread->Join();
		Delete(Thread);
	}
}
