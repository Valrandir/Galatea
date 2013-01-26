#define __PLACEMENT_NEW_INLINE
#define _HAS_EXCEPTIONS 0
#include <vector>

#include "../Core.hpp"
#include "Counter.hpp"

using namespace Core;
using std::vector;

Bool StdConstructEmptyTest()
{
	Counter::Clear();

	Bool Result;
	vector<Counter> Vec;

	Result = Vec.capacity() == 0 && Vec.size() == 0;
	Result = Result && Counter::Assert(0U, 1U, 0U, 0U, 0U, 0U);

	return Result;
}

Bool StdConstructCapacityTest()
{
	return true;
}

Bool StdAddTest()
{
	Bool Result = true;
	vector<Counter> Vec;
	Counter c1, c2, c3;

	Counter::Clear();

	Vec.push_back(c1);
	Result = Result && Vec.capacity() == 1U && Vec.size() == 1U;
	Result = Result && Counter::Assert(0U, 1U, 0U, 0U, 0U, 0U);
	Result = Result && Vec[0U].ID == 1U;

	Vec.push_back(c2);
	Result = Result && Vec.capacity() == 2U && Vec.size() == 2U;
	Result = Result && Counter::Assert(0U, 1U, 0U, 0U, 0U, 0U);
	Result = Result && Vec[1U].ID == 2U;

	Vec.push_back(c3);
	Result = Result && Vec.capacity() == 3U && Vec.size() == 3U;
	Result = Result && Counter::Assert(0U, 1U, 0U, 0U, 0U, 0U);
	Result = Result && Vec[2U].ID == 3U;

	return Result;
}

Bool StdInsertTest()
{
	Bool Result = true;
	vector<Counter> Vec;
	Counter c1, c2, c3, c4;

	Counter::Clear();
	Vec.insert(Vec.end(), c1);
	Result = Result && Vec.capacity() == 1U && Vec.size() == 1U;
	Result = Result && Counter::Assert(0U, 1U, 0U, 0U, 0U, 0U);
	Result = Result && Vec[0U].ID == 1U;

	Counter::Clear();
	Vec.insert(Vec.end(), c2);
	Result = Result && Vec.capacity() == 2U && Vec.size() == 2U;
	Result = Result && Counter::Assert(0U, 1U, 0U, 0U, 0U, 0U);
	Result = Result && Vec[1U].ID == 2U;

	Counter::Clear();
	Vec.insert(Vec.begin(), c3);
	Result = Result && Vec.capacity() == 3U && Vec.size() == 3U;
	Result = Result && Counter::Assert(0U, 1U, 0U, 0U, 0U, 0U);
	Result = Result && Vec[0U].ID == 3U;
	Result = Result && Vec[1U].ID == 1U;
	Result = Result && Vec[2U].ID == 2U;

	Counter::Clear();
	Vec.insert(Vec.begin() + 1, c4);
	Result = Result && Vec.capacity() == 4U && Vec.size() == 4U;
	Result = Result && Counter::Assert(0U, 1U, 0U, 0U, 0U, 0U);
	Result = Result && Vec[0U].ID == 3U;
	Result = Result && Vec[1U].ID == 4U;
	Result = Result && Vec[2U].ID == 1U;
	Result = Result && Vec[3U].ID == 2U;

	return Result;
}

Bool StdDeleteTest()
{
	Bool Result = true;
	vector<Counter> Vec;
	Counter c1, c2, c3, c4;

	Vec.push_back(c1);
	Vec.push_back(c2);
	Vec.push_back(c3);
	Vec.push_back(c4);

	Counter::Clear();
	Vec.erase(Vec.end() - 1);
	Result = Result && Vec.capacity() == 4U && Vec.size() == 3U;
	Result = Result && Counter::Assert(0U, 1U, 0U, 0U, 0U, 0U);
	Result = Result && Vec[0U].ID == 1U;
	Result = Result && Vec[1U].ID == 2U;
	Result = Result && Vec[2U].ID == 3U;

	Counter::Clear();
	Vec.erase(Vec.begin() + 1);
	Result = Result && Vec.capacity() == 4U && Vec.size() == 2U;
	Result = Result && Counter::Assert(0U, 1U, 0U, 0U, 0U, 0U);
	Result = Result && Vec[0U].ID == 1U;
	Result = Result && Vec[1U].ID == 3U;

	Counter::Clear();
	Vec.erase(Vec.begin());
	Result = Result && Vec.capacity() == 4U && Vec.size() == 1U;
	Result = Result && Counter::Assert(0U, 1U, 0U, 0U, 0U, 0U);
	Result = Result && Vec[0U].ID == 3U;

	Counter::Clear();
	Vec.erase(Vec.begin());
	Result = Result && Vec.capacity() == 4U && Vec.size() == 0U;
	Result = Result && Counter::Assert(0U, 1U, 0U, 0U, 0U, 0U);

	return Result;
}

