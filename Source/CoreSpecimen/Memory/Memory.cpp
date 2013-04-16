#include "../Core.hpp"
using namespace Core;

Bool FreeTest()
{
	Bool result = true;

	CHECK_ASSERT(Memory::Free(0));

	return result;
}

Bool CopyTest()
{
	Bool result = true;

	CHECK_ASSERT(Memory::Copy((VoidPtr)0, (VoidPtr)0, 0));
	CHECK_ASSERT(Memory::Copy((VoidPtr)0, (VoidPtr)1, 0));
	CHECK_ASSERT(Memory::Copy((VoidPtr)1, (VoidPtr)0, 0));

	return result;
}


Bool MoveTest()
{
	Bool result = true;

	CHECK_ASSERT(Memory::Move((VoidPtr)0, (VoidPtr)0, 0));
	CHECK_ASSERT(Memory::Move((VoidPtr)0, (VoidPtr)1, 0));
	CHECK_ASSERT(Memory::Move((VoidPtr)1, (VoidPtr)0, 0));

	return result;
}

Bool AllocFreeTest()
{
	Bool result = true;

	void *pMem = NULL;
	UInt32 const OneMegabytes = 1024U * 1024U * 16U;

	pMem = Memory::Alloc(OneMegabytes);
	CHECK pMem != 0;

	Memory::Free(pMem);
	pMem = NULL;

	return result;
}

Bool MemoryTest()
{
	Bool result = true;

	CHECK FreeTest();
	CHECK CopyTest();
	CHECK MoveTest();
	CHECK AllocFreeTest();

	return result;
}
