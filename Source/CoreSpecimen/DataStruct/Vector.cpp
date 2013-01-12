#include "../Core.hpp"
#include "Counter.hpp"

using namespace Core;
using namespace DataStruct;

Bool ConstructEmptyTest()
{
	Counter::Clear();

	Bool Result;
	Vector<Counter> Vec;

	Result = Vec.GetCapacity() == 0 && Vec.GetLength() == 0;
	Result = Result && Counter::Assert(0U, 0U, 0U, 0U);

	return Result;
}

Bool ConstructCapacityTest()
{
	Counter::Clear();

	Bool Result;
	UInt Capacity = 10U;
	Vector<Counter> Vec(Capacity);

	Result = Vec.GetCapacity() == Capacity && Vec.GetLength() == 0;
	Result = Result && Counter::Assert(0U, 0U, 0U, 0U);

	return Result;
}

Bool AddTest()
{
	Bool Result = true;
	Vector<Counter> Vec;
	Counter c1, c2, c3;

	Counter::Clear();

	Vec.Add(c1);
	Result = Result && Vec.GetCapacity() == 2U && Vec.GetLength() == 1U;
	Result = Result && Counter::Assert(0U, 1U, 0U, 0U);
	Result = Result && Vec[0U].ID == 1U;

	Vec.Add(c2);
	Result = Result && Vec.GetCapacity() == 2U && Vec.GetLength() == 2U;
	Result = Result && Counter::Assert(0U, 2U, 0U, 0U);
	Result = Result && Vec[1U].ID == 2U;

	Vec.Add(c3);
	Result = Result && Vec.GetCapacity() == 4U && Vec.GetLength() == 3U;
	Result = Result && Counter::Assert(0U, 5U, 0U, 2U);
	Result = Result && Vec[2U].ID == 3U;

	return Result;
}

Bool InsertTest()
{
	Bool Result = true;
	Vector<Counter> Vec;
	Counter c1, c2, c3, c4;

	Counter::Clear();
	Vec.Insert(100U, c1);
	Result = Result && Vec.GetCapacity() == 2U && Vec.GetLength() == 1U;
	Result = Result && Counter::Assert(0U, 1U, 0U, 0U);
	Result = Result && Vec[0U].ID == 1U;

	Counter::Clear();
	Vec.Insert(100U, c2);
	Result = Result && Vec.GetCapacity() == 2U && Vec.GetLength() == 2U;
	Result = Result && Counter::Assert(0U, 1U, 0U, 0U);
	Result = Result && Vec[1U].ID == 2U;

	Counter::Clear();
	Vec.Insert(0U, c3);
	Result = Result && Vec.GetCapacity() == 4U && Vec.GetLength() == 3U;
	Result = Result && Counter::Assert(0U, 5U, 0U, 3U);
	Result = Result && Vec[0U].ID == 3U;
	Result = Result && Vec[1U].ID == 1U;
	Result = Result && Vec[2U].ID == 2U;

	Counter::Clear();
	Vec.Insert(1U, c4);
	Result = Result && Vec.GetCapacity() == 4U && Vec.GetLength() == 4U;
	Result = Result && Counter::Assert(0U, 3U, 0U, 1U);
	Result = Result && Vec[0U].ID == 3U;
	Result = Result && Vec[1U].ID == 4U;
	Result = Result && Vec[2U].ID == 1U;
	Result = Result && Vec[3U].ID == 2U;

	return Result;
}

Bool DeleteTest()
{
	Bool Result = true;
	Vector<Counter> Vec;
	Counter c1, c2, c3, c4;

	Vec.Add(c1);
	Vec.Add(c2);
	Vec.Add(c3);
	Vec.Add(c4);

	Counter::Clear();
	Vec.Remove(100U);
	Result = Result && Vec.GetCapacity() == 4U && Vec.GetLength() == 3U;
	Result = Result && Counter::Assert(0U, 0U, 0U, 1U);
	Result = Result && Vec[0U].ID == 1U;
	Result = Result && Vec[1U].ID == 2U;
	Result = Result && Vec[2U].ID == 3U;

	Counter::Clear();
	Vec.Remove(1U);
	Result = Result && Vec.GetCapacity() == 4U && Vec.GetLength() == 2U;
	Result = Result && Counter::Assert(0U, 1U, 0U, 1U);
	Result = Result && Vec[0U].ID == 1U;
	Result = Result && Vec[1U].ID == 3U;

	Counter::Clear();
	Vec.Remove(0U);
	Result = Result && Vec.GetCapacity() == 4U && Vec.GetLength() == 1U;
	Result = Result && Counter::Assert(0U, 1U, 0U, 1U);
	Result = Result && Vec[0U].ID == 3U;

	Counter::Clear();
	Vec.Remove(0U);
	Result = Result && Vec.GetCapacity() == 4U && Vec.GetLength() == 0U;
	Result = Result && Counter::Assert(0U, 0U, 0U, 1U);

	return Result;
}

