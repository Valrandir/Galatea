#include "Core.hpp"

using namespace Core;

Bool SizeOfTest()
{
	Bool result = true;

	CHECK sizeof(Int16) == 2U;
	CHECK sizeof(Int32) == 4U;
	CHECK sizeof(Int64) == 8U;

	CHECK sizeof(UInt16) == 2U;
	CHECK sizeof(UInt32) == 4U;
	CHECK sizeof(UInt64) == 8U;

	#ifndef CoreTarget64Bits
		CHECK sizeof(Int) == 4U;
		CHECK sizeof(UInt) == 4U;
	#else
		CHECK sizeof(Int) == 8U;
		CHECK sizeof(UInt) == 8U;
	#endif

	return result;
}

Bool ToInt32Test()
{
	Bool result = true;

	CHECK ToInt32(-1) == -1;
	CHECK ToInt32(100) == 100;
	CHECK ToInt32(0x00ffffff) == 0x00ffffff;
	//Would Assert - CHECK ToInt32(0x100000000) == 0x100000000;

	return result;
}

Bool ToUInt32Test()
{
	Bool result = true;

	//Would Assert - CHECK ToInt32(-1) == -1;
	CHECK ToUInt32(100) == 100;
	CHECK ToUInt32(0xffffffff) == 0xffffffff;
	//Would Assert - CHECK ToInt32(0x100000000) == 0x100000000;

	return result;
}

Bool TypesTest()
{
	Bool result = true;

	CHECK SizeOfTest();
	CHECK ToInt32Test();
	CHECK ToUInt32Test();

	return result;
}
