#include "Core.hpp"

using namespace Core;

Bool TypesTest()
{
	Bool result = true;

	ASSERT sizeof(Int16) == 2U;
	ASSERT sizeof(Int32) == 4U;
	ASSERT sizeof(Int64) == 8U;

	ASSERT sizeof(UInt16) == 2U;
	ASSERT sizeof(UInt32) == 4U;
	ASSERT sizeof(UInt64) == 8U;

	#ifndef CoreTarget64Bits
		ASSERT sizeof(Int) == 4U;
		ASSERT sizeof(UInt) == 4U;
	#else
		ASSERT sizeof(Int) == 8U;
		ASSERT sizeof(UInt) == 8U;
	#endif

	return result;
}
