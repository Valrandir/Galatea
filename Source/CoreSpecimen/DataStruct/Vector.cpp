#define VectorUnitTest

#include "../Core.hpp"
#include "Counter.hpp"

using namespace Core;
using namespace DataStruct;

#define ASSERT result = result && 
typedef Vector<Counter> VCntr;

namespace VectorTestNamespace {

void AddFiveElementsNoReserve(VCntr &v)
{
	Counter::Clear();
	for(UInt i = 0; i < 5U; ++i)
		v.Add(Counter());
}

void AddFiveElements(VCntr &v)
{
	v.Reserve(5U);
	AddFiveElementsNoReserve(v);
}

Bool AssertCapLen(VCntr& v, UInt capacity, UInt length)
{
	return v.GetCapacity() == capacity && v.GetLength() == length;
}

Bool AssertCounter(UInt construct, UInt copyConstruct, UInt moveConstruct, UInt operatorEqual, UInt operatorMove, UInt destruct)
{
	if(VCntr::DefaultMode == VCntr::RawCopyDisabled)
		return Counter::Assert(construct, copyConstruct, moveConstruct, operatorEqual, operatorMove, destruct);
	else
		return true;
}

Bool AssertBeginEndNull(VCntr& v)
{
	Bool result = true;
	VCntr const & c = v;

	ASSERT v.Begin() == NULL && v.End() == NULL;
	ASSERT c.Begin() == NULL && c.End() == NULL;
	ASSERT v.RBegin() == v.End() - 1 && v.REnd() == v.Begin() - 1;
	ASSERT c.RBegin() == c.End() - 1 && c.REnd() == c.Begin() - 1;

	return result;
}

Bool AssertBeginEndNotNull(VCntr& v)
{
	Bool result = true;
	VCntr const & c = v;

	ASSERT v.Begin() && v.End() == v.Begin() + v.GetLength();
	ASSERT c.Begin() && c.End() == c.Begin() + c.GetLength();
	ASSERT v.RBegin() && v.REnd() == v.RBegin() - v.GetLength();
	ASSERT c.RBegin() && c.REnd() == c.RBegin() - c.GetLength();

	return result;
}

Bool AssertIteratageLength(VCntr& v, UInt length)
{
	Bool result = true;
	VCntr const & c = v;
	VCntr::Element *it, *end;
	VCntr::ConstElement *cit, *cend;
	UInt i, j, k, l;

	//Forward, then reverse, then const forward, then const reverse
	for(i = 0, it = v.Begin(), end = v.End(); it != end; ++i, ++it);
	for(j = 0, it = v.RBegin(), end = v.REnd(); it != end; ++j, --it);
	for(k = 0, cit = c.Begin(), cend = c.End(); cit != cend; ++k, ++cit);
	for(l = 0, cit = c.RBegin(), cend = c.REnd(); cit != cend; ++l, --cit);

	ASSERT i == length;
	ASSERT j == length;
	ASSERT k == length;
	ASSERT l == length;

	return result;
}

Bool CtorEmptyTest()
{
	Counter::Clear();

	Bool result = true;
	VCntr vc;

	ASSERT AssertCounter(0U, 0U, 0U, 0U, 0U, 0U);
	ASSERT AssertCapLen(vc, 0U, 0U);
	ASSERT vc.GetElementType() == VCntr::DefaultMode;
	ASSERT AssertBeginEndNull(vc);

	return result;
}

Bool CtorRawCopyTest()
{
	Bool result = true;
	VCntr vc(VCntr::RawCopyEnabled);

	ASSERT vc.GetElementType() == VCntr::RawCopyEnabled;

	return result;
}

Bool CtorCapacityTest()
{
	Counter::Clear();

	Bool result = true;
	VCntr vc(10U);
	VCntr const & cvc = vc;

	ASSERT AssertCounter(0U, 0U, 0U, 0U, 0U, 0U);
	ASSERT AssertCapLen(vc, 10U, 0U);
	ASSERT AssertBeginEndNotNull(vc);

	return result;
}

Bool CtorCopyTest()
{
	Bool result = true;

	//Copy empty vector
	VCntr vcEmpty;
	Counter::Clear();
	VCntr vc1(vcEmpty);
	ASSERT AssertCounter(0U, 0U, 0U, 0U, 0U, 0U);
	ASSERT AssertCapLen(vc1, 0U, 0U);
	ASSERT AssertBeginEndNull(vc1);

	//Copy Vector with capacity 5 and no elements
	VCntr vcCap5(5U);
	Counter::Clear();
	VCntr vc2(vcCap5);
	ASSERT AssertCounter(0U, 0U, 0U, 0U, 0U, 0U);
	ASSERT AssertCapLen(vc2, 0U, 0U);
	ASSERT AssertBeginEndNull(vc2);

	//Copy Vector with 5 elements
	VCntr vcWith5(5U);
	AddFiveElements(vcWith5);
	Counter::Clear();
	VCntr vc3(vcWith5);
	ASSERT AssertCounter(0U, 5U, 0U, 0U, 0U, 0U);
	ASSERT AssertCapLen(vc3, 5U, 5U);
	ASSERT AssertBeginEndNotNull(vc3);

	//Copy RawCopyEnabled vector
	VCntr vcRaw(VCntr::RawCopyEnabled);
	VCntr vc4(vcRaw);
	ASSERT vc4.GetElementType() == VCntr::RawCopyEnabled;

	return result;
}

Bool CtorMoveTest()
{
	Bool result = true;

	//Move empty vector
	VCntr vcEmpty;
	Counter::Clear();
	VCntr vc1((VCntr&&)vcEmpty);
	ASSERT AssertCounter(0U, 0U, 0U, 0U, 0U, 0U);
	ASSERT AssertCapLen(vc1, 0U, 0U);
	ASSERT AssertBeginEndNull(vc1);

	//Move Vector with capacity 5 and no elements
	VCntr vcCap5(5U);
	Counter::Clear();
	VCntr vc2((VCntr&&)vcCap5);
	ASSERT AssertCounter(0U, 0U, 0U, 0U, 0U, 0U);
	ASSERT AssertCapLen(vc2, 0U, 0U);
	ASSERT AssertBeginEndNull(vc2);

	//Move Vector with 5 elements
	VCntr vcWith5(5U);
	AddFiveElements(vcWith5);
	Counter::Clear();
	VCntr vc3((VCntr&&)vcWith5);
	ASSERT AssertCounter(0U, 0U, 0U, 0U, 0U, 0U);
	ASSERT AssertCapLen(vc3, 5U, 5U);
	ASSERT AssertBeginEndNotNull(vc3);
	ASSERT AssertCapLen(vcWith5, 0U, 0U);
	ASSERT AssertBeginEndNull(vcWith5);

	//Move RawCopyEnabled vector
	VCntr vcRaw(VCntr::RawCopyEnabled);
	VCntr vc4((VCntr&&)vcRaw);
	ASSERT vc4.GetElementType() == VCntr::RawCopyEnabled;

	return result;
}

Bool OperatorEqualTest()
{
	Bool result = true;

	//Assign empty vector
	VCntr vcEmpty;
	Counter::Clear();
	VCntr vc1 = vcEmpty;
	ASSERT AssertCounter(0U, 0U, 0U, 0U, 0U, 0U);
	ASSERT AssertCapLen(vc1, 0U, 0U);
	ASSERT AssertBeginEndNull(vc1);

	//Assign Vector with capacity 5 and no elements
	VCntr vcCap5(5U);
	Counter::Clear();
	VCntr vc2 = vcCap5;
	ASSERT AssertCounter(0U, 0U, 0U, 0U, 0U, 0U);
	ASSERT AssertCapLen(vc2, 0U, 0U);
	ASSERT AssertBeginEndNull(vc2);

	//Assign Vector with 5 elements
	VCntr vcWith5(5U);
	AddFiveElements(vcWith5);
	Counter::Clear();
	VCntr vc3 = vcWith5;
	ASSERT AssertCounter(0U, 5U, 0U, 0U, 0U, 0U);
	ASSERT AssertCapLen(vc3, 5U, 5U);
	ASSERT AssertBeginEndNotNull(vc3);

	//Assign RawCopyEnabled vector
	VCntr vcRaw(VCntr::RawCopyEnabled);
	VCntr vc4 = vcRaw;
	ASSERT vc4.GetElementType() == VCntr::RawCopyEnabled;

	return result;
}

Bool OperatorMoveTest()
{
	Bool result = true;

	//Assign empty vector
	VCntr vcEmpty;
	Counter::Clear();
	VCntr vc1 = (VCntr&&)vcEmpty;
	ASSERT AssertCounter(0U, 0U, 0U, 0U, 0U, 0U);
	ASSERT AssertCapLen(vc1, 0U, 0U);
	ASSERT AssertBeginEndNull(vc1);

	//Assign Vector with capacity 5 and no elements
	VCntr vcCap5(5U);
	Counter::Clear();
	VCntr vc2 = (VCntr&&)vcCap5;
	ASSERT AssertCounter(0U, 0U, 0U, 0U, 0U, 0U);
	ASSERT AssertCapLen(vc2, 0U, 0U);
	ASSERT AssertBeginEndNull(vc2);

	//Assign Vector with 5 elements
	VCntr vcWith5(5U);
	AddFiveElements(vcWith5);
	Counter::Clear();
	VCntr vc3 = (VCntr&&)vcWith5;
	ASSERT AssertCounter(0U, 0U, 0U, 0U, 0U, 0U);
	ASSERT AssertCapLen(vc3, 5U, 5U);
	ASSERT AssertBeginEndNotNull(vc3);

	//Assign RawCopyEnabled vector
	VCntr vcRaw(VCntr::RawCopyEnabled);
	VCntr vc4 = (VCntr&&)vcRaw;
	ASSERT vc4.GetElementType() == VCntr::RawCopyEnabled;

	return result;
}

Bool OperatorPlusEqualTest()
{
	Bool result = true;

	//Append empty to empty
	VCntr l1, r1;
	Counter::Clear();
	l1 += r1;
	ASSERT AssertCounter(0U, 0U, 0U, 0U, 0U, 0U);
	ASSERT AssertCapLen(l1, 0U, 0U);
	ASSERT AssertBeginEndNull(l1);

	//Append empty to not empty
	VCntr l2, r2;
	AddFiveElements(l2);
	Counter::Clear();
	l2 += r2;
	ASSERT AssertCounter(0U, 0U, 0U, 0U, 0U, 0U);
	ASSERT AssertCapLen(l2, 5U, 5U);
	ASSERT AssertBeginEndNotNull(l2);

	//Append not empty to empty
	VCntr l3, r3;
	AddFiveElements(r3);
	Counter::Clear();
	l3 += r3;
	ASSERT AssertCounter(0U, 5U, 0U, 0U, 0U, 0U);
	ASSERT AssertCapLen(l3, 5U, 5U);
	ASSERT AssertBeginEndNotNull(l3);

	//Append not empty to not empty
	VCntr l4, r4;
	AddFiveElements(l4);
	AddFiveElements(r4);
	Counter::Clear();
	l4 += r4;
	ASSERT AssertCounter(0U, 5U, 5U, 0U, 0U, 5U);
	ASSERT AssertCapLen(l4, 10U, 10U);
	ASSERT AssertBeginEndNotNull(l4);

	return result;
}

Bool GetElementTypeTest()
{
	Bool result = true;

	VCntr v1(VCntr::RawCopyEnabled);
	ASSERT v1.GetElementType() == VCntr::RawCopyEnabled;

	VCntr v2;
	ASSERT v2.GetElementType() == VCntr::DefaultMode;

	return result;
}

Bool IsEmptyTest()
{
	Bool result = true;

	//No Capacity
	VCntr v1;
	ASSERT v1.IsEmpty() == true;

	//Capacity and no elements
	VCntr v2(10U);
	ASSERT v2.IsEmpty() == true;

	//Capacity and elements
	VCntr v3(10U);
	v3.Add(Counter());
	ASSERT v3.IsEmpty() == false;

	return result;
}

Bool GetCapacityTest()
{
	Bool result = true;

	//No Capacity
	VCntr v1;
	ASSERT v1.GetCapacity() == 0;

	//Capacity
	VCntr v2(10U);
	ASSERT v2.GetCapacity() == 10U;

	return result;
}

Bool GetLengthTest()
{
	Bool result = true;

	//No Capacity
	VCntr v1;
	ASSERT v1.GetLength() == 0;

	//Capacity
	VCntr v2(10U);
	ASSERT v2.GetLength() == 0U;

	//Length
	VCntr v3(10U);
	v3.Add(Counter());
	ASSERT v3.GetLength() == 1U;

	return result;
}

Bool IteratorsTest()
{
	Bool result = true;

	//No Capacity
	VCntr v1;
	ASSERT AssertBeginEndNull(v1);

	//Capacity
	VCntr v2(10U);
	ASSERT AssertCapLen(v2, 10U, 0U);
	ASSERT AssertBeginEndNotNull(v2);
	ASSERT AssertIteratageLength(v2, 0U);

	//Length == 1
	VCntr v3(10U);
	v3.Add(Counter());
	ASSERT AssertCapLen(v3, 10U, 1U);
	ASSERT AssertBeginEndNotNull(v3);
	ASSERT AssertIteratageLength(v3, 1U);

	//Length == 5
	VCntr v4(15U);
	AddFiveElements(v4);
	ASSERT AssertCapLen(v4, 15U, 5U);
	ASSERT AssertBeginEndNotNull(v4);
	ASSERT AssertIteratageLength(v4, 5U);

	return result;
}

Bool ReserveTest()
{
	Bool result = true;

	//Reserve 10
	VCntr v1;
	v1.Reserve(10U);
	ASSERT v1.GetCapacity() == 10U;

	//Reserve 10 to a vector having 15
	VCntr v2(15U);
	v2.Reserve(10U);
	ASSERT v1.GetCapacity() == 10U;

	return result;
}

Bool ShrinkTest()
{
	Bool result = true;

	//Capacity 10 Length 0
	VCntr v1(10U);
	v1.Shrink();
	ASSERT v1.GetCapacity() == 0U;

	//Capacity 10 Length 5
	VCntr v2(10U);
	AddFiveElements(v2);
	v2.Shrink();
	ASSERT AssertCapLen(v2, 5U, 5U);

	return result;
}

Bool ClearTest()
{
	Bool result = true;

	//Empty
	VCntr v1;
	v1.Clear();
	ASSERT AssertCapLen(v1, 0U, 0U);

	//Capacity
	VCntr v2(10U);
	v2.Clear();
	ASSERT AssertCapLen(v2, 10U, 0U);

	//Length
	VCntr v3(10U);
	AddFiveElements(v3);
	v3.Clear();
	ASSERT AssertCapLen(v2, 10U, 0U);

	return result;
}

Bool FreeTest()
{
	Bool result = true;

	//Empty
	VCntr v1;
	v1.Free();
	ASSERT AssertCapLen(v1, 0U, 0U);

	//Capacity
	VCntr v2(10U);
	v2.Free();
	ASSERT AssertCapLen(v2, 0U, 0U);

	//Length
	VCntr v3(10U);
	AddFiveElements(v3);
	v3.Free();
	ASSERT AssertCapLen(v2, 0U, 0U);

	return result;
}

Bool AddTest()
{
	Bool result = true;
	VCntr v;

	Counter::Clear();
	Counter c1, c2, c3;

	Counter::Clear();
	v.Add(c1);
	ASSERT AssertCapLen(v, 2U, 1U);
	ASSERT AssertCounter(0U, 1U, 0U, 0U, 0U, 0U);
	ASSERT v[0U].ID == 1U;

	Counter::Clear();
	v.Add(c2);
	ASSERT AssertCapLen(v, 2U, 2U);
	ASSERT AssertCounter(0U, 1U, 0U, 0U, 0U, 0U);
	ASSERT v[1U].ID == 2U;

	Counter::Clear();
	v.Add(c3);
	ASSERT AssertCapLen(v, 4U, 3U);
	ASSERT AssertCounter(0U, 1U, 2U, 0U, 0U, 2U);
	ASSERT v[2U].ID == 3U;

	return result;
}

Bool AddRangeTest()
{
	Bool result = true;

	//Append empty to empty
	VCntr l1, r1;
	Counter::Clear();
	l1.AddRange(r1.Begin(), r1.End());
	ASSERT AssertCounter(0U, 0U, 0U, 0U, 0U, 0U);
	ASSERT AssertCapLen(l1, 0U, 0U);
	ASSERT AssertBeginEndNull(l1);

	//Append empty to not empty
	VCntr l2, r2;
	AddFiveElements(l2);
	Counter::Clear();
	l2.AddRange(r2.Begin(), r2.End());
	ASSERT AssertCounter(0U, 0U, 0U, 0U, 0U, 0U);
	ASSERT AssertCapLen(l2, 5U, 5U);
	ASSERT AssertBeginEndNotNull(l2);

	//Append not empty to empty
	VCntr l3, r3;
	AddFiveElements(r3);
	Counter::Clear();
	l3.AddRange(r3.Begin(), r3.End());
	ASSERT AssertCounter(0U, 5U, 0U, 0U, 0U, 0U);
	ASSERT AssertCapLen(l3, 5U, 5U);
	ASSERT AssertBeginEndNotNull(l3);

	//Append not empty to not empty
	VCntr l4, r4;
	AddFiveElements(l4);
	AddFiveElements(r4);
	Counter::Clear();
	l4.AddRange(r4.Begin(), r4.End());
	ASSERT AssertCounter(0U, 5U, 5U, 0U, 0U, 5U);
	ASSERT AssertCapLen(l4, 10U, 10U);
	ASSERT AssertBeginEndNotNull(l4);

	return result;
}

Bool InsertByIndexTest()
{
	Bool result = true;
	VCntr v;

	Counter::Clear();
	Counter c1, c2, c3, c4;

	Counter::Clear();
	v.Insert(100U, c1);
	ASSERT AssertCapLen(v, 2U, 1U);
	ASSERT AssertCounter(0U, 1U, 0U, 0U, 0U, 0U);
	ASSERT v[0U].ID == 1U;

	Counter::Clear();
	v.Insert(100U, c2);
	ASSERT AssertCapLen(v, 2U, 2U);
	ASSERT AssertCounter(0U, 1U, 0U, 0U, 0U, 0U);
	ASSERT v[1U].ID == 2U;

	Counter::Clear();
	v.Insert(0U, c3);
	ASSERT AssertCapLen(v, 4U, 3U);
	ASSERT AssertCounter(0U, 1U, 4U, 0U, 0U, 2U);
	ASSERT v[0U].ID == 3U;
	ASSERT v[1U].ID == 1U;
	ASSERT v[2U].ID == 2U;

	Counter::Clear();
	v.Insert(1U, c4);
	ASSERT AssertCapLen(v, 4U, 4U);
	ASSERT AssertCounter(0U, 1U, 2U, 0U, 0U, 0U);
	ASSERT v[0U].ID == 3U;
	ASSERT v[1U].ID == 4U;
	ASSERT v[2U].ID == 1U;
	ASSERT v[3U].ID == 2U;

	return result;
}

Bool InsertByRefTest()
{
	Bool result = true;
	VCntr v;

	Counter::Clear();
	AddFiveElementsNoReserve(v);
	Counter c1, c2, c3, c4;

	Counter::Clear();
	v.Insert(v[4], c1);
	ASSERT AssertCapLen(v, 8U, 6U);
	ASSERT AssertCounter(0U, 1U, 1U, 0U, 0U, 0U);
	ASSERT v[0U].ID == 1U;
	ASSERT v[1U].ID == 2U;
	ASSERT v[2U].ID == 3U;
	ASSERT v[3U].ID == 4U;
	ASSERT v[4U].ID == 6U;
	ASSERT v[5U].ID == 5U;

	Counter::Clear();
	v.Insert(v[0], c2);
	ASSERT AssertCapLen(v, 8U, 7U);
	ASSERT AssertCounter(0U, 1U, 6U, 0U, 0U, 0U);
	ASSERT v[0U].ID == 7U;
	ASSERT v[1U].ID == 1U;
	ASSERT v[2U].ID == 2U;
	ASSERT v[3U].ID == 3U;
	ASSERT v[4U].ID == 4U;
	ASSERT v[5U].ID == 6U;
	ASSERT v[6U].ID == 5U;

	Counter::Clear();
	v.Insert(v[3], c3);
	ASSERT AssertCapLen(v, 8U, 8U);
	ASSERT AssertCounter(0U, 1U, 4U, 0U, 0U, 0U);
	ASSERT v[0U].ID == 7U;
	ASSERT v[1U].ID == 1U;
	ASSERT v[2U].ID == 2U;
	ASSERT v[3U].ID == 8U;
	ASSERT v[4U].ID == 3U;
	ASSERT v[5U].ID == 4U;
	ASSERT v[6U].ID == 6U;
	ASSERT v[7U].ID == 5U;

	Counter::Clear();
	v.Insert(v[6], c4);
	ASSERT AssertCapLen(v, 16U, 9U);
	ASSERT AssertCounter(0U, 1U, 10U, 0U, 0U, 8U);
	ASSERT v[0U].ID == 7U;
	ASSERT v[1U].ID == 1U;
	ASSERT v[2U].ID == 2U;
	ASSERT v[3U].ID == 8U;
	ASSERT v[4U].ID == 3U;
	ASSERT v[5U].ID == 4U;
	ASSERT v[6U].ID == 9U;
	ASSERT v[7U].ID == 6U;
	ASSERT v[8U].ID == 5U;

	return result;
}

Bool RemoveByIndexTest()
{
	Bool result = true;
	VCntr v;

	AddFiveElements(v);

	Counter::Clear();
	v.Remove(100U);
	ASSERT AssertCapLen(v, 5U, 4U);
	ASSERT AssertCounter(0U, 0U, 0U, 0U, 0U, 1U);
	ASSERT v[0U].ID == 1U;
	ASSERT v[1U].ID == 2U;
	ASSERT v[2U].ID == 3U;
	ASSERT v[3U].ID == 4U;

	Counter::Clear();
	v.Remove(1U);
	ASSERT AssertCapLen(v, 5U, 3U);
	ASSERT AssertCounter(0U, 0U, 2U, 0U, 0U, 2U);
	ASSERT v[0U].ID == 1U;
	ASSERT v[1U].ID == 3U;
	ASSERT v[2U].ID == 4U;

	Counter::Clear();
	v.Remove(1U);
	ASSERT AssertCapLen(v, 5U, 2U);
	ASSERT AssertCounter(0U, 0U, 1U, 0U, 0U, 2U);
	ASSERT v[0U].ID == 1U;
	ASSERT v[1U].ID == 4U;

	Counter::Clear();
	v.Remove(0U);
	ASSERT AssertCapLen(v, 5U, 1U);
	ASSERT AssertCounter(0U, 0U, 1U, 0U, 0U, 2U);
	ASSERT v[0U].ID == 4U;

	Counter::Clear();
	v.Remove(0U);
	ASSERT AssertCapLen(v, 5U, 0U);
	ASSERT AssertCounter(0U, 0U, 0U, 0U, 0U, 1U);

	return result;
}

Bool RemoveByRefTest()
{
	Bool result = true;
	VCntr v;

	AddFiveElements(v);

	Counter::Clear();
	v.Remove(v[4]);
	ASSERT AssertCapLen(v, 5U, 4U);
	ASSERT AssertCounter(0U, 0U, 0U, 0U, 0U, 1U);
	ASSERT v[0U].ID == 1U;
	ASSERT v[1U].ID == 2U;
	ASSERT v[2U].ID == 3U;
	ASSERT v[3U].ID == 4U;

	Counter::Clear();
	v.Remove(v[1]);
	ASSERT AssertCapLen(v, 5U, 3U);
	ASSERT AssertCounter(0U, 0U, 2U, 0U, 0U, 2U);
	ASSERT v[0U].ID == 1U;
	ASSERT v[1U].ID == 3U;
	ASSERT v[2U].ID == 4U;

	Counter::Clear();
	v.Remove(v[1]);
	ASSERT AssertCapLen(v, 5U, 2U);
	ASSERT AssertCounter(0U, 0U, 1U, 0U, 0U, 2U);
	ASSERT v[0U].ID == 1U;
	ASSERT v[1U].ID == 4U;

	Counter::Clear();
	v.Remove(v[0]);
	ASSERT AssertCapLen(v, 5U, 1U);
	ASSERT AssertCounter(0U, 0U, 1U, 0U, 0U, 2U);
	ASSERT v[0U].ID == 4U;

	Counter::Clear();
	v.Remove(v[0]);
	ASSERT AssertCapLen(v, 5U, 0U);
	ASSERT AssertCounter(0U, 0U, 0U, 0U, 0U, 1U);

	return result;
}

} //namespace

