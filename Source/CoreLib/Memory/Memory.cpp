#include <string.h>
#include <stdlib.h>
#include "Memory.hpp"
#include "../Assert/Assert.hpp"

namespace Core
{
	namespace Memory
	{
		VoidPtr Alloc(UInt bytes)
		{
			void *ptr = malloc(bytes);
			ASSERT(ptr != 0);
			return ptr;
		}

		void Free(VoidPtr ptr)
		{
			free(ptr);
		}

		void Copy(VoidPtr source, VoidPtr target, UInt size)
		{
			memcpy(target, source, size);
		}

		void Move(VoidPtr source, VoidPtr target, UInt size)
		{
			memmove(target, source, size);
		}
	}
}
