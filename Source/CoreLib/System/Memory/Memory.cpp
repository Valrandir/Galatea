#include <string.h>
#include <stdlib.h>
#include "Memory.hpp"

namespace Core
{
	namespace System
	{
		namespace Memory
		{
			VoidPtr Alloc(UInt Bytes)
			{
				return malloc(Bytes);
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
