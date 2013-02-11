#include "Core.hpp"

using namespace Core;

Bool TypesTest()
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
