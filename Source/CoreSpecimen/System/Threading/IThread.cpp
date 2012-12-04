#include <Core.hpp>
using namespace Core;

ThreadFoncDef(ThreadEntry)
{
	UInt32 value = *((UInt32*)ThreadParam);
	value *= value;
	return value;
}

void IThreadTest()
{
	void* Param = (void*)55U;
	System::Threading::IThread* thread;
	UInt32 ExitCode;

	thread = System::Threading::CreateThread(ThreadEntry, Param);
	ExitCode = thread->Join();

	delete thread;
}
