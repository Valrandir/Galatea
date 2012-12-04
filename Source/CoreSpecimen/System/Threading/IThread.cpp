#include <Core.hpp>
using namespace Core;

void* ThreadEntry(void* ThreadParam)
{
	UInt32 value = (UInt32)ThreadParam;
	value *= value;
	return (void*)value;
}

void IThreadTest()
{
	void* Param = (void*)55U;
	void* ReturnValue;

	System::Threading::IThread* thread;

	thread = System::Threading::CreateThread(ThreadEntry, Param);
	if(thread)
	{
		thread->Join(&ReturnValue);
		delete thread;
	}
}
