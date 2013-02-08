#define VectorUnitTest

#include "../Core.hpp"
#include "Counter.hpp"

using namespace Core;
using namespace DataStruct;

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

Bool AssertCntrAlways(UInt construct, UInt copyConstruct, UInt moveConstruct, UInt operatorEqual, UInt operatorMove, UInt destruct)
{
	if(VCntr::DefaultMode == VCntr::CtorModeEnum::Always)
		return Counter::Assert(construct, copyConstruct, moveConstruct, operatorEqual, operatorMove, destruct);
	else
		return true;
}

Bool AssertCntrOnce(UInt construct, UInt copyConstruct, UInt moveConstruct, UInt operatorEqual, UInt operatorMove, UInt destruct)
{
	if(VCntr::DefaultMode == VCntr::CtorModeEnum::Once)
		return Counter::Assert(construct, copyConstruct, moveConstruct, operatorEqual, operatorMove, destruct);
	else
		return true;
}

Bool AssertCntrPod(UInt construct = 0U, UInt copyConstruct = 0U, UInt moveConstruct = 0U, UInt operatorEqual = 0U, UInt operatorMove = 0U, UInt destruct = 0U)
{
	if(VCntr::DefaultMode == VCntr::CtorModeEnum::Pod)
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

	ASSERT AssertCntrPod();
	ASSERT AssertCntrOnce(0U, 0U, 0U, 0U, 0U, 0U);
	ASSERT AssertCntrAlways(0U, 0U, 0U, 0U, 0U, 0U);

	ASSERT AssertCapLen(vc, 0U, 0U);
	ASSERT vc.GetElementType() == VCntr::DefaultMode;
	ASSERT AssertBeginEndNull(vc);

	return result;
}

Bool CtorModeTest()
{
	Bool result = true;
	VCntr vc(VCntr::CtorModeEnum::Once);

	ASSERT vc.GetElementType() == VCntr::CtorModeEnum::Once;

	return result;
}

Bool CtorCapacityTest()
{
	Counter::Clear();

	Bool result = true;
	VCntr vc(10U);

	ASSERT AssertCntrPod();
	ASSERT AssertCntrOnce(0U, 0U, 0U, 0U, 0U, 0U);
	ASSERT AssertCntrAlways(0U, 0U, 0U, 0U, 0U, 0U);
	ASSERT AssertCapLen(vc, 10U, 0U);
	ASSERT AssertBeginEndNotNull(vc);

	return result;
}

Bool CtorCopyTest()
{
	Bool result = true;

	//Copy empty vector
	{
		VCntr source;
		Counter::Clear();
		VCntr target(source);
		ASSERT AssertCntrPod();
		ASSERT AssertCntrOnce(0U, 0U, 0U, 0U, 0U, 0U);
		ASSERT AssertCntrAlways(0U, 0U, 0U, 0U, 0U, 0U);
		ASSERT AssertCapLen(target, 0U, 0U);
		ASSERT AssertBeginEndNull(target);
	}

	//Copy Vector with capacity 5 and no elements
	{
		VCntr source(5U);
		Counter::Clear();
		VCntr target(source);
		ASSERT AssertCntrPod();
		ASSERT AssertCntrOnce(0U, 0U, 0U, 0U, 0U, 0U);
		ASSERT AssertCntrAlways(0U, 0U, 0U, 0U, 0U, 0U);
		ASSERT AssertCapLen(target, 0U, 0U);
		ASSERT AssertBeginEndNull(target);
	}

	//Copy Vector with 5 elements
	{
		VCntr source(5U);
		AddFiveElements(source);
		Counter::Clear();
		VCntr target(source);
		ASSERT AssertCntrPod();
		ASSERT AssertCntrOnce(0U, 0U, 0U, 0U, 0U, 0U);
		ASSERT AssertCntrAlways(0U, 5U, 0U, 0U, 0U, 0U);
		ASSERT AssertCapLen(target, 5U, 5U);
		ASSERT AssertBeginEndNotNull(target);
	}

	//Copy RawCopyEnabled vector
	{
		VCntr source(VCntr::CtorModeEnum::Pod);
		VCntr target(source);
		ASSERT target.GetElementType() == VCntr::CtorModeEnum::Pod;
	}

	return result;
}

