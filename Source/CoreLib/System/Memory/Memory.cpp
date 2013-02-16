#include <string.h>
#include <stdlib.h>
#include "Memory.hpp"
#include "../Assert/Assert.hpp"

namespace Core
{
	namespace System
	{
		namespace Memory
		{
			VoidPtr Alloc(UInt Bytes)
			{
				void *ptr = malloc(Bytes);
				Assert(ptr != 0);
				return ptr;
			}

			void Free(VoidPtr MemoryPtr)
			{
				free(MemoryPtr);
			}

			void Copy(VoidPtr Source, VoidPtr Target, UInt Size)
			{
				memcpy(Target, Source, Size);
			}

			void Move(VoidPtr Source, VoidPtr Target, UInt Size)
			{
				memmove(Target, Source, Size);
			}
		}
	}
}
