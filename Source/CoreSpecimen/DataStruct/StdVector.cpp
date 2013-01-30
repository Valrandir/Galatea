#define __PLACEMENT_NEW_INLINE
#define _HAS_EXCEPTIONS 0
#include <vector>

#include "../Core.hpp"
#include "Counter.hpp"

using namespace Core;
using std::vector;

#define ASSERT result = result &&  

Bool StdConstructEmptyTest()
{
	Bool result = true;

	Counter::Clear();
	vector<Counter> v;

	result = v.capacity() == 0 && v.size() == 0;

	return result;
}

Bool StdConstructCapacityTest()
{
	return true;
}

Bool StdAddTest()
{
	Bool result = true;
	vector<Counter> v;
	Counter c1, c2, c3;

	Counter::Clear();

	v.push_back(c1);
	ASSERT v.capacity() == 1U && v.size() == 1U;
	ASSERT v[0U].ID == 1U;

	v.push_back(c2);
	ASSERT v.capacity() == 2U && v.size() == 2U;
	ASSERT v[1U].ID == 2U;

	v.push_back(c3);
	ASSERT v.capacity() == 3U && v.size() == 3U;
	ASSERT v[2U].ID == 3U;

	return result;
}

Bool StdInsertTest()
{
	Bool result = true;
	vector<Counter> v;
	Counter c1, c2, c3, c4;

	Counter::Clear();
	v.insert(v.end(), c1);
	ASSERT v.capacity() == 1U && v.size() == 1U;
	ASSERT v[0U].ID == 1U;

	Counter::Clear();
	v.insert(v.end(), c2);
	ASSERT v.capacity() == 2U && v.size() == 2U;
	ASSERT v[1U].ID == 2U;

	Counter::Clear();
	v.insert(v.begin(), c3);
	ASSERT v.capacity() == 3U && v.size() == 3U;
	ASSERT v[0U].ID == 3U;
	ASSERT v[1U].ID == 1U;
	ASSERT v[2U].ID == 2U;

	Counter::Clear();
	v.insert(v.begin() + 1, c4);
	ASSERT v.capacity() == 4U && v.size() == 4U;
	ASSERT v[0U].ID == 3U;
	ASSERT v[1U].ID == 4U;
	ASSERT v[2U].ID == 1U;
	ASSERT v[3U].ID == 2U;

	return result;
}

Bool StdRemoveTest()
{
	Bool result = true;
	vector<Counter> v;
	Counter c1, c2, c3, c4;

	v.push_back(c1);
	v.push_back(c2);
	v.push_back(c3);
	v.push_back(c4);

	Counter::Clear();
	v.erase(v.end() - 1);
	ASSERT v.capacity() == 4U && v.size() == 3U;
	ASSERT v[0U].ID == 1U;
	ASSERT v[1U].ID == 2U;
	ASSERT v[2U].ID == 3U;

	Counter::Clear();
	v.erase(v.begin() + 1);
	ASSERT v.capacity() == 4U && v.size() == 2U;
	ASSERT v[0U].ID == 1U;
	ASSERT v[1U].ID == 3U;

	Counter::Clear();
	v.erase(v.begin());
	ASSERT v.capacity() == 4U && v.size() == 1U;
	ASSERT v[0U].ID == 3U;

	Counter::Clear();
	v.erase(v.begin());
	ASSERT v.capacity() == 4U && v.size() == 0U;

	return result;
}

Bool StdConstructCopyTest()
{
	Bool result = true;
	vector<Counter> v1;
	Counter c1, c2, c3, c4;

	v1.push_back(c1);
	v1.push_back(c2);

	Counter::Clear();
	vector<Counter> v2(v1);
	ASSERT v2.capacity() == 2U && v2.size() == 2U;
	ASSERT v2[0U].ID == 1U;
	ASSERT v2[1U].ID == 2U;

	vector<Counter> v3;
	Counter::Clear();
	vector<Counter> v4(v3);
	ASSERT v4.capacity() == 0U && v4.size() == 0U;

	return result;
}

Bool StdConstructEqualTest()
{
	Bool result = true;
	vector<Counter> v1;
	Counter c1, c2, c3, c4;

	v1.push_back(c1);
	v1.push_back(c2);

	Counter::Clear();
	vector<Counter> v2 = v1;
	ASSERT v2.capacity() == 2U && v2.size() == 2U;
	ASSERT v2[0U].ID == 1U;
	ASSERT v2[1U].ID == 2U;

	Counter::Clear();
	v2 = v2;
	ASSERT v2.capacity() == 2U && v2.size() == 2U;

	vector<Counter> v3;
	v3.push_back(c3);
	v3.push_back(c4);
	Counter::Clear();
	v2 = v3;
	ASSERT v2.capacity() == 2U && v2.size() == 2U;
	ASSERT v2[0U].ID == 3U;
	ASSERT v2[1U].ID == 4U;

	return result;
}

Bool StdReserveTest()
{
	Bool result;
	UInt Capacity = 10U;
	vector<Counter> v;

	Counter::Clear();
	v.reserve(Capacity);
	result = v.capacity() == Capacity && v.size() == 0;

	return result;
}

Bool StdShrinkTest()
{
	Bool result = true;
	vector<Counter> v;
	Counter c1, c2, c3, c4, c5, c6, c7;

	v.push_back(c1);
	v.push_back(c2);
	v.push_back(c3);
	v.push_back(c4);
	v.push_back(c5);
	v.push_back(c6);
	v.push_back(c7);

	Counter::Clear();
	v.shrink_to_fit();
	result = v.capacity() == 7U && v.size() == 7U;
	ASSERT v[0U].ID == 1U;
	ASSERT v[1U].ID == 2U;
	ASSERT v[2U].ID == 3U;

	return result;
}

Bool StdClearTest()
{
	Bool result = true;
	vector<Counter> v;
	Counter c1, c2, c3;

	v.push_back(c1);
	v.push_back(c2);
	v.push_back(c3);

	Counter::Clear();
	v.clear();
	result = v.capacity() == 3U && v.size() == 0U;

	return result;
}

Bool StdFreeTest()
{
	return true;
}

Bool StdBeginEndTest()
{
	Bool result = true;
	vector<Counter> v;
	Counter c[3] = {Counter(), Counter(), Counter()};
	UInt i = 0;

	v.push_back(c[0]);
	v.push_back(c[1]);
	v.push_back(c[2]);

	Counter::Clear();

	for(auto it = v.begin(); it < v.end(); ++i, ++it)
		ASSERT it->ID == c[i].ID;

	result = v.capacity() == 3U && v.size() == 3U;

	return result;
}

Bool StdVectorTest()
{
	Bool result = true;

	ASSERT StdConstructEmptyTest();
	ASSERT StdConstructCapacityTest();

	ASSERT StdAddTest();
	ASSERT StdInsertTest();
	ASSERT StdRemoveTest();

	ASSERT StdConstructCopyTest();
	ASSERT StdConstructEqualTest();

	ASSERT StdReserveTest();
	ASSERT StdShrinkTest();
	ASSERT StdClearTest();
	ASSERT StdFreeTest();

	ASSERT StdBeginEndTest();

	return result;
}