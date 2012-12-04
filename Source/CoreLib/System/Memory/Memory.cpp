#include <stdlib.h>
#include "Memory.hpp"

namespace Core
{
	namespace System
	{
		namespace Memory
		{
			void* Alloc(UInt32 bytes)
			{
				return malloc(bytes);
			}

			void Free(void* pMemory)
			{
				free(pMemory);
			}
		}
	}
}
