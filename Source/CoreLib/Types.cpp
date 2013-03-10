#include "Types.hpp"
#include "Assert/Assert.hpp"

namespace Core
{
	Int32 ToInt32(Int64 value)
	{
		if(value != -1)
			Assert(value >> 32 == 0);
		return value & 0xffffffff;
	}

	UInt32 ToUInt32(UInt64 value)
	{
		Assert(value >> 32 == 0U);
		return value & 0xffffffff;
	}
}
