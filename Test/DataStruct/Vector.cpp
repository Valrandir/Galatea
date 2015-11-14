#define VectorUnitTest

#include "../Core.hpp"
#include "Counter.hpp"

using namespace Core;
using namespace DataStruct;

typedef Vector<Counter> VCntr;

namespace VectorTestNamespace
{
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
		return v.Capacity() == capacity && v.Length() == length;
	}

	Bool AssertCntrAlways(UInt construct = 0U, UInt copyConstruct = 0U, UInt moveConstruct = 0U, UInt operatorEqual = 0U, UInt operatorMove = 0U, UInt destruct = 0U)
	{
		if(VCntr::DefaultMode == VCntr::CtorModeEnum::Always)
			return Counter::Compare(construct, copyConstruct, moveConstruct, operatorEqual, operatorMove, destruct);
		else
			return true;
	}

	Bool AssertCntrOnce(UInt construct = 0U, UInt copyConstruct = 0U, UInt moveConstruct = 0U, UInt operatorEqual = 0U, UInt operatorMove = 0U, UInt destruct = 0U)
	{
		if(VCntr::DefaultMode == VCntr::CtorModeEnum::Once)
			return Counter::Compare(construct, copyConstruct, moveConstruct, operatorEqual, operatorMove, destruct);
		else
			return true;
	}

	Bool AssertCntrPod(UInt construct = 0U, UInt copyConstruct = 0U, UInt moveConstruct = 0U, UInt operatorEqual = 0U, UInt operatorMove = 0U, UInt destruct = 0U)
	{
		if(VCntr::DefaultMode == VCntr::CtorModeEnum::Pod)
			return Counter::Compare(construct, copyConstruct, moveConstruct, operatorEqual, operatorMove, destruct);
		else
			return true;
	}

	Bool AssertCntrZero()
	{
		Bool result = true;
		CHECK AssertCntrPod();
		CHECK AssertCntrOnce();
		CHECK AssertCntrAlways();
		return result;
	}

	Bool AssertBeginEndNull(VCntr& v)
	{
		Bool result = true;
		VCntr const & c = v;

		CHECK v.Begin() == NULL && v.End() == NULL;
		CHECK c.Begin() == NULL && c.End() == NULL;
		CHECK v.RBegin() == v.End() - 1 && v.REnd() == v.Begin() - 1;
		CHECK c.RBegin() == c.End() - 1 && c.REnd() == c.Begin() - 1;

		return result;
	}

	Bool AssertBeginEndNotNull(VCntr& v)
	{
		Bool result = true;
		VCntr const & c = v;

		CHECK v.Begin() && v.End() == v.Begin() + v.Length();
		CHECK c.Begin() && c.End() == c.Begin() + c.Length();
		CHECK v.RBegin() && v.REnd() == v.RBegin() - v.Length();
		CHECK c.RBegin() && c.REnd() == c.RBegin() - c.Length();

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

		CHECK i == length;
		CHECK j == length;
		CHECK k == length;
		CHECK l == length;

		return result;
	}

	Bool CtorEmptyTest()
	{
		Counter::Clear();

		Bool result = true;
		VCntr vc;

		CHECK AssertCntrZero();
		CHECK AssertCapLen(vc, 0U, 0U);
		CHECK vc.CtorMode() == VCntr::DefaultMode;
		CHECK AssertBeginEndNull(vc);

		return result;
	}

	Bool CtorModeTest()
	{
		Bool result = true;
		VCntr vc(VCntr::CtorModeEnum::Once);

		CHECK vc.CtorMode() == VCntr::CtorModeEnum::Once;

		return result;
	}

	Bool CtorCapacityTest()
	{
		Counter::Clear();

		Bool result = true;
		VCntr vc(10U);

		CHECK AssertCntrZero();
		CHECK AssertCapLen(vc, 10U, 0U);
		CHECK AssertBeginEndNotNull(vc);

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
			CHECK AssertCntrZero();
			CHECK AssertCapLen(target, 0U, 0U);
			CHECK AssertBeginEndNull(target);
		}

		//Copy Vector with capacity 5 and no elements
		{
			VCntr source(5U);
			Counter::Clear();
			VCntr target(source);
			CHECK AssertCntrZero();
			CHECK AssertCapLen(target, 0U, 0U);
			CHECK AssertBeginEndNull(target);
		}

		//Copy Vector with 5 elements
		{
			VCntr source(5U);
			AddFiveElements(source);
			Counter::Clear();
			VCntr target(source);
			CHECK AssertCntrPod();
			CHECK AssertCntrOnce();
			CHECK AssertCntrAlways(0U, 5U, 0U, 0U, 0U, 0U);
			CHECK AssertCapLen(target, 5U, 5U);
			CHECK AssertBeginEndNotNull(target);
		}

		//Copy Pod vector
		{
			VCntr source(VCntr::CtorModeEnum::Pod);
			VCntr target(source);
			CHECK target.CtorMode() == VCntr::CtorModeEnum::Pod;
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
			CHECK AssertCntrZero();
			CHECK AssertCapLen(target, 0U, 0U);
			CHECK AssertBeginEndNull(target);
	}

		//Move Vector with capacity 5 and no elements
		{
			VCntr source(5U);
			Counter::Clear();
			VCntr target((VCntr&&)source);
			CHECK AssertCntrZero();
			CHECK AssertCapLen(target, 0U, 0U);
			CHECK AssertBeginEndNull(target);
		}

		//Move Vector with 5 elements
		{
			VCntr source(5U);
			AddFiveElements(source);
			Counter::Clear();
			VCntr target((VCntr&&)source);
			CHECK AssertCntrZero();
			CHECK AssertCapLen(target, 5U, 5U);
			CHECK AssertBeginEndNotNull(target);
			CHECK AssertCapLen(source, 0U, 0U);
			CHECK AssertBeginEndNull(source);
		}

		//Move Pod vector
		{
			VCntr source(VCntr::CtorModeEnum::Pod);
			VCntr target((VCntr&&)source);
			CHECK target.CtorMode() == VCntr::CtorModeEnum::Pod;
		}

		return result;
	}

	Bool CtorRangeTest()
	{
		Bool result = true;

		//Construct with zero element
		{
			VCntr source;
			Counter::Clear();
			CHECK_ASSERT(VCntr target(source.Begin(), source.End()));
		}

		//Construct with five elements
		{
			VCntr source;
			AddFiveElements(source);
			Counter::Clear();
			VCntr target(source.Begin(), source.End());
			CHECK AssertCntrPod();
			CHECK AssertCntrOnce(0U, 5U, 0U, 0U, 0U, 0U);
			CHECK AssertCntrAlways(0U, 5U, 0U, 0U, 0U, 0U);
			CHECK AssertCapLen(target, 5U, 5U);
			CHECK AssertBeginEndNotNull(target);
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
			CHECK AssertCntrZero();
			CHECK AssertCapLen(target, 0U, 0U);
			CHECK AssertBeginEndNull(target);
		}

		//Assign Vector with capacity 5 and no elements to empty vector
		{
			VCntr source(5U);
			Counter::Clear();
			VCntr target = source;
			CHECK AssertCntrZero();
			CHECK AssertCapLen(target, 0U, 0U);
			CHECK AssertBeginEndNull(target);
		}

		//Assign Vector with 5 elements to empty vector
		{
			VCntr source;
			AddFiveElements(source);
			Counter::Clear();
			VCntr target = source;
			CHECK AssertCntrPod();
			CHECK AssertCntrOnce();
			CHECK AssertCntrAlways(0U, 5U, 0U, 0U, 0U, 0U);
			CHECK AssertCapLen(target, 5U, 5U);
			CHECK AssertBeginEndNotNull(target);
		}

		//Assign empty vector to vector with 5 elements
		{
			VCntr source, target;
			AddFiveElements(target);
			Counter::Clear();
			target = source;
			CHECK AssertCntrPod();
			CHECK AssertCntrOnce(0U, 0U, 0U, 0U, 0U, 5U);
			CHECK AssertCntrAlways(0U, 0U, 0U, 0U, 0U, 5U);
			CHECK AssertCapLen(target, 0U, 0U);
			CHECK AssertBeginEndNull(target);
		}

		//Assign Vector with capacity 5 and no elements to vector with 5 elements
		{
			VCntr source(5U), target;
			AddFiveElements(target);
			Counter::Clear();
			target = source;
			CHECK AssertCntrPod();
			CHECK AssertCntrOnce(0U, 0U, 0U, 0U, 0U, 5U);
			CHECK AssertCntrAlways(0U, 0U, 0U, 0U, 0U, 5U);
			CHECK AssertCapLen(target, 0U, 0U);
			CHECK AssertBeginEndNull(target);
		}

		//Assign Vector with 5 elements to vector with 5 elements
		{
			VCntr source, target;
			AddFiveElements(source);
			AddFiveElements(target);
			Counter::Clear();
			target = source;
			CHECK AssertCntrPod();
			CHECK AssertCntrOnce(0U, 0U, 0U, 0U, 0U, 5U);
			CHECK AssertCntrAlways(0U, 5U, 0U, 0U, 0U, 5U);
			CHECK AssertCapLen(target, 5U, 5U);
			CHECK AssertBeginEndNotNull(target);
		}

		//Assign Pod vector
		{
			VCntr source(VCntr::CtorModeEnum::Pod);
			VCntr target = source;
			CHECK target.CtorMode() == VCntr::CtorModeEnum::Pod;
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
			CHECK AssertCntrZero();
			CHECK AssertCapLen(source, 0U, 0U);
			CHECK AssertBeginEndNull(source);
		}

		//Assign Vector with capacity 5 and no elements
		{
			VCntr target(5U);
			Counter::Clear();
			VCntr source = (VCntr&&)target;
			CHECK AssertCntrZero();
			CHECK AssertCapLen(source, 0U, 0U);
			CHECK AssertBeginEndNull(source);
		}

		//Assign Vector with 5 elements
		{
			VCntr target(5U);
			AddFiveElements(target);
			Counter::Clear();
			VCntr source = (VCntr&&)target;
			CHECK AssertCntrZero();
			CHECK AssertCapLen(source, 5U, 5U);
			CHECK AssertBeginEndNotNull(source);
		}

		//Assign Pod vector
		{
			VCntr target(VCntr::CtorModeEnum::Pod);
			VCntr source = (VCntr&&)target;
			CHECK source.CtorMode() == VCntr::CtorModeEnum::Pod;
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
			CHECK AssertCntrZero();
			CHECK AssertCapLen(target, 0U, 0U);
			CHECK AssertBeginEndNull(target);
		}

		//Append empty to not empty
		{
			VCntr source, target;
			AddFiveElements(target);
			Counter::Clear();
			target += source;
			CHECK AssertCntrZero();
			CHECK AssertCapLen(target, 5U, 5U);
			CHECK AssertBeginEndNotNull(target);
		}

		//Append not empty to empty
		{
			VCntr source, target;
			AddFiveElements(source);
			Counter::Clear();
			target += source;
			CHECK AssertCntrPod();
			CHECK AssertCntrOnce(0U, 5U, 0U, 0U, 0U, 0U);
			CHECK AssertCntrAlways(0U, 5U, 0U, 0U, 0U, 0U);
			CHECK AssertCapLen(target, 5U, 5U);
			CHECK AssertBeginEndNotNull(target);
		}

		//Append not empty to not empty
		{
			VCntr source, target;
			AddFiveElements(target);
			AddFiveElements(source);
			Counter::Clear();
			target += source;
			CHECK AssertCntrPod();
			CHECK AssertCntrOnce(0U, 5U, 0U, 0U, 0U, 0U);
			CHECK AssertCntrAlways(0U, 5U, 5U, 0U, 0U, 5U);
			CHECK AssertCapLen(target, 10U, 10U);
			CHECK AssertBeginEndNotNull(target);
		}

		return result;
	}

	Bool OperatorSubscriptTest()
	{
		Bool result = true;

		//Empty Vector, Assert
		{
			VCntr v;
			CHECK_ASSERT(v[0]);
		}

		//Index Out of Range, Assert
		{
			VCntr v;
			AddFiveElements(v);
			CHECK_ASSERT(v[10]);
		}

		//Return Element
		{
			VCntr v;
			AddFiveElements(v);
			CHECK v[0U]._id == 1U;
			CHECK v[4U]._id == 5U;
		}

		return result;
	}

	Bool OperatorSubscriptConstTest()
	{
		Bool result = true;

		//Empty Vector, Assert
		{
			const VCntr v;
			CHECK_ASSERT(v[0]);
		}

		//Index Out of range, Assert
		{
			VCntr v;
			AddFiveElements(v);
			VCntr const vc(v);
			CHECK_ASSERT(vc[10]);
		}

		//Return Element
		{
			VCntr v;
			AddFiveElements(v);
			VCntr const vc(v);
			CHECK vc[0U]._id == 1U;
			CHECK vc[4U]._id == 5U;
		}

		return result;
	}

	Bool GetCtorModeTest()
	{
		Bool result = true;

		//Specify mode obtain same mode
		{
			VCntr v(VCntr::CtorModeEnum::Pod);
			CHECK v.CtorMode() == VCntr::CtorModeEnum::Pod;
		}

		//Don't specify mode obtain default
		{
			VCntr v;
			CHECK v.CtorMode() == VCntr::DefaultMode;
		}

		return result;
	}

	Bool IsEmptyTest()
	{
		Bool result = true;

		//No Capacity
		{
			VCntr v;
			CHECK v.IsEmpty() == true;
		}

		//Capacity and no elements
		{
			VCntr v(10U);
			CHECK v.IsEmpty() == true;
		}

		//Capacity and elements
		{
			VCntr v(10U);
			v.Add(Counter());
			CHECK v.IsEmpty() == false;
		}

		return result;
	}

	Bool CapacityTest()
	{
		Bool result = true;

		//No Capacity Specified
		{
			VCntr v;
			CHECK v.Capacity() == 0;
		}

		//Capacity Specified
		{
			VCntr v(10U);
			CHECK v.Capacity() == 10U;
		}

		return result;
	}

	Bool LengthTest()
	{
		Bool result = true;

		//No Capacity
		{
			VCntr v;
			CHECK v.Length() == 0;
		}

		//Capacity
		{
			VCntr v(10U);
			CHECK v.Length() == 0U;
		}

		//Length
		{
			VCntr v(10U);
			v.Add(Counter());
			CHECK v.Length() == 1U;
		}

		return result;
	}

	Bool IteratorsTest()
	{
		Bool result = true;

		//No Capacity
		{
			VCntr v;
			CHECK AssertBeginEndNull(v);
		}

		//Capacity
		{
			VCntr v(10U);
			CHECK AssertCapLen(v, 10U, 0U);
			CHECK AssertBeginEndNotNull(v);
			CHECK AssertIteratageLength(v, 0U);
		}

		//Length == 1
		{
			VCntr v(10U);
			v.Add(Counter());
			CHECK AssertCapLen(v, 10U, 1U);
			CHECK AssertBeginEndNotNull(v);
			CHECK AssertIteratageLength(v, 1U);
		}

		//Length == 5
		{
			VCntr v(15U);
			AddFiveElements(v);
			CHECK AssertCapLen(v, 15U, 5U);
			CHECK AssertBeginEndNotNull(v);
			CHECK AssertIteratageLength(v, 5U);
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
			CHECK v.Capacity() == 10U;
		}

		//Reserve 10 to a vector having 15
		{
			VCntr v(15U);
			v.Reserve(10U);
			CHECK v.Capacity() == 15U;
		}

		return result;
	}

	Bool ShrinkTest()
	{
		Bool result = true;

		//Capacity 10 Length 0
		{
			VCntr v(10U);
			Counter::Clear();
			v.Shrink();
			CHECK v.IsEmpty();
			CHECK AssertCapLen(v, 0U, 0U);
			CHECK AssertCntrZero();
		}

		//Capacity 10 Length 5
		{
			VCntr v(10U);
			AddFiveElements(v);
			Counter::Clear();
			v.Shrink();
			CHECK AssertCapLen(v, 5U, 5U);
			CHECK AssertCntrPod();
			CHECK AssertCntrOnce();
			CHECK AssertCntrAlways(0U, 0U, 5U, 0U, 0U, 5U);
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
			CHECK AssertCntrZero();
			CHECK AssertCapLen(v, 0U, 0U);
		}

		//Capacity
		{
			VCntr v(10U);
			Counter::Clear();
			v.Clear();
			CHECK AssertCntrZero();
			CHECK AssertCapLen(v, 10U, 0U);
		}

		//Length
		{
			VCntr v(10U);
			AddFiveElements(v);
			Counter::Clear();
			v.Clear();
			CHECK AssertCntrPod();
			CHECK AssertCntrOnce(0U, 0U, 0U, 0U, 0U, 5U);
			CHECK AssertCntrAlways(0U, 0U, 0U, 0U, 0U, 5U);
			CHECK AssertCapLen(v, 10U, 0U);
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
			CHECK AssertCntrZero();
			CHECK AssertCapLen(v, 0U, 0U);
		}

		//Capacity
		{
			VCntr v(10U);
			Counter::Clear();
			v.Free();
			CHECK AssertCntrZero();
			CHECK AssertCapLen(v, 0U, 0U);
		}

		//Length
		{
			VCntr v(10U);
			AddFiveElements(v);
			Counter::Clear();
			v.Free();
			CHECK AssertCntrPod();
			CHECK AssertCntrOnce(0U, 0U, 0U, 0U, 0U, 5U);
			CHECK AssertCntrAlways(0U, 0U, 0U, 0U, 0U, 5U);
			CHECK AssertCapLen(v, 0U, 0U);
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
		CHECK AssertCapLen(v, 2U, 1U);
		CHECK AssertCntrPod(0U, 0U, 0U, 1U, 0U, 0U);
		CHECK AssertCntrOnce(0U, 1U, 0U, 0U, 0U, 0U);
		CHECK AssertCntrAlways(0U, 1U, 0U, 0U, 0U, 0U);
		CHECK v[0U]._id == 1U;

		Counter::Clear();
		v.Add(c2);
		CHECK AssertCapLen(v, 2U, 2U);
		CHECK AssertCntrPod(0U, 0U, 0U, 1U, 0U, 0U);
		CHECK AssertCntrOnce(0U, 1U, 0U, 0U, 0U, 0U);
		CHECK AssertCntrAlways(0U, 1U, 0U, 0U, 0U, 0U);
		CHECK v[1U]._id == 2U;

		Counter::Clear();
		v.Add(c3);
		CHECK AssertCapLen(v, 4U, 3U);
		CHECK AssertCntrPod(0U, 0U, 0U, 1U, 0U, 0U);
		CHECK AssertCntrOnce(0U, 1U, 0U, 0U, 0U, 0U);
		CHECK AssertCntrAlways(0U, 1U, 2U, 0U, 0U, 2U);
		CHECK v[2U]._id == 3U;

		return result;
	}

	Bool AddRangeTest()
	{
		Bool result = true;

		//Append empty to empty
		{
			VCntr source, target;
			Counter::Clear();
			CHECK_ASSERT(target.AddRange(source.Begin(), source.End()));
		}

		//Append empty to not empty
		{
			VCntr source, target;
			AddFiveElements(target);
			Counter::Clear();
			CHECK_ASSERT(target.AddRange(source.Begin(), source.End()));
		}

		//Append not empty to empty
		{
			VCntr source, target;
			AddFiveElements(source);
			Counter::Clear();
			target.AddRange(source.Begin(), source.End());
			CHECK AssertCntrPod();
			CHECK AssertCntrOnce(0U, 5U, 0U, 0U, 0U, 0U);
			CHECK AssertCntrAlways(0U, 5U, 0U, 0U, 0U, 0U);
			CHECK AssertCapLen(target, 5U, 5U);
			CHECK AssertBeginEndNotNull(target);
		}

		//Append not empty to not empty
		{
			VCntr source, target;
			AddFiveElements(target);
			AddFiveElements(source);
			Counter::Clear();
			target.AddRange(source.Begin(), source.End());
			CHECK AssertCntrPod();
			CHECK AssertCntrOnce(0U, 5U, 0U, 0U, 0U, 0U);
			CHECK AssertCntrAlways(0U, 5U, 5U, 0U, 0U, 5U);
			CHECK AssertCapLen(target, 10U, 10U);
			CHECK AssertBeginEndNotNull(target);
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
		CHECK AssertCapLen(v, 2U, 1U);
		CHECK AssertCntrPod(0U, 0U, 0U, 1U, 0U, 0U);
		CHECK AssertCntrOnce(0U, 1U, 0U, 0U, 0U, 0U);
		CHECK AssertCntrAlways(0U, 1U, 0U, 0U, 0U, 0U);
		CHECK v[0U]._id == 1U;

		Counter::Clear();
		v.Insert(100U, c2);
		CHECK AssertCapLen(v, 2U, 2U);
		CHECK AssertCntrPod(0U, 0U, 0U, 1U, 0U, 0U);
		CHECK AssertCntrOnce(0U, 1U, 0U, 0U, 0U, 0U);
		CHECK AssertCntrAlways(0U, 1U, 0U, 0U, 0U, 0U);
		CHECK v[1U]._id == 2U;

		Counter::Clear();
		v.Insert(0U, c3);
		CHECK AssertCapLen(v, 4U, 3U);
		CHECK AssertCntrPod(0U, 0U, 0U, 1U, 0U, 0U);
		CHECK AssertCntrOnce(0U, 1U, 0U, 0U, 0U, 0U);
		CHECK AssertCntrAlways(0U, 1U, 4U, 0U, 0U, 2U);
		CHECK v[0U]._id == 3U;
		CHECK v[1U]._id == 1U;
		CHECK v[2U]._id == 2U;

		Counter::Clear();
		v.Insert(1U, c4);
		CHECK AssertCapLen(v, 4U, 4U);
		CHECK AssertCntrPod(0U, 0U, 0U, 1U, 0U, 0U);
		CHECK AssertCntrOnce(0U, 1U, 0U, 0U, 0U, 0U);
		CHECK AssertCntrAlways(0U, 1U, 2U, 0U, 0U, 0U);
		CHECK v[0U]._id == 3U;
		CHECK v[1U]._id == 4U;
		CHECK v[2U]._id == 1U;
		CHECK v[3U]._id == 2U;

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
		CHECK AssertCapLen(v, 8U, 6U);
		CHECK AssertCntrPod(0U, 0U, 0U, 1U, 0U, 0U);
		CHECK AssertCntrOnce(0U, 1U, 0U, 0U, 0U, 0U);
		CHECK AssertCntrAlways(0U, 1U, 1U, 0U, 0U, 0U);
		CHECK v[0U]._id == 1U;
		CHECK v[1U]._id == 2U;
		CHECK v[2U]._id == 3U;
		CHECK v[3U]._id == 4U;
		CHECK v[4U]._id == 6U;
		CHECK v[5U]._id == 5U;

		Counter::Clear();
		v.Insert(v[0], c2);
		CHECK AssertCapLen(v, 8U, 7U);
		CHECK AssertCntrPod(0U, 0U, 0U, 1U, 0U, 0U);
		CHECK AssertCntrOnce(0U, 1U, 0U, 0U, 0U, 0U);
		CHECK AssertCntrAlways(0U, 1U, 6U, 0U, 0U, 0U);
		CHECK v[0U]._id == 7U;
		CHECK v[1U]._id == 1U;
		CHECK v[2U]._id == 2U;
		CHECK v[3U]._id == 3U;
		CHECK v[4U]._id == 4U;
		CHECK v[5U]._id == 6U;
		CHECK v[6U]._id == 5U;

		Counter::Clear();
		v.Insert(v[3], c3);
		CHECK AssertCapLen(v, 8U, 8U);
		CHECK AssertCntrPod(0U, 0U, 0U, 1U, 0U, 0U);
		CHECK AssertCntrOnce(0U, 1U, 0U, 0U, 0U, 0U);
		CHECK AssertCntrAlways(0U, 1U, 4U, 0U, 0U, 0U);
		CHECK v[0U]._id == 7U;
		CHECK v[1U]._id == 1U;
		CHECK v[2U]._id == 2U;
		CHECK v[3U]._id == 8U;
		CHECK v[4U]._id == 3U;
		CHECK v[5U]._id == 4U;
		CHECK v[6U]._id == 6U;
		CHECK v[7U]._id == 5U;

		Counter::Clear();
		v.Insert(v[6], c4);
		CHECK AssertCapLen(v, 16U, 9U);
		CHECK AssertCntrPod(0U, 0U, 0U, 1U, 0U, 0U);
		CHECK AssertCntrOnce(0U, 1U, 0U, 0U, 0U, 0U);
		CHECK AssertCntrAlways(0U, 1U, 10U, 0U, 0U, 8U);
		CHECK v[0U]._id == 7U;
		CHECK v[1U]._id == 1U;
		CHECK v[2U]._id == 2U;
		CHECK v[3U]._id == 8U;
		CHECK v[4U]._id == 3U;
		CHECK v[5U]._id == 4U;
		CHECK v[6U]._id == 9U;
		CHECK v[7U]._id == 6U;
		CHECK v[8U]._id == 5U;

		return result;
	}

	Bool RemoveByIndexTest()
	{
		Bool result = true;
		VCntr v;

		AddFiveElements(v);

		Counter::Clear();
		v.Remove(100U);
		CHECK AssertCapLen(v, 5U, 4U);
		CHECK AssertCntrPod();
		CHECK AssertCntrOnce(0U, 0U, 0U, 0U, 0U, 1U);
		CHECK AssertCntrAlways(0U, 0U, 0U, 0U, 0U, 1U);
		CHECK v[0U]._id == 1U;
		CHECK v[1U]._id == 2U;
		CHECK v[2U]._id == 3U;
		CHECK v[3U]._id == 4U;

		Counter::Clear();
		v.Remove(1U);
		CHECK AssertCapLen(v, 5U, 3U);
		CHECK AssertCntrPod();
		CHECK AssertCntrOnce(0U, 0U, 0U, 0U, 0U, 1U);
		CHECK AssertCntrAlways(0U, 0U, 2U, 0U, 0U, 2U);
		CHECK v[0U]._id == 1U;
		CHECK v[1U]._id == 3U;
		CHECK v[2U]._id == 4U;

		Counter::Clear();
		v.Remove(1U);
		CHECK AssertCapLen(v, 5U, 2U);
		CHECK AssertCntrPod();
		CHECK AssertCntrOnce(0U, 0U, 0U, 0U, 0U, 1U);
		CHECK AssertCntrAlways(0U, 0U, 1U, 0U, 0U, 2U);
		CHECK v[0U]._id == 1U;
		CHECK v[1U]._id == 4U;

		Counter::Clear();
		v.Remove(0U);
		CHECK AssertCapLen(v, 5U, 1U);
		CHECK AssertCntrPod();
		CHECK AssertCntrOnce(0U, 0U, 0U, 0U, 0U, 1U);
		CHECK AssertCntrAlways(0U, 0U, 1U, 0U, 0U, 2U);
		CHECK v[0U]._id == 4U;

		Counter::Clear();
		v.Remove(0U);
		CHECK AssertCapLen(v, 5U, 0U);
		CHECK AssertCntrPod();
		CHECK AssertCntrOnce(0U, 0U, 0U, 0U, 0U, 1U);
		CHECK AssertCntrAlways(0U, 0U, 0U, 0U, 0U, 1U);

		return result;
	}

	Bool RemoveByRefTest()
	{
		Bool result = true;
		VCntr v;

		AddFiveElements(v);

		Counter::Clear();
		v.Remove(v[4]);
		CHECK AssertCapLen(v, 5U, 4U);
		CHECK AssertCntrPod();
		CHECK AssertCntrOnce(0U, 0U, 0U, 0U, 0U, 1U);
		CHECK AssertCntrAlways(0U, 0U, 0U, 0U, 0U, 1U);
		CHECK v[0U]._id == 1U;
		CHECK v[1U]._id == 2U;
		CHECK v[2U]._id == 3U;
		CHECK v[3U]._id == 4U;

		Counter::Clear();
		v.Remove(v[1]);
		CHECK AssertCapLen(v, 5U, 3U);
		CHECK AssertCntrPod();
		CHECK AssertCntrOnce(0U, 0U, 0U, 0U, 0U, 1U);
		CHECK AssertCntrAlways(0U, 0U, 2U, 0U, 0U, 2U);
		CHECK v[0U]._id == 1U;
		CHECK v[1U]._id == 3U;
		CHECK v[2U]._id == 4U;

		Counter::Clear();
		v.Remove(v[1]);
		CHECK AssertCapLen(v, 5U, 2U);
		CHECK AssertCntrPod();
		CHECK AssertCntrOnce(0U, 0U, 0U, 0U, 0U, 1U);
		CHECK AssertCntrAlways(0U, 0U, 1U, 0U, 0U, 2U);
		CHECK v[0U]._id == 1U;
		CHECK v[1U]._id == 4U;

		Counter::Clear();
		v.Remove(v[0]);
		CHECK AssertCapLen(v, 5U, 1U);
		CHECK AssertCntrPod();
		CHECK AssertCntrOnce(0U, 0U, 0U, 0U, 0U, 1U);
		CHECK AssertCntrAlways(0U, 0U, 1U, 0U, 0U, 2U);
		CHECK v[0U]._id == 4U;

		Counter::Clear();
		v.Remove(v[0]);
		CHECK AssertCapLen(v, 5U, 0U);
		CHECK AssertCntrPod();
		CHECK AssertCntrOnce(0U, 0U, 0U, 0U, 0U, 1U);
		CHECK AssertCntrAlways(0U, 0U, 0U, 0U, 0U, 1U);

		return result;
	}
}

Bool VectorTest(VCntr::CtorModeEnum defaultMode)
{
	using namespace VectorTestNamespace;
	Bool result = true;

	VCntr::DefaultMode = defaultMode;

	CHECK CtorEmptyTest();
	CHECK CtorModeTest();
	CHECK CtorCapacityTest();
	CHECK CtorCopyTest();
	CHECK CtorMoveTest();
	CHECK CtorRangeTest();

	CHECK OperatorEqualTest();
	CHECK OperatorMoveTest();
	CHECK OperatorPlusEqualTest();
	CHECK OperatorSubscriptTest();
	CHECK OperatorSubscriptConstTest();

	CHECK GetCtorModeTest();
	CHECK IsEmptyTest();
	CHECK CapacityTest();
	CHECK LengthTest();

	CHECK IteratorsTest();

	CHECK ReserveTest();
	CHECK ShrinkTest();
	CHECK ClearTest();
	CHECK FreeTest();

	CHECK AddTest();
	CHECK AddRangeTest();
	CHECK InsertByIndexTest();
	CHECK InsertByRefTest();
	CHECK RemoveByIndexTest();
	CHECK RemoveByRefTest();

	return result;
}

Bool VectorTest()
{
	Bool result = true;

	CHECK VectorTest(VCntr::Always);
	CHECK VectorTest(VCntr::Once);
	CHECK VectorTest(VCntr::Pod);

	return result;
}
