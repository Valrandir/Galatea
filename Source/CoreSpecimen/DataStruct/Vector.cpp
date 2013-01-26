#include "../Core.hpp"
#include "Counter.hpp"

using namespace Core;
using namespace DataStruct;

#define ASSERT result = result && 
typedef Vector<Counter> VCntr;

void AddFiveElements(VCntr &vector)
{
	Counter::Clear();
	int const n = 5;
	Counter c[5];
	for(int i = 0; i < n; ++i)
		vector.Add(c[i]);
}

VCntr GetRValue(VCntr& vector)
{
	//Call copy constructor and return an r-value
	return vector;
}

Bool AssertCapLen(VCntr& vector, UInt capacity, UInt length)
{
	return vector.GetCapacity() == capacity && vector.GetLength() == length;
}

Bool AssertBeginEndNull(VCntr& v)
{
	Bool result = true;
	VCntr const & cv = v;

	ASSERT v.Begin() == NULL && v.End() == v.Begin() + 1;
	ASSERT cv.Begin() == NULL && cv.End() == cv.Begin() + 1;

	return result;
}

Bool AssertBeginEndNotNull(VCntr& v)
{
	Bool result = true;
	VCntr const & cv = v;

	ASSERT v.Begin() && v.End() == v.Begin() + 1;
	ASSERT cv.Begin() && cv.End() == cv.Begin() + 1;

	return result;
}

Bool CTorEmptyTest()
{
	Counter::Clear();

	Bool result = true;
	VCntr vc;

	ASSERT Counter::Assert(0U, 0U, 0U, 0U, 0U, 0U);
	ASSERT AssertCapLen(vc, 0U, 0U);
	ASSERT vc.GetElementType() == VCntr::RawCopyDisabled;
	ASSERT AssertBeginEndNull(vc);

	return result;
}

Bool CTorRawCopyTest()
{
	Bool result = true;
	VCntr vc(VCntr::RawCopyEnabled);

	ASSERT vc.GetElementType() == VCntr::RawCopyEnabled;

	return result;
}

Bool CTorCapacityTest()
{
	Counter::Clear();

	Bool result = true;
	VCntr vc(10U);
	VCntr const & cvc = vc;

	ASSERT Counter::Assert(0U, 0U, 0U, 0U, 0U, 0U);
	ASSERT AssertCapLen(vc, 10U, 0U);
	ASSERT AssertBeginEndNotNull(vc);

	return result;
}

Bool CTorCopyTest()
{
	Bool result = true;

	//Copy empty vector
	VCntr vcEmpty;
	Counter::Clear();
	VCntr vc1(vcEmpty);
	ASSERT Counter::Assert(0U, 0U, 0U, 0U, 0U, 0U);
	ASSERT AssertCapLen(vc1, 10U, 0U);

	//Copy Vector with capacity 5 and no elements
	VCntr vcCap5(5U);
	Counter::Clear();
	VCntr vc2(vcCap5);
	ASSERT Counter::Assert(0U, 0U, 0U, 0U, 0U, 0U);
	ASSERT AssertCapLen(vc2, 5U, 0U);

	//Copy Vector with 5 elements
	VCntr vcWith5(5U);
	AddFiveElements(vcWith5);
	Counter::Clear();
	VCntr vc3(vcWith5);
	ASSERT Counter::Assert(0U, 5U, 0U, 0U, 0U, 0U);
	ASSERT AssertCapLen(vc3, 5U, 5U);

	//Copy RawCopyEnabled vector
	VCntr vcRaw(VCntr::RawCopyEnabled);
	VCntr vc4(vcRaw);
	ASSERT vc4.GetElementType() == VCntr::RawCopyEnabled;

	return result;
}