Bool CtorMoveTest()
{
	Bool result = true;

	//Move empty vector
	{
		VCntr source;
		Counter::Clear();
		VCntr target((VCntr&&)source);
		ASSERT AssertCntrPod();
		ASSERT AssertCntrOnce(0U, 0U, 0U, 0U, 0U, 0U);
		ASSERT AssertCntrAlways(0U, 0U, 0U, 0U, 0U, 0U);
		ASSERT AssertCapLen(target, 0U, 0U);
		ASSERT AssertBeginEndNull(target);
}

	//Move Vector with capacity 5 and no elements
	{
		VCntr source(5U);
		Counter::Clear();
		VCntr target((VCntr&&)source);
		ASSERT AssertCntrPod();
		ASSERT AssertCntrOnce(0U, 0U, 0U, 0U, 0U, 0U);
		ASSERT AssertCntrAlways(0U, 0U, 0U, 0U, 0U, 0U);
		ASSERT AssertCapLen(target, 0U, 0U);
		ASSERT AssertBeginEndNull(target);
	}

	//Move Vector with 5 elements
	{
		VCntr source(5U);
		AddFiveElements(source);
		Counter::Clear();
		VCntr target((VCntr&&)source);
		ASSERT AssertCntrPod();
		ASSERT AssertCntrOnce(0U, 0U, 0U, 0U, 0U, 0U);
		ASSERT AssertCntrAlways(0U, 0U, 0U, 0U, 0U, 0U);
		ASSERT AssertCapLen(target, 5U, 5U);
		ASSERT AssertBeginEndNotNull(target);
		ASSERT AssertCapLen(source, 0U, 0U);
		ASSERT AssertBeginEndNull(source);
	}

	//Move RawCopyEnabled vector
	{
		VCntr source(VCntr::CtorModeEnum::Pod);
		VCntr target((VCntr&&)source);
		ASSERT target.GetElementType() == VCntr::CtorModeEnum::Pod;
	}

	return result;
}