Bool ConstructCopyTest()
{
	Bool Result = true;
	Vector<Counter> v1;
	Counter c1, c2, c3, c4;

	v1.Add(c1);
	v1.Add(c2);

	Counter::Clear();
	Vector<Counter> v2(v1);
	Result = Result && v2.GetCapacity() == 2U && v2.GetLength() == 2U;
	Result = Result && Counter::Assert(0U, 2U, 0U, 0U);
	Result = Result && v2[0U].ID == 1U;
	Result = Result && v2[1U].ID == 2U;

	Vector<Counter> v3;
	Counter::Clear();
	Vector<Counter> v4(v3);
	Result = Result && v4.GetCapacity() == 0U && v4.GetLength() == 0U;
	Result = Result && Counter::Assert(0U, 0U, 0U, 0U);

	return Result;
}

Bool ConstructEqualTest()
{
	Bool Result = true;
	Vector<Counter> v1;
	Counter c1, c2, c3, c4;

	v1.Add(c1);
	v1.Add(c2);

	Counter::Clear();
	Vector<Counter> v2 = v1;
	Result = Result && v2.GetCapacity() == 2U && v2.GetLength() == 2U;
	Result = Result && Counter::Assert(0U, 2U, 0U, 0U);
	Result = Result && v2[0U].ID == 1U;
	Result = Result && v2[1U].ID == 2U;

	Counter::Clear();
	v2 = v2;
	Result = Result && v2.GetCapacity() == 2U && v2.GetLength() == 2U;
	Result = Result && Counter::Assert(0U, 0U, 0U, 0U);

	Vector<Counter> v3;
	v3.Add(c3);
	v3.Add(c4);
	Counter::Clear();
	v2 = v3;
	Result = Result && v2.GetCapacity() == 2U && v2.GetLength() == 2U;
	Result = Result && Counter::Assert(0U, 2U, 0U, 2U);
	Result = Result && v2[0U].ID == 3U;
	Result = Result && v2[1U].ID == 4U;

	return Result;
}

Bool ReserveTest()
{
	Bool Result;
	UInt Capacity = 10U;
	Vector<Counter> Vec;

	Counter::Clear();
	Vec.Reserve(Capacity);
	Result = Vec.GetCapacity() == Capacity && Vec.GetLength() == 0;
	Result = Result && Counter::Assert(0U, 0U, 0U, 0U);

	return Result;
}

Bool ShrinkTest()
{
	Bool Result = true;
	Vector<Counter> Vec;
	Counter c1, c2, c3;

	Vec.Add(c1);
	Vec.Add(c2);
	Vec.Add(c3);

	Counter::Clear();
	Vec.Shrink();
	Result = Vec.GetCapacity() == 3U && Vec.GetLength() == 3U;
	Result = Result && Counter::Assert(0U, 3U, 0U, 3U);
	Result = Result && Vec[0U].ID == 1U;
	Result = Result && Vec[1U].ID == 2U;
	Result = Result && Vec[2U].ID == 3U;

	return Result;
}

Bool ClearTest()
{
	Bool Result = true;
	Vector<Counter> Vec;
	Counter c1, c2, c3;

	Vec.Add(c1);
	Vec.Add(c2);
	Vec.Add(c3);

	Counter::Clear();
	Vec.Clear();
	Result = Vec.GetCapacity() == 4U && Vec.GetLength() == 0U;
	Result = Result && Counter::Assert(0U, 0U, 0U, 3U);

	return Result;
}

Bool FreeTest()
{
	Bool Result = true;
	Vector<Counter> Vec;
	Counter c1, c2, c3;

	Vec.Add(c1);
	Vec.Add(c2);
	Vec.Add(c3);

	Counter::Clear();
	Vec.Free();
	Result = Vec.GetCapacity() == 0U && Vec.GetLength() == 0U;
	Result = Result && Counter::Assert(0U, 0U, 0U, 3U);

	return Result;
}

Bool BeginEndTest()
{
	Bool Result = true;
	Vector<Counter> Vec;
	Counter c[3] = {Counter(), Counter(), Counter()};
	UInt i = 0;

	Vec.Add(c[0]);
	Vec.Add(c[1]);
	Vec.Add(c[2]);

	Counter::Clear();

	for(auto it = Vec.Begin(); it < Vec.End(); ++i, ++it)
		Result = Result && it->ID == c[i].ID;

	Result = Vec.GetCapacity() == 4U && Vec.GetLength() == 3U;
	Result = Result && Counter::Assert(0U, 0U, 0U, 0U);

	return Result;
}

Bool VectorTest()
{
	Bool Result = true;

	Result = Result && ConstructEmptyTest();
	Result = Result && ConstructCapacityTest();

	Result = Result && AddTest();
	Result = Result && InsertTest();
	Result = Result && DeleteTest();

	Result = Result && ConstructCopyTest();
	Result = Result && ConstructEqualTest();

	Result = Result && ReserveTest();
	Result = Result && ShrinkTest();
	Result = Result && ClearTest();
	Result = Result && FreeTest();

	Result = Result && BeginEndTest();

	return Result;
}
