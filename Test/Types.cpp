#include "Galatea.hpp"

using namespace Galatea;

Bool SizeOfTest()
{
	Bool result = true;

	CHECK sizeof(Int16) == 2U;
	CHECK sizeof(Int32) == 4U;
	CHECK sizeof(Int64) == 8U;

	CHECK sizeof(UInt16) == 2U;
	CHECK sizeof(UInt32) == 4U;
	CHECK sizeof(UInt64) == 8U;

	#ifndef GALATEA_BUILD_X64
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
	CHECK_ASSERT(ToInt32(0x100000000));

	return result;
}

Bool ToUInt32Test()
{
	Bool result = true;

	CHECK ToUInt32(100) == 100;
	CHECK ToUInt32(0xffffffff) == 0xffffffff;
	CHECK_ASSERT(ToInt32(0x100000000));

	return result;
}

Bool WithinInt32LimitTest()
{
	Bool result = true;

	CHECK WithinInt32Limit(0);
	CHECK WithinInt32Limit(100);
	CHECK WithinInt32Limit(-1);
	CHECK WithinInt32Limit(-100);
	CHECK WithinInt32Limit(0x7fffffff);
	CHECK WithinInt32Limit(0x80000000);

	#if defined(GALATEA_BUILD_X64)
		CHECK WithinInt32Limit(0x7fffffff0) == false;
		CHECK WithinInt32Limit(0x100000000000) == false;
		CHECK WithinInt32Limit(0x8000000000000000) == false;
	#endif

	return result;
}

Bool WithinUInt32LimitTest()
{
	Bool result = true;

	CHECK WithinInt32Limit(0);
	CHECK WithinInt32Limit(100);
	CHECK WithinInt32Limit(0x7fffffff);
	CHECK WithinInt32Limit(0x80000000);

	#if defined(GALATEA_BUILD_X64)
		CHECK WithinInt32Limit(0x100000000000) == false;
		CHECK WithinInt32Limit(0x8000000000000000) == false;
	#endif

	return result;
}

Bool TypesTest()
{
	Bool result = true;

	CHECK SizeOfTest();
	CHECK ToInt32Test();
	CHECK ToUInt32Test();
	CHECK WithinInt32LimitTest();
	CHECK WithinUInt32LimitTest();

	return result;
}
