#pragma once
#include "../Types.hpp"

namespace Core
{
	namespace Memory
	{
		VoidPtr Alloc(UInt bytes);
		void Free(VoidPtr ptr);
		void Copy(VoidPtr source, VoidPtr target, UInt size);
		void Move(VoidPtr source, VoidPtr target, UInt size);
	};
}
