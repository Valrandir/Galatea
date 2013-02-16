#include "../../Core.hpp"
using namespace Core;

Bool MemoryTest()
{
	Bool result = true;

	void *pMem = NULL;
	UInt32 const OneMegabytes = 1024U * 1024U * 16U;

	pMem = System::Memory::Alloc(OneMegabytes);
	CHECK pMem != 0;

	System::Memory::Free(pMem);
	pMem = NULL;

	return result;
}