Bool OperatorEqualTest()
{
	Bool result = true;

	//Assign empty vector to empty vector
	{
		VCntr source;
		Counter::Clear();
		VCntr target = source;
		ASSERT AssertCntrPod();
		ASSERT AssertCntrOnce(0U, 0U, 0U, 0U, 0U, 0U);
		ASSERT AssertCntrAlways(0U, 0U, 0U, 0U, 0U, 0U);
		ASSERT AssertCapLen(target, 0U, 0U);
		ASSERT AssertBeginEndNull(target);
	}

	//Assign Vector with capacity 5 and no elements to empty vector
	{
		VCntr source(5U);
		Counter::Clear();
		VCntr target = source;
		ASSERT AssertCntrPod();
		ASSERT AssertCntrOnce(0U, 0U, 0U, 0U, 0U, 0U);
		ASSERT AssertCntrAlways(0U, 0U, 0U, 0U, 0U, 0U);
		ASSERT AssertCapLen(target, 0U, 0U);
		ASSERT AssertBeginEndNull(target);
	}

	//Assign Vector with 5 elements to empty vector
	{
		VCntr source;
		AddFiveElements(source);
		Counter::Clear();
		VCntr target = source;
		ASSERT AssertCntrPod();
		ASSERT AssertCntrOnce(0U, 0U, 0U, 0U, 0U, 0U);
		ASSERT AssertCntrAlways(0U, 5U, 0U, 0U, 0U, 0U);
		ASSERT AssertCapLen(target, 5U, 5U);
		ASSERT AssertBeginEndNotNull(target);
	}

	//Assign empty vector to vector with 5 elements
	{
		VCntr source, target;
		AddFiveElements(target);
		Counter::Clear();
		target = source;
		ASSERT AssertCntrPod();
		ASSERT AssertCntrOnce(0U, 0U, 0U, 0U, 0U, 5U);
		ASSERT AssertCntrAlways(0U, 0U, 0U, 0U, 0U, 5U);
		ASSERT AssertCapLen(target, 0U, 0U);
		ASSERT AssertBeginEndNull(target);
	}

	//Assign Vector with capacity 5 and no elements to vector with 5 elements
	{
		VCntr source(5U), target;
		AddFiveElements(target);
		Counter::Clear();
		target = source;
		ASSERT AssertCntrPod();
		ASSERT AssertCntrOnce(0U, 0U, 0U, 0U, 0U, 5U);
		ASSERT AssertCntrAlways(0U, 0U, 0U, 0U, 0U, 5U);
		ASSERT AssertCapLen(target, 0U, 0U);
		ASSERT AssertBeginEndNull(target);
	}

	//Assign Vector with 5 elements to vector with 5 elements
	{
		VCntr source, target;
		AddFiveElements(source);
		AddFiveElements(target);
		Counter::Clear();
		target = source;
		ASSERT AssertCntrPod();
		ASSERT AssertCntrOnce(0U, 0U, 0U, 0U, 0U, 5U);
		ASSERT AssertCntrAlways(0U, 5U, 0U, 0U, 0U, 5U);
		ASSERT AssertCapLen(target, 5U, 5U);
		ASSERT AssertBeginEndNotNull(target);
	}

	//Assign RawCopyEnabled vector
	{
		VCntr source(VCntr::CtorModeEnum::Pod);
		VCntr target = source;
		ASSERT target.GetElementType() == VCntr::CtorModeEnum::Pod;
	}

	return result;
}

Bool OperatorMoveTest()
{
	Bool result = true;

	//Assign empty vector
	{
		VCntr target;
		Counter::Clear();
		VCntr source = (VCntr&&)target;
		ASSERT AssertCntrPod();
		ASSERT AssertCntrOnce(0U, 0U, 0U, 0U, 0U, 0U);
		ASSERT AssertCntrAlways(0U, 0U, 0U, 0U, 0U, 0U);
		ASSERT AssertCapLen(source, 0U, 0U);
		ASSERT AssertBeginEndNull(source);
	}

	//Assign Vector with capacity 5 and no elements
	{
		VCntr target(5U);
		Counter::Clear();
		VCntr source = (VCntr&&)target;
		ASSERT AssertCntrPod();
		ASSERT AssertCntrOnce(0U, 0U, 0U, 0U, 0U, 0U);
		ASSERT AssertCntrAlways(0U, 0U, 0U, 0U, 0U, 0U);
		ASSERT AssertCapLen(source, 0U, 0U);
		ASSERT AssertBeginEndNull(source);
	}

	//Assign Vector with 5 elements
	{
		VCntr target(5U);
		AddFiveElements(target);
		Counter::Clear();
		VCntr source = (VCntr&&)target;
		ASSERT AssertCntrPod();
		ASSERT AssertCntrOnce(0U, 0U, 0U, 0U, 0U, 0U);
		ASSERT AssertCntrAlways(0U, 0U, 0U, 0U, 0U, 0U);
		ASSERT AssertCapLen(source, 5U, 5U);
		ASSERT AssertBeginEndNotNull(source);
	}

	//Assign RawCopyEnabled vector
	{
		VCntr target(VCntr::CtorModeEnum::Pod);
		VCntr source = (VCntr&&)target;
		ASSERT source.GetElementType() == VCntr::CtorModeEnum::Pod;
	}

	return result;
}

