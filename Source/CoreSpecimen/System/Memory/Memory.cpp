#include <Core.hpp>
using namespace Core;

void MemoryTest()
{
	void *pMem = NULL;
	UInt32 const OneMegabytes = 1024U * 1024U * 16U;
	pMem = System::Memory::Alloc(OneMegabytes);
	System::Memory::Free(pMem);
	pMem = NULL;
}
