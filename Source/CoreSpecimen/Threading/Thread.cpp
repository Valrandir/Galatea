#include "../Core.hpp"
using namespace Core;

VoidPtr ThreadEntryByValue(VoidPtr ThreadParam)
{
	UInt value = (Int)ThreadParam;
	value *= value;
	return (VoidPtr)value;
}

VoidPtr ThreadEntryByRef(VoidPtr ThreadParam)
{
	UInt32& value = *(UInt32*)ThreadParam;
	value *= value;
	return ThreadParam;
}

Bool ThreadTestByValue()
{
	Bool result = true;

	Int Param = 55U;
	VoidPtr ThreadParam = (VoidPtr)Param;
	VoidPtr ReturnValue;
	Threading::Thread* Thread;

	Thread = Threading::CreateThread(ThreadEntryByValue, ThreadParam);
	CHECK Thread;

	if(Thread)
	{
		ReturnValue = Thread->Join();
		DeletePtr(Thread);
		CHECK (Int)ReturnValue == Param * Param;
	}

	return result;
}

Bool ThreadTestByRef()
{
	Bool result = true;

	UInt32 Param = 55U;
	VoidPtr ThreadParam = (VoidPtr)&Param;
	VoidPtr ReturnValue;
	Threading::Thread* Thread;

	Thread = Threading::CreateThread(ThreadEntryByRef, ThreadParam);
	CHECK Thread != 0;

	if(Thread)
	{
		ReturnValue = Thread->Join();
		DeletePtr(Thread);
		CHECK *(UInt32*)ReturnValue == Param;
		CHECK ReturnValue == &Param;
	}

	return result;
}

Bool ThreadTest()
{
	Bool result = true;

	CHECK ThreadTestByValue();
	CHECK ThreadTestByRef();

	return result;
}
