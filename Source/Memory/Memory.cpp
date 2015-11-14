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
			ASSERT_PARAMETER(bytes);
			void *ptr = malloc(bytes);
			ASSERT(ptr != 0);
			return ptr;
		}

		void Free(VoidPtr ptr)
		{
			ASSERT_PARAMETER(ptr != NULL);

			if(ptr)
				free(ptr);
		}

		void Copy(VoidPtr source, VoidPtr target, UInt size)
		{
			ASSERT_PARAMETER(source != NULL);
			ASSERT_PARAMETER(target != NULL);

			if(size)
				memcpy(target, source, size);
		}

		void Move(VoidPtr source, VoidPtr target, UInt size)
		{
			ASSERT_PARAMETER(source != NULL);
			ASSERT_PARAMETER(target != NULL);

			if(size)
				memmove(target, source, size);
		}
	}
}
