#pragma once
#include "../../Types.hpp"

namespace Core
{
	namespace System
	{
		namespace Memory
		{
			VoidPtr Alloc(UInt Bytes);
			void Free(VoidPtr MemoryPtr);
			void Copy(VoidPtr Source, VoidPtr Target, UInt Size);
			void Move(VoidPtr Source, VoidPtr Target, UInt Size);
		};
	}
}
