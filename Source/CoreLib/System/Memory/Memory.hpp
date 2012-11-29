#pragma once
#include "../../Types.hpp"

namespace Core
{
	namespace System
	{
		class Memory
		{
			public:
			static void* Alloc(UInt32 bytes);
			static void Free(void* pMemory);
		};
	}
}