Bool OperatorPlusEqualTest()
{
	Bool result = true;

	//Append empty to empty
	{
		VCntr source, target;
		Counter::Clear();
		target += source;
		ASSERT AssertCntrPod();
		ASSERT AssertCntrOnce(0U, 0U, 0U, 0U, 0U, 0U);
		ASSERT AssertCntrAlways(0U, 0U, 0U, 0U, 0U, 0U);
		ASSERT AssertCapLen(target, 0U, 0U);
		ASSERT AssertBeginEndNull(target);
	}

	//Append empty to not empty
	{
		VCntr source, target;
		AddFiveElements(target);
		Counter::Clear();
		target += source;
		ASSERT AssertCntrPod();
		ASSERT AssertCntrOnce(0U, 0U, 0U, 0U, 0U, 0U);
		ASSERT AssertCntrAlways(0U, 0U, 0U, 0U, 0U, 0U);
		ASSERT AssertCapLen(target, 5U, 5U);
		ASSERT AssertBeginEndNotNull(target);
	}

	//Append not empty to empty
	{
		VCntr source, target;
		AddFiveElements(source);
		Counter::Clear();
		target += source;
		ASSERT AssertCntrPod();
		ASSERT AssertCntrOnce(0U, 5U, 0U, 0U, 0U, 0U);
		ASSERT AssertCntrAlways(0U, 5U, 0U, 0U, 0U, 0U);
		ASSERT AssertCapLen(target, 5U, 5U);
		ASSERT AssertBeginEndNotNull(target);
	}

	//Append not empty to not empty
	{
		VCntr source, target;
		AddFiveElements(target);
		AddFiveElements(source);
		Counter::Clear();
		target += source;
		ASSERT AssertCntrPod();
		ASSERT AssertCntrOnce(0U, 5U, 0U, 0U, 0U, 0U);
		ASSERT AssertCntrAlways(0U, 5U, 5U, 0U, 0U, 5U);
		ASSERT AssertCapLen(target, 10U, 10U);
		ASSERT AssertBeginEndNotNull(target);
	}

	return result;
}

Bool GetElementTypeTest()
{
	Bool result = true;

	//Specify mode obtain same mode
	{
		VCntr v(VCntr::CtorModeEnum::Pod);
		ASSERT v.GetElementType() == VCntr::CtorModeEnum::Pod;
	}

	//Don't specify mode obtain default
	{
		VCntr v;
		ASSERT v.GetElementType() == VCntr::DefaultMode;
	}

	return result;
}

Bool IsEmptyTest()
{
	Bool result = true;

	//No Capacity
	{
		VCntr v;
		ASSERT v.IsEmpty() == true;
	}

	//Capacity and no elements
	{
		VCntr v(10U);
		ASSERT v.IsEmpty() == true;
	}

	//Capacity and elements
	{
		VCntr v(10U);
		v.Add(Counter());
		ASSERT v.IsEmpty() == false;
	}

	return result;
}

Bool GetCapacityTest()
{
	Bool result = true;

	//No Capacity Specified
	{
		VCntr v;
		ASSERT v.GetCapacity() == 0;
	}

	//Capacity Specified
	{
		VCntr v(10U);
		ASSERT v.GetCapacity() == 10U;
	}

	return result;
}

Bool GetLengthTest()
{
	Bool result = true;

	//No Capacity
	{
		VCntr v;
		ASSERT v.GetLength() == 0;
	}

	//Capacity
	{
		VCntr v(10U);
		ASSERT v.GetLength() == 0U;
	}

	//Length
	{
		VCntr v(10U);
		v.Add(Counter());
		ASSERT v.GetLength() == 1U;
	}

	return result;
}

