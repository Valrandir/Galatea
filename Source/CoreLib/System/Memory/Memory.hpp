#pragma once
#include "../../Types.hpp"

namespace Core
{
	namespace System
	{
		namespace Memory
		{
			VoidPtr Alloc(UInt32 bytes);
			void Free(VoidPtr pMemory);
		};
	}
}
