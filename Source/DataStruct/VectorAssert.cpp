#include "../Types.hpp"
#include "../Assert/Assert.hpp"

namespace Galatea
{
	namespace DataStruct
	{
		void AssertSourceTarget(VoidPtr const source, VoidPtr const target)
		{
			ASSERT_PARAMETER(source);
			ASSERT_PARAMETER(target);
		}

		void AssertTarget(VoidPtr const target)
		{
			ASSERT_PARAMETER(target);
		}

		void AssertBeginEnd(VoidPtr const begin, VoidPtr const end)
		{
			ASSERT_PARAMETER(begin);
			ASSERT_PARAMETER(end);
			ASSERT(begin <= end);
		}

		void AssertVectorIsEmpty(VoidPtr const vector)
		{
			ASSERT_MSG(vector, Text("The Vector is empty."));
		}

		void AssertRange(UInt offset, UInt length)
		{
			ASSERT_RANGE(offset >= 0U && offset < length);
		}
	}
}