Bool CTorMoveTest()
{
	Bool result = true;

	//Move empty vector
	VCntr vcEmpty;
	Counter::Clear();
	VCntr vc1(GetRValue(vcEmpty));
	ASSERT Counter::Assert(0U, 1U, 0U, 0U, 0U, 1U);
	ASSERT AssertCapLen(vc1, 0U, 0U);
	ASSERT AssertBeginEndNull(vc1);

	//Move Vector with capacity 5 and no elements
	VCntr vcCap5(5U);
	Counter::Clear();
	VCntr vc2(GetRValue(vcCap5));
	ASSERT Counter::Assert(0U, 1U, 0U, 0U, 0U, 1U);
	ASSERT AssertCapLen(vc2, 5U, 0U);
	ASSERT AssertBeginEndNotNull(vc2);

	//Move Vector with 5 elements
	VCntr vcWith5(5U);
	AddFiveElements(vcWith5);
	Counter::Clear();
	VCntr vc3(vcWith5);
	ASSERT Counter::Assert(0U, 5U, 0U, 0U, 0U, 0U);
	ASSERT AssertCapLen(vc3, 5U, 5U);
	ASSERT AssertBeginEndNotNull(vc3);
	ASSERT AssertCapLen(vcWith5, 0U, 0U);
	ASSERT AssertBeginEndNull(vcWith5);

	//Move RawCopyEnabled vector
	VCntr vcRaw(VCntr::RawCopyEnabled);
	VCntr vc4(vcRaw);
	ASSERT vc4.GetElementType() == VCntr::RawCopyEnabled;

	return result;
}

Bool VectorTest()
{
	Bool result = true;

	ASSERT CTorEmptyTest();
	ASSERT CTorRawCopyTest();
	ASSERT CTorCapacityTest();
	ASSERT CTorCopyTest();
	ASSERT CTorMoveTest();

	return result;
}


