#include <stdlib.h>
#include "Memory.hpp"

namespace Core
{
	namespace System
	{
		void* Memory::Alloc(UInt32 bytes)
		{
			return malloc(bytes);
		}

		void Memory::Free(void* pMemory)
		{
			free(pMemory);
		}
	}
}
