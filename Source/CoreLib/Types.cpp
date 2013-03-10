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

	Int ToInt(Int64 value)
	{
		#ifdef CoreTarget64Bits
			return value;
		#else
			return ToInt32(value);
		#endif
	}

	UInt ToUInt(UInt64 value)
	{
		#ifdef CoreTarget64Bits
			return value;
		#else
			return ToUInt32(value);
		#endif
	}
}
