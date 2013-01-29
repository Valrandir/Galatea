#define VectorUnitTest

#include "Core.hpp"

using namespace Core;

#define ASSERT result = result && 
TChar const * _text = Text("This is CoreLib");
TChar const * _textSmaller = Text("A is smaller than T");
TChar const * _textGreater = Text("V is Greater than T");
UInt const _len = 16U;

namespace StringTestNamespace {

Bool AssertCapLen(String& s, UInt capacity, UInt length)
{
	return s.GetCapacity() == capacity && s.GetLength() == length;
}

Bool CtorEmptyTest()
{
	Bool result = true;

	String s;
	ASSERT s.IsEmpty() == true;
	ASSERT AssertCapLen(s, 0U, 0U);

	return result;
}

Bool CtorCapacityTest()
{
	Bool result = true;

	String s1(0U);
	ASSERT s1.IsEmpty() == true;
	ASSERT AssertCapLen(s1, 0U, 0U);

	String s2(10U);
	ASSERT s2.IsEmpty() == true;
	ASSERT AssertCapLen(s2, 10U, 0U);

	return result;
}

Bool CtorTCharTest()
{
	Bool result = true;

	String s(_text);
	ASSERT s.IsEmpty() == false;
	ASSERT AssertCapLen(s, _len, _len);

	return result;
}

Bool CtorCopyTest()
{
	Bool result = true;

	//Copy Empty
	String s1;
	String t1(s1);
	ASSERT s1.IsEmpty() == true;
	ASSERT AssertCapLen(s1, 0U, 0U);

	//Copy not Empty
	String s2(_text);
	String t2(s2);
	ASSERT t2.IsEmpty() == false;
	ASSERT AssertCapLen(t2, _len, _len);

	return result;
}

Bool CtorMoveTest()
{
	Bool result = true;

	//Move Empty
	String s1;
	String t1((String&&)s1);
	ASSERT s1.IsEmpty() == true;
	ASSERT AssertCapLen(s1, 0U, 0U);

	//Move not Empty
	String s2(_text);
	String t2((String&&)s2);
	ASSERT s2.IsEmpty() == true;
	ASSERT AssertCapLen(s2, 0U, 0U);
	ASSERT t2.IsEmpty() == false;
	ASSERT AssertCapLen(t2, _len, _len);

	return result;
}

Bool IsEmptyTest()
{
	Bool result = true;

	//Empty
	String s1;
	ASSERT s1.IsEmpty() == true;

	//Empty with Capacity
	String s2(10U);
	ASSERT s2.IsEmpty() == true;

	//Not Empty
	String s3(_text);
	ASSERT s3.IsEmpty() == false;

	return result;
}

Bool GetCapacityTest()
{
	Bool result = true;

	//Empty
	String s1;
	ASSERT s1.GetCapacity() == 0U;

	//Capacity
	String s2(10U);
	ASSERT s2.GetCapacity() == 10U;

	return result;
}

Bool GetLengthTest()
{
	Bool result = true;

	//Empty
	String s1;
	ASSERT s1.GetLength() == 0U;

	//Empty with Capacity
	String s2(10U);
	ASSERT s2.GetLength() == 0U;

	//Not Empty
	String s3(_text);
	ASSERT s3.GetLength() == _len;

	return result;
}

Bool GetTCharTest()
{
	Bool result = true;

	String s(_text);
	TChar const * tc = s.GetTChar();

	ASSERT *_text == *tc;

	return result;
}

Bool CompareTCharTest()
{
	Bool result = true;

	//Empty to empty
	String s1;
	ASSERT 0 == s1.Compare(Text(""));

	//Empty to not empty
	String s2;
	ASSERT -1 == s2.Compare(Text("Not Empty"));

	//Not Empty to empty
	String s3(_text);
	ASSERT 1 == s3.Compare(Text(""));

	//Not Empty to smaller
	String s4(_text);
	ASSERT 1 == s3.Compare(_textSmaller);

	//Not Empty to greater
	String s5(_text);
	ASSERT -1 == s5.Compare(_textGreater);

	//Not Empty to same
	String s6(_text);
	ASSERT 0 == s6.Compare(_text);

	return result;
}

Bool CompareStringTest()
{
	Bool result = true;

	//Empty to empty
	String s1;
	ASSERT 0 == s1.Compare(String(Text("")));

	//Empty to not empty
	String s2;
	ASSERT -1 == s2.Compare(String(Text("Not Empty")));

	//Not Empty to empty
	String s3(_text);
	ASSERT 1 == s3.Compare(String(Text("")));

	//Not Empty to smaller
	String s4(_text);
	ASSERT 1 == s3.Compare(String(_textSmaller));

	//Not Empty to greater
	String s5(_text);
	ASSERT -1 == s5.Compare(String(_textGreater));

	//Not Empty to same
	String s6(_text);
	ASSERT 0 == s6.Compare(String(_text));

	return result;
}

} //namespace

using namespace StringTestNamespace;

Bool StringTest()
{
	Bool result = true;

	ASSERT CtorEmptyTest();
	ASSERT CtorCapacityTest();
	ASSERT CtorTCharTest();
	ASSERT CtorCopyTest();
	ASSERT CtorMoveTest();

	ASSERT IsEmptyTest();
	ASSERT GetCapacityTest();
	ASSERT GetLengthTest();
	ASSERT GetTCharTest();

	ASSERT CompareTCharTest();
	ASSERT CompareStringTest();

	return result;
}