Bool IteratorsTest()
{
	Bool result = true;

	//No Capacity
	{
		VCntr v;
		ASSERT AssertBeginEndNull(v);
	}

	//Capacity
	{
		VCntr v(10U);
		ASSERT AssertCapLen(v, 10U, 0U);
		ASSERT AssertBeginEndNotNull(v);
		ASSERT AssertIteratageLength(v, 0U);
	}

	//Length == 1
	{
		VCntr v(10U);
		v.Add(Counter());
		ASSERT AssertCapLen(v, 10U, 1U);
		ASSERT AssertBeginEndNotNull(v);
		ASSERT AssertIteratageLength(v, 1U);
	}

	//Length == 5
	{
		VCntr v(15U);
		AddFiveElements(v);
		ASSERT AssertCapLen(v, 15U, 5U);
		ASSERT AssertBeginEndNotNull(v);
		ASSERT AssertIteratageLength(v, 5U);
	}

	return result;
}

Bool ReserveTest()
{
	Bool result = true;

	//Reserve 10
	{
		VCntr v;
		v.Reserve(10U);
		ASSERT v.GetCapacity() == 10U;
	}

	//Reserve 10 to a vector having 15
	{
		VCntr v(15U);
		v.Reserve(10U);
		ASSERT v.GetCapacity() == 15U;
	}

	return result;
}

Bool ShrinkTest()
{
	Bool result = true;

	//Capacity 10 Length 0
	{
		VCntr v(10U);
		v.Shrink();
		ASSERT v.GetCapacity() == 0U;
	}

	//Capacity 10 Length 5
	{
		VCntr v(10U);
		AddFiveElements(v);
		v.Shrink();
		ASSERT AssertCapLen(v, 5U, 5U);
	}

	return result;
}

Bool ClearTest()
{
	Bool result = true;

	//Empty
	{
		VCntr v;
		Counter::Clear();
		v.Clear();
		ASSERT AssertCntrPod();
		ASSERT AssertCntrOnce(0U, 0U, 0U, 0U, 0U, 0U);
		ASSERT AssertCntrAlways(0U, 0U, 0U, 0U, 0U, 0U);
		ASSERT AssertCapLen(v, 0U, 0U);
	}

	//Capacity
	{
		VCntr v(10U);
		Counter::Clear();
		v.Clear();
		ASSERT AssertCntrPod();
		ASSERT AssertCntrOnce(0U, 0U, 0U, 0U, 0U, 0U);
		ASSERT AssertCntrAlways(0U, 0U, 0U, 0U, 0U, 0U);
		ASSERT AssertCapLen(v, 10U, 0U);
	}

	//Length
	{
		VCntr v(10U);
		AddFiveElements(v);
		Counter::Clear();
		v.Clear();
		ASSERT AssertCntrPod();
		ASSERT AssertCntrOnce(0U, 0U, 0U, 0U, 0U, 5U);
		ASSERT AssertCntrAlways(0U, 0U, 0U, 0U, 0U, 5U);
		ASSERT AssertCapLen(v, 10U, 0U);
	}

	return result;
}