using namespace VectorTestNamespace;

Bool VectorTest(VCntr::RawCopyEnum defaultMode)
{
	Bool result = true;

	VCntr::DefaultMode = defaultMode;

	ASSERT CtorEmptyTest();
	ASSERT CtorRawCopyTest();
	ASSERT CtorCapacityTest();
	ASSERT CtorCopyTest();
	ASSERT CtorMoveTest();

	ASSERT OperatorEqualTest();
	ASSERT OperatorMoveTest();
	ASSERT OperatorPlusEqualTest();

	ASSERT GetElementTypeTest();
	ASSERT IsEmptyTest();
	ASSERT GetCapacityTest();
	ASSERT GetLengthTest();

	ASSERT IteratorsTest();

	ASSERT ReserveTest();
	ASSERT ShrinkTest();
	ASSERT ClearTest();
	ASSERT FreeTest();

	ASSERT AddTest();
	ASSERT AddRangeTest();
	ASSERT InsertByIndexTest();
	ASSERT InsertByRefTest();
	ASSERT RemoveByIndexTest();
	ASSERT RemoveByRefTest();

	return result;
}

Bool VectorTest()
{
	Bool result = true;

	ASSERT VectorTest(VCntr::RawCopyDisabled);
	ASSERT VectorTest(VCntr::RawCopyEnabled);

	return result;
}
