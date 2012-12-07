#include "../../Core.hpp"
using namespace Core;

VoidPtr ThreadEntryByValue(VoidPtr ThreadParam)
{
	UInt value = (Int)ThreadParam;
	value *= value;
	return (VoidPtr)value;
}

void ThreadTestByValue()
{
	Int Param = 55U;
	Int Out;
	VoidPtr ThreadParam = (VoidPtr)Param;
	VoidPtr ReturnValue;
	System::Threading::Thread* Thread;

	Thread = System::Threading::CreateThread(ThreadEntryByValue, ThreadParam);

	if(Thread)
	{
		ReturnValue = Thread->Join();
		Out = (Int)ReturnValue;
		Delete(Thread);
	}
}

VoidPtr ThreadEntryByRef(VoidPtr ThreadParam)
{
	UInt32& value = *(UInt32*)ThreadParam;
	value *= value;
	return ThreadParam;
}

void ThreadTestByRef()
{
	UInt32 Param = 55U;
	VoidPtr ThreadParam = (VoidPtr)&Param;
	VoidPtr ReturnValue;
	System::Threading::Thread* Thread;

	Thread = System::Threading::CreateThread(ThreadEntryByRef, ThreadParam);

	if(Thread)
	{
		ReturnValue = Thread->Join();
		Delete(Thread);
	}
}