Bool StdConstructCopyTest()
{
	Bool Result = true;
	vector<Counter> v1;
	Counter c1, c2, c3, c4;

	v1.push_back(c1);
	v1.push_back(c2);

	Counter::Clear();
	vector<Counter> v2(v1);
	Result = Result && v2.capacity() == 2U && v2.size() == 2U;
	Result = Result && Counter::Assert(0U, 1U, 0U, 0U, 0U, 0U);
	Result = Result && v2[0U].ID == 1U;
	Result = Result && v2[1U].ID == 2U;

	vector<Counter> v3;
	Counter::Clear();
	vector<Counter> v4(v3);
	Result = Result && v4.capacity() == 0U && v4.size() == 0U;
	Result = Result && Counter::Assert(0U, 1U, 0U, 0U, 0U, 0U);

	return Result;
}

Bool StdConstructEqualTest()
{
	Bool Result = true;
	vector<Counter> v1;
	Counter c1, c2, c3, c4;

	v1.push_back(c1);
	v1.push_back(c2);

	Counter::Clear();
	vector<Counter> v2 = v1;
	Result = Result && v2.capacity() == 2U && v2.size() == 2U;
	Result = Result && Counter::Assert(0U, 1U, 0U, 0U, 0U, 0U);
	Result = Result && v2[0U].ID == 1U;
	Result = Result && v2[1U].ID == 2U;

	Counter::Clear();
	v2 = v2;
	Result = Result && v2.capacity() == 2U && v2.size() == 2U;
	Result = Result && Counter::Assert(0U, 1U, 0U, 0U, 0U, 0U);

	vector<Counter> v3;
	v3.push_back(c3);
	v3.push_back(c4);
	Counter::Clear();
	v2 = v3;
	Result = Result && v2.capacity() == 2U && v2.size() == 2U;
	Result = Result && Counter::Assert(0U, 1U, 0U, 0U, 0U, 0U);
	Result = Result && v2[0U].ID == 3U;
	Result = Result && v2[1U].ID == 4U;

	return Result;
}

Bool StdReserveTest()
{
	Bool Result;
	UInt Capacity = 10U;
	vector<Counter> Vec;

	Counter::Clear();
	Vec.reserve(Capacity);
	Result = Vec.capacity() == Capacity && Vec.size() == 0;
	Result = Result && Counter::Assert(0U, 1U, 0U, 0U, 0U, 0U);

	return Result;
}

Bool StdShrinkTest()
{
	Bool Result = true;
	vector<Counter> Vec;
	Counter c1, c2, c3, c4, c5, c6, c7;

	Vec.push_back(c1);
	Vec.push_back(c2);
	Vec.push_back(c3);
	Vec.push_back(c4);
	Vec.push_back(c5);
	Vec.push_back(c6);
	Vec.push_back(c7);

	Counter::Clear();
	Vec.shrink_to_fit();
	Result = Vec.capacity() == 7U && Vec.size() == 7U;
	Result = Result && Counter::Assert(0U, 1U, 0U, 0U, 0U, 0U);
	Result = Result && Vec[0U].ID == 1U;
	Result = Result && Vec[1U].ID == 2U;
	Result = Result && Vec[2U].ID == 3U;

	return Result;
}

Bool StdClearTest()
{
	Bool Result = true;
	vector<Counter> Vec;
	Counter c1, c2, c3;

	Vec.push_back(c1);
	Vec.push_back(c2);
	Vec.push_back(c3);

	Counter::Clear();
	Vec.clear();
	Result = Vec.capacity() == 3U && Vec.size() == 0U;
	Result = Result && Counter::Assert(0U, 1U, 0U, 0U, 0U, 0U);

	return Result;
}

Bool StdFreeTest()
{
	return true;
}

Bool StdBeginEndTest()
{
	Bool Result = true;
	vector<Counter> Vec;
	Counter c[3] = {Counter(), Counter(), Counter()};
	UInt i = 0;

	Vec.push_back(c[0]);
	Vec.push_back(c[1]);
	Vec.push_back(c[2]);

	Counter::Clear();

	for(auto it = Vec.begin(); it < Vec.end(); ++i, ++it)
		Result = Result && it->ID == c[i].ID;

	Result = Vec.capacity() == 3U && Vec.size() == 3U;
	Result = Result && Counter::Assert(0U, 1U, 0U, 0U, 0U, 0U);

	return Result;
}

#include <stdlib.h>

Bool StdVectorTest()
{
	Bool Result = true;

	Result = Result && StdConstructEmptyTest();
	Result = Result && StdConstructCapacityTest();

	Result = Result && StdAddTest();
	Result = Result && StdInsertTest();
	Result = Result && StdDeleteTest();

	Result = Result && StdConstructCopyTest();
	Result = Result && StdConstructEqualTest();

	Result = Result && StdReserveTest();
	Result = Result && StdShrinkTest();
	Result = Result && StdClearTest();
	Result = Result && StdFreeTest();

	Result = Result && StdBeginEndTest();

	return Result;
}
