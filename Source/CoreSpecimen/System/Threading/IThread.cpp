#include <Core.hpp>
using namespace Core;

VoidPtr ThreadEntry(VoidPtr ThreadParam)
{
	UInt32 value = (UInt32)ThreadParam;
	value *= value;
	return (VoidPtr)value;
}

void IThreadTest()
{
	VoidPtr Param = (VoidPtr)55U;
	VoidPtr ReturnValue;

	System::Threading::IThread* thread;

	thread = System::Threading::CreateThread(ThreadEntry, Param);
	if(thread)
	{
		ReturnValue = thread->Join();
		delete thread;
	}
}
