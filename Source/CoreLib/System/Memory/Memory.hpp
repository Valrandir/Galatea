#pragma once
#include "../../Types.hpp"

namespace Core
{
	namespace System
	{
		namespace Memory
		{
			void* Alloc(UInt32 bytes);
			void Free(void* pMemory);
		};
	}
}
