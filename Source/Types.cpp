#include "Types.hpp"
#include "Assert/Assert.hpp"

namespace Galatea
{
	Int32 ToInt32(Int64 value)
	{
		if(value != -1)
			ASSERT(value >> 32 == 0);
		return value & 0xffffffff;
	}

	UInt32 ToUInt32(UInt64 value)
	{
		ASSERT(value >> 32 == 0U);
		return value & 0xffffffff;
	}

	Int ToInt(Int64 value)
	{
		#ifdef GALATEA_BUILD_X64
			return value;
		#else
			return ToInt32(value);
		#endif
	}

	UInt ToUInt(UInt64 value)
	{
		#ifdef GALATEA_BUILD_X64
			return value;
		#else
			return ToUInt32(value);
		#endif
	}

	Bool WithinInt32Limit(Int value)
	{
		#ifdef GALATEA_BUILD_X64
			if(value & 0x8000000000000000)
				value = ~value;
			value &= 0xffffffff00000000;
			return value == 0;
		#else
			return true;
		#endif
	}

	Bool WithinUInt32Limit(UInt value)
	{
		#ifdef GALATEA_BUILD_X64
			return (value & 0xffffffff00000000) == 0U;
		#else
			return true;
		#endif
	}
}
