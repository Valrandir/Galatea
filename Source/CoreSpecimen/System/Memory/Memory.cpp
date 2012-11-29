#include <Core.hpp>

void MemoryTest()
{
	void *pMem = NULL;
	Core::UInt32 const OneMegabytes = 1024U * 1024U * 16U;
	pMem = Core::System::Memory::Alloc(OneMegabytes);
	Core::System::Memory::Free(pMem);
	pMem = NULL;
}
