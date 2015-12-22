#include <string.h>
#include <stdlib.h>
#include "Memory.hpp"
#include "../Assert/Assert.hpp"

namespace Galatea
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
			ASSERT_PARAMETER(ptr != nullptr);

			if(ptr)
				free(ptr);
		}

		void Copy(VoidPtr source, VoidPtr target, UInt size)
		{
			ASSERT_PARAMETER(source != nullptr);
			ASSERT_PARAMETER(target != nullptr);

			if(size)
				memcpy(target, source, size);
		}

		void Move(VoidPtr source, VoidPtr target, UInt size)
		{
			ASSERT_PARAMETER(source != nullptr);
			ASSERT_PARAMETER(target != nullptr);

			if(size)
				memmove(target, source, size);
		}
	}
}