Bool FreeTest()
{
	Bool result = true;

	//Empty
	{
		VCntr v;
		Counter::Clear();
		v.Free();
		ASSERT AssertCntrPod();
		ASSERT AssertCntrOnce(0U, 0U, 0U, 0U, 0U, 0U);
		ASSERT AssertCntrAlways(0U, 0U, 0U, 0U, 0U, 0U);
		ASSERT AssertCapLen(v, 0U, 0U);
	}

	//Capacity
	{
		VCntr v(10U);
		Counter::Clear();
		v.Free();
		ASSERT AssertCntrPod();
		ASSERT AssertCntrOnce(0U, 0U, 0U, 0U, 0U, 0U);
		ASSERT AssertCntrAlways(0U, 0U, 0U, 0U, 0U, 0U);
		ASSERT AssertCapLen(v, 0U, 0U);
	}

	//Length
	{
		VCntr v(10U);
		AddFiveElements(v);
		Counter::Clear();
		v.Free();
		ASSERT AssertCntrPod();
		ASSERT AssertCntrOnce(0U, 0U, 0U, 0U, 0U, 5U);
		ASSERT AssertCntrAlways(0U, 0U, 0U, 0U, 0U, 5U);
		ASSERT AssertCapLen(v, 0U, 0U);
	}

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
	ASSERT AssertCntrPod(0U, 0U, 0U, 1U, 0U, 0U);
	ASSERT AssertCntrOnce(0U, 1U, 0U, 0U, 0U, 0U);
	ASSERT AssertCntrAlways(0U, 1U, 0U, 0U, 0U, 0U);
	ASSERT v[0U].ID == 1U;

	Counter::Clear();
	v.Add(c2);
	ASSERT AssertCapLen(v, 2U, 2U);
	ASSERT AssertCntrPod(0U, 0U, 0U, 1U, 0U, 0U);
	ASSERT AssertCntrOnce(0U, 1U, 0U, 0U, 0U, 0U);
	ASSERT AssertCntrAlways(0U, 1U, 0U, 0U, 0U, 0U);
	ASSERT v[1U].ID == 2U;

	Counter::Clear();
	v.Add(c3);
	ASSERT AssertCapLen(v, 4U, 3U);
	ASSERT AssertCntrPod(0U, 0U, 0U, 1U, 0U, 0U);
	ASSERT AssertCntrOnce(0U, 1U, 0U, 0U, 0U, 0U);
	ASSERT AssertCntrAlways(0U, 1U, 2U, 0U, 0U, 2U);
	ASSERT v[2U].ID == 3U;

	return result;
}

