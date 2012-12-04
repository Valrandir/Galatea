#include <stdlib.h>
#include "Memory.hpp"

namespace Core
{
	namespace System
	{
		namespace Memory
		{
			VoidPtr Alloc(UInt32 bytes)
			{
				return malloc(bytes);
			}

			void Free(VoidPtr pMemory)
			{
				free(pMemory);
			}
		}
	}
}
