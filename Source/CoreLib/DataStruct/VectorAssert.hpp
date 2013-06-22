#pragma once
#include "../Types.hpp"

namespace Core
{
	namespace DataStruct
	{
		void AssertSourceTarget(VoidPtr const source, VoidPtr const target);
		void AssertTarget(VoidPtr const target);
		void AssertBeginEnd(VoidPtr const begin, VoidPtr const end);
		void AssertVectorIsEmpty(VoidPtr const vector);
		void AssertRange(UInt offset, UInt length);
	}
}