/*
#include "../Core.hpp"
#include "Counter.hpp"

using namespace Core;
using namespace DataStruct;

Bool ConstructEmptyTest()
{
	Counter::Clear();

	Bool result;
	Vector<Counter> Vec;

	result = Vec.GetCapacity() == 0 && Vec.GetLength() == 0;
	result = result && Counter::Assert(0U, 0U, 0U, 0U, 0U, 0U);

	return result;
}

Bool ConstructCapacityTest()
{
	Counter::Clear();

	Bool result;
	UInt Capacity = 10U;
	Vector<Counter> Vec(Capacity);

	result = Vec.GetCapacity() == Capacity && Vec.GetLength() == 0;
	result = result && Counter::Assert(0U, 0U, 0U, 0U, 0U, 0U);

	return result;
}

Bool AddTest()
{
	Bool result = true;
	Vector<Counter> Vec;
	Counter c1, c2, c3;

	Counter::Clear();
	Vec.Add(c1);
	result = result && Vec.GetCapacity() == 2U && Vec.GetLength() == 1U;
	result = result && Counter::Assert(0U, 1U, 0U, 0U, 0U, 0U);
	result = result && Vec[0U].ID == 1U;

	Counter::Clear();
	Vec.Add(c2);
	result = result && Vec.GetCapacity() == 2U && Vec.GetLength() == 2U;
	result = result && Counter::Assert(0U, 1U, 0U, 0U, 0U, 0U);
	result = result && Vec[1U].ID == 2U;

	Counter::Clear();
	Vec.Add(c3);
	result = result && Vec.GetCapacity() == 4U && Vec.GetLength() == 3U;
	result = result && Counter::Assert(0U, 1U, 2U, 0U, 0U, 2U);
	result = result && Vec[2U].ID == 3U;

	return result;
}

Bool InsertTest()
{
	Bool result = true;
	Vector<Counter> Vec;
	Counter c1, c2, c3, c4;

	Counter::Clear();
	Vec.Insert(100U, c1);
	result = result && Vec.GetCapacity() == 2U && Vec.GetLength() == 1U;
	result = result && Counter::Assert(0U, 1U, 0U, 0U, 0U, 0U);
	result = result && Vec[0U].ID == 1U;

	Counter::Clear();
	Vec.Insert(100U, c2);
	result = result && Vec.GetCapacity() == 2U && Vec.GetLength() == 2U;
	result = result && Counter::Assert(0U, 1U, 0U, 0U, 0U, 0U);
	result = result && Vec[1U].ID == 2U;

	Counter::Clear();
	Vec.Insert(0U, c3);
	result = result && Vec.GetCapacity() == 4U && Vec.GetLength() == 3U;
	result = result && Counter::Assert(0U, 1U, 4U, 0U, 0U, 2U);
	result = result && Vec[0U].ID == 3U;
	result = result && Vec[1U].ID == 1U;
	result = result && Vec[2U].ID == 2U;

	Counter::Clear();
	Vec.Insert(1U, c4);
	result = result && Vec.GetCapacity() == 4U && Vec.GetLength() == 4U;
	result = result && Counter::Assert(0U, 1U, 2U, 0U, 0U, 0U);
	result = result && Vec[0U].ID == 3U;
	result = result && Vec[1U].ID == 4U;
	result = result && Vec[2U].ID == 1U;
	result = result && Vec[3U].ID == 2U;

	return result;
}

Bool DeleteTest()
{
	Bool result = true;
	Vector<Counter> Vec;
	Counter c1, c2, c3, c4;

	Vec.Add(c1);
	Vec.Add(c2);
	Vec.Add(c3);
	Vec.Add(c4);

	Counter::Clear();
	Vec.Remove(100U);
	result = result && Vec.GetCapacity() == 4U && Vec.GetLength() == 3U;
	result = result && Counter::Assert(0U, 0U, 0U, 0U, 0U, 1U);
	result = result && Vec[0U].ID == 1U;
	result = result && Vec[1U].ID == 2U;
	result = result && Vec[2U].ID == 3U;

	Counter::Clear();
	Vec.Remove(1U);
	result = result && Vec.GetCapacity() == 4U && Vec.GetLength() == 2U;
	result = result && Counter::Assert(0U, 0U, 1U, 0U, 0U, 2U);
	result = result && Vec[0U].ID == 1U;
	result = result && Vec[1U].ID == 3U;

	Counter::Clear();
	Vec.Remove(0U);
	result = result && Vec.GetCapacity() == 4U && Vec.GetLength() == 1U;
	result = result && Counter::Assert(0U, 0U, 1U, 0U, 0U, 2U);
	result = result && Vec[0U].ID == 3U;

	Counter::Clear();
	Vec.Remove(0U);
	result = result && Vec.GetCapacity() == 4U && Vec.GetLength() == 0U;
	result = result && Counter::Assert(0U, 0U, 0U, 0U, 0U, 1U);

	return result;
}

Bool ConstructCopyTest()
{
	Bool result = true;
	Vector<Counter> v1;
	Counter c1, c2, c3, c4;

	v1.Add(c1);
	v1.Add(c2);

	Counter::Clear();
	Vector<Counter> v2(v1);
	result = result && v2.GetCapacity() == 2U && v2.GetLength() == 2U;
	result = result && Counter::Assert(0U, 2U, 0U, 0U, 0U, 0U);
	result = result && v2[0U].ID == 1U;
	result = result && v2[1U].ID == 2U;

	Vector<Counter> v3;
	Counter::Clear();
	Vector<Counter> v4(v3);
	result = result && v4.GetCapacity() == 0U && v4.GetLength() == 0U;
	result = result && Counter::Assert(0U, 0U, 0U, 0U, 0U, 0U);

	return result;
}

Bool ConstructEqualTest()
{
	Bool result = true;
	Vector<Counter> v1;
	Counter c1, c2, c3, c4;

	v1.Add(c1);
	v1.Add(c2);

	Counter::Clear();
	Vector<Counter> v2 = v1;
	result = result && v2.GetCapacity() == 2U && v2.GetLength() == 2U;
	result = result && Counter::Assert(0U, 2U, 0U, 0U, 0U, 0U);
	result = result && v2[0U].ID == 1U;
	result = result && v2[1U].ID == 2U;

	Counter::Clear();
	v2 = v2;
	result = result && v2.GetCapacity() == 2U && v2.GetLength() == 2U;
	result = result && Counter::Assert(0U, 0U, 0U, 0U, 0U, 0U);

	Vector<Counter> v3;
	v3.Add(c3);
	v3.Add(c4);
	Counter::Clear();
	v2 = v3;
	result = result && v2.GetCapacity() == 2U && v2.GetLength() == 2U;
	result = result && Counter::Assert(0U, 2U, 0U, 0U, 0U, 2U);
	result = result && v2[0U].ID == 3U;
	result = result && v2[1U].ID == 4U;

	return result;
}

Bool ReserveTest()
{
	Bool result;
	UInt Capacity = 10U;
	Vector<Counter> Vec;

	Counter::Clear();
	Vec.Reserve(Capacity);
	result = Vec.GetCapacity() == Capacity && Vec.GetLength() == 0;
	result = result && Counter::Assert(0U, 0U, 0U, 0U, 0U, 0U);

	return result;
}

Bool ShrinkTest()
{
	Bool result = true;
	Vector<Counter> Vec;
	Counter c1, c2, c3;

	Vec.Add(c1);
	Vec.Add(c2);
	Vec.Add(c3);

	Counter::Clear();
	Vec.Shrink();
	result = Vec.GetCapacity() == 3U && Vec.GetLength() == 3U;
	result = result && Counter::Assert(0U, 0U, 3U, 0U, 0U, 3U);
	result = result && Vec[0U].ID == 1U;
	result = result && Vec[1U].ID == 2U;
	result = result && Vec[2U].ID == 3U;

	return result;
}

Bool ClearTest()
{
	Bool result = true;
	Vector<Counter> Vec;
	Counter c1, c2, c3;

	Vec.Add(c1);
	Vec.Add(c2);
	Vec.Add(c3);

	Counter::Clear();
	Vec.Clear();
	result = Vec.GetCapacity() == 4U && Vec.GetLength() == 0U;
	result = result && Counter::Assert(0U, 0U, 0U, 0U, 0U, 3U);

	return result;
}

Bool FreeTest()
{
	Bool result = true;
	Vector<Counter> Vec;
	Counter c1, c2, c3;

	Vec.Add(c1);
	Vec.Add(c2);
	Vec.Add(c3);

	Counter::Clear();
	Vec.Free();
	result = Vec.GetCapacity() == 0U && Vec.GetLength() == 0U;
	result = result && Counter::Assert(0U, 0U, 0U, 0U, 0U, 3U);

	return result;
}

Bool BeginEndTest()
{
	Bool result = true;
	Vector<Counter> Vec;
	Counter c[3] = {Counter(), Counter(), Counter()};
	UInt i = 0;

	Vec.Add(c[0]);
	Vec.Add(c[1]);
	Vec.Add(c[2]);

	Counter::Clear();

	for(auto it = Vec.Begin(); it != Vec.End(); ++i, ++it)
		result = result && it->ID == c[i].ID;

	result = Vec.GetCapacity() == 4U && Vec.GetLength() == 3U;
	result = result && Counter::Assert(0U, 0U, 0U, 0U, 0U, 0U);

	return result;
}

Bool VectorTest()
{
	Bool result = true;

	result = result && ConstructEmptyTest();
	result = result && ConstructCapacityTest();

	result = result && AddTest();
	result = result && InsertTest();
	result = result && DeleteTest();

	result = result && ConstructCopyTest();
	result = result && ConstructEqualTest();

	result = result && ReserveTest();
	result = result && ShrinkTest();
	result = result && ClearTest();
	result = result && FreeTest();

	result = result && BeginEndTest();

	return result;
}
*/