Bool AddRangeTest()
{
	Bool result = true;

	//Append empty to empty
	{
		VCntr source, target;
		Counter::Clear();
		target.AddRange(source.Begin(), source.End());
		ASSERT AssertCntrPod();
		ASSERT AssertCntrOnce(0U, 0U, 0U, 0U, 0U, 0U);
		ASSERT AssertCntrAlways(0U, 0U, 0U, 0U, 0U, 0U);
		ASSERT AssertCapLen(target, 0U, 0U);
		ASSERT AssertBeginEndNull(target);
	}

	//Append empty to not empty
	{
		VCntr source, target;
		AddFiveElements(target);
		Counter::Clear();
		target.AddRange(source.Begin(), source.End());
		ASSERT AssertCntrPod();
		ASSERT AssertCntrOnce(0U, 0U, 0U, 0U, 0U, 0U);
		ASSERT AssertCntrAlways(0U, 0U, 0U, 0U, 0U, 0U);
		ASSERT AssertCapLen(target, 5U, 5U);
		ASSERT AssertBeginEndNotNull(target);
	}

	//Append not empty to empty
	{
		VCntr source, target;
		AddFiveElements(source);
		Counter::Clear();
		target.AddRange(source.Begin(), source.End());
		ASSERT AssertCntrPod();
		ASSERT AssertCntrOnce(0U, 5U, 0U, 0U, 0U, 0U);
		ASSERT AssertCntrAlways(0U, 5U, 0U, 0U, 0U, 0U);
		ASSERT AssertCapLen(target, 5U, 5U);
		ASSERT AssertBeginEndNotNull(target);
	}

	//Append not empty to not empty
	{
		VCntr source, target;
		AddFiveElements(target);
		AddFiveElements(source);
		Counter::Clear();
		target.AddRange(source.Begin(), source.End());
		ASSERT AssertCntrPod();
		ASSERT AssertCntrOnce(0U, 5U, 0U, 0U, 0U, 0U);
		ASSERT AssertCntrAlways(0U, 5U, 5U, 0U, 0U, 5U);
		ASSERT AssertCapLen(target, 10U, 10U);
		ASSERT AssertBeginEndNotNull(target);
	}

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
	ASSERT AssertCntrPod(0U, 0U, 0U, 1U, 0U, 0U);
	ASSERT AssertCntrOnce(0U, 1U, 0U, 0U, 0U, 0U);
	ASSERT AssertCntrAlways(0U, 1U, 0U, 0U, 0U, 0U);
	ASSERT v[0U].ID == 1U;

	Counter::Clear();
	v.Insert(100U, c2);
	ASSERT AssertCapLen(v, 2U, 2U);
	ASSERT AssertCntrPod(0U, 0U, 0U, 1U, 0U, 0U);
	ASSERT AssertCntrOnce(0U, 1U, 0U, 0U, 0U, 0U);
	ASSERT AssertCntrAlways(0U, 1U, 0U, 0U, 0U, 0U);
	ASSERT v[1U].ID == 2U;

	Counter::Clear();
	v.Insert(0U, c3);
	ASSERT AssertCapLen(v, 4U, 3U);
	ASSERT AssertCntrPod(0U, 0U, 0U, 1U, 0U, 0U);
	ASSERT AssertCntrOnce(0U, 1U, 0U, 0U, 0U, 0U);
	ASSERT AssertCntrAlways(0U, 1U, 4U, 0U, 0U, 2U);
	ASSERT v[0U].ID == 3U;
	ASSERT v[1U].ID == 1U;
	ASSERT v[2U].ID == 2U;

	Counter::Clear();
	v.Insert(1U, c4);
	ASSERT AssertCapLen(v, 4U, 4U);
	ASSERT AssertCntrPod(0U, 0U, 0U, 1U, 0U, 0U);
	ASSERT AssertCntrOnce(0U, 1U, 0U, 0U, 0U, 0U);
	ASSERT AssertCntrAlways(0U, 1U, 2U, 0U, 0U, 0U);
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
	ASSERT AssertCntrPod(0U, 0U, 0U, 1U, 0U, 0U);
	ASSERT AssertCntrOnce(0U, 1U, 0U, 0U, 0U, 0U);
	ASSERT AssertCntrAlways(0U, 1U, 1U, 0U, 0U, 0U);
	ASSERT v[0U].ID == 1U;
	ASSERT v[1U].ID == 2U;
	ASSERT v[2U].ID == 3U;
	ASSERT v[3U].ID == 4U;
	ASSERT v[4U].ID == 6U;
	ASSERT v[5U].ID == 5U;

	Counter::Clear();
	v.Insert(v[0], c2);
	ASSERT AssertCapLen(v, 8U, 7U);
	ASSERT AssertCntrPod(0U, 0U, 0U, 1U, 0U, 0U);
	ASSERT AssertCntrOnce(0U, 1U, 0U, 0U, 0U, 0U);
	ASSERT AssertCntrAlways(0U, 1U, 6U, 0U, 0U, 0U);
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
	ASSERT AssertCntrPod(0U, 0U, 0U, 1U, 0U, 0U);
	ASSERT AssertCntrOnce(0U, 1U, 0U, 0U, 0U, 0U);
	ASSERT AssertCntrAlways(0U, 1U, 4U, 0U, 0U, 0U);
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
	ASSERT AssertCntrPod(0U, 0U, 0U, 1U, 0U, 0U);
	ASSERT AssertCntrOnce(0U, 1U, 0U, 0U, 0U, 0U);
	ASSERT AssertCntrAlways(0U, 1U, 10U, 0U, 0U, 8U);
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
	ASSERT AssertCntrPod();
	ASSERT AssertCntrOnce(0U, 0U, 0U, 0U, 0U, 1U);
	ASSERT AssertCntrAlways(0U, 0U, 0U, 0U, 0U, 1U);
	ASSERT v[0U].ID == 1U;
	ASSERT v[1U].ID == 2U;
	ASSERT v[2U].ID == 3U;
	ASSERT v[3U].ID == 4U;

	Counter::Clear();
	v.Remove(1U);
	ASSERT AssertCapLen(v, 5U, 3U);
	ASSERT AssertCntrPod();
	ASSERT AssertCntrOnce(0U, 0U, 0U, 0U, 0U, 1U);
	ASSERT AssertCntrAlways(0U, 0U, 2U, 0U, 0U, 2U);
	ASSERT v[0U].ID == 1U;
	ASSERT v[1U].ID == 3U;
	ASSERT v[2U].ID == 4U;

	Counter::Clear();
	v.Remove(1U);
	ASSERT AssertCapLen(v, 5U, 2U);
	ASSERT AssertCntrPod();
	ASSERT AssertCntrOnce(0U, 0U, 0U, 0U, 0U, 1U);
	ASSERT AssertCntrAlways(0U, 0U, 1U, 0U, 0U, 2U);
	ASSERT v[0U].ID == 1U;
	ASSERT v[1U].ID == 4U;

	Counter::Clear();
	v.Remove(0U);
	ASSERT AssertCapLen(v, 5U, 1U);
	ASSERT AssertCntrPod();
	ASSERT AssertCntrOnce(0U, 0U, 0U, 0U, 0U, 1U);
	ASSERT AssertCntrAlways(0U, 0U, 1U, 0U, 0U, 2U);
	ASSERT v[0U].ID == 4U;

	Counter::Clear();
	v.Remove(0U);
	ASSERT AssertCapLen(v, 5U, 0U);
	ASSERT AssertCntrPod();
	ASSERT AssertCntrOnce(0U, 0U, 0U, 0U, 0U, 1U);
	ASSERT AssertCntrAlways(0U, 0U, 0U, 0U, 0U, 1U);

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
	ASSERT AssertCntrPod();
	ASSERT AssertCntrOnce(0U, 0U, 0U, 0U, 0U, 1U);
	ASSERT AssertCntrAlways(0U, 0U, 0U, 0U, 0U, 1U);
	ASSERT v[0U].ID == 1U;
	ASSERT v[1U].ID == 2U;
	ASSERT v[2U].ID == 3U;
	ASSERT v[3U].ID == 4U;

	Counter::Clear();
	v.Remove(v[1]);
	ASSERT AssertCapLen(v, 5U, 3U);
	ASSERT AssertCntrPod();
	ASSERT AssertCntrOnce(0U, 0U, 0U, 0U, 0U, 1U);
	ASSERT AssertCntrAlways(0U, 0U, 2U, 0U, 0U, 2U);
	ASSERT v[0U].ID == 1U;
	ASSERT v[1U].ID == 3U;
	ASSERT v[2U].ID == 4U;

	Counter::Clear();
	v.Remove(v[1]);
	ASSERT AssertCapLen(v, 5U, 2U);
	ASSERT AssertCntrPod();
	ASSERT AssertCntrOnce(0U, 0U, 0U, 0U, 0U, 1U);
	ASSERT AssertCntrAlways(0U, 0U, 1U, 0U, 0U, 2U);
	ASSERT v[0U].ID == 1U;
	ASSERT v[1U].ID == 4U;

	Counter::Clear();
	v.Remove(v[0]);
	ASSERT AssertCapLen(v, 5U, 1U);
	ASSERT AssertCntrPod();
	ASSERT AssertCntrOnce(0U, 0U, 0U, 0U, 0U, 1U);
	ASSERT AssertCntrAlways(0U, 0U, 1U, 0U, 0U, 2U);
	ASSERT v[0U].ID == 4U;

	Counter::Clear();
	v.Remove(v[0]);
	ASSERT AssertCapLen(v, 5U, 0U);
	ASSERT AssertCntrPod();
	ASSERT AssertCntrOnce(0U, 0U, 0U, 0U, 0U, 1U);
	ASSERT AssertCntrAlways(0U, 0U, 0U, 0U, 0U, 1U);

	return result;
}

} //namespace

using namespace VectorTestNamespace;

Bool VectorTest(VCntr::CtorModeEnum defaultMode)
{
	Bool result = true;

	VCntr::DefaultMode = defaultMode;

	ASSERT CtorEmptyTest();
	ASSERT CtorModeTest();
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

	ASSERT VectorTest(VCntr::Always);
	ASSERT VectorTest(VCntr::Once);
	ASSERT VectorTest(VCntr::Pod);

	return result;
}
