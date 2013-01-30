#include "Core.hpp"

using namespace Core;

#define ASSERT result = result && 
TChar const * _text = Text("This is CoreLib");
TChar const * _textSmaller = Text("A is smaller than T");
TChar const * _textGreater = Text("V is Greater than T");
TChar const * _textShorter = Text("Shorter");
TChar const * _textBigger = Text("Very much larger than _text");
UInt const _textlen = 16U;

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
	ASSERT AssertCapLen(s, _textlen, _textlen);

	return result;
}

Bool CtorCopyTest()
{
	Bool result = true;

	//Copy Empty
	String s1;
	String t1(s1);
	ASSERT t1.IsEmpty() == true;
	ASSERT AssertCapLen(t1, 0U, 0U);

	//Copy not Empty
	String s2(_text);
	String t2(s2);
	ASSERT t2.IsEmpty() == false;
	ASSERT AssertCapLen(t2, _textlen, _textlen);

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
	ASSERT AssertCapLen(t2, _textlen, _textlen);

	return result;
}

Bool GetTCharLenTest()
{
	Bool result = true;

	//Null
	ASSERT String::GetTCharLength(NULL) == 0U;

	//Empty string Len == 1 for terminating character
	ASSERT String::GetTCharLength(Text("")) == 1U;

	//Len == _textlen
	ASSERT String::GetTCharLength(_text) == _textlen;

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
	ASSERT s3.GetLength() == _textlen;

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

Bool OperatorEqualTest()
{
	Bool result = true;
	UInt capacity;

	//Assign Empty to Empty
	String s1;
	String t1 = s1;
	ASSERT t1.IsEmpty() == true;
	ASSERT AssertCapLen(t1, 0U, 0U);

	//Assign Empty to not Empty
	String s2;
	String t2(_text);
	capacity = t2.GetCapacity();
	t2 = s2;
	ASSERT t2.IsEmpty() == true;
	ASSERT AssertCapLen(t2, capacity, 0U);

	//Assign not Empty to Empty
	String s3(_text);
	String t3 = s3;
	ASSERT t3.IsEmpty() == false;
	ASSERT AssertCapLen(t3, _textlen, _textlen);

	//Assign bigger string to shorter string
	String s4(_textBigger);
	String t4(_text);
	t4 = s4;
	ASSERT t4.IsEmpty() == false;
	ASSERT AssertCapLen(t4, s4.GetCapacity(), s4.GetLength());

	//Assign shorter string to bigger string
	//Target capacity is same as before
	String s5(_textShorter);
	String t5(_text);
	capacity = t5.GetCapacity();
	t5 = s5;
	ASSERT t5.IsEmpty() == false;
	ASSERT AssertCapLen(t5, capacity, s5.GetLength());

	return result;
}

Bool OperatorMoveTest()
{
	Bool result = true;

	//Move Empty to Empty
	String s1;
	String t1((String&&)s1);
	ASSERT s1.IsEmpty() == true;
	ASSERT AssertCapLen(s1, 0U, 0U);

	//Move not Empty to Empty
	String s2(_text);
	String t2((String&&)s2);
	ASSERT s2.IsEmpty() == true;
	ASSERT AssertCapLen(s2, 0U, 0U);
	ASSERT t2.IsEmpty() == false;
	ASSERT AssertCapLen(t2, _textlen, _textlen);

	//Move Empty to not Empty
	String s3;
	String t3(_text);
	t3 = (String&&)s3;
	ASSERT s3.IsEmpty() == true;
	ASSERT AssertCapLen(s3, 0U, 0U);
	ASSERT t3.IsEmpty() == true;
	ASSERT AssertCapLen(t3, 0U, 0U);

	//Move not Empty to not Empty
	String s4(_text);
	String t4(_text);
	t4 = (String&&)s4;
	ASSERT s4.IsEmpty() == true;
	ASSERT AssertCapLen(s4, 0U, 0U);
	ASSERT t4.IsEmpty() == false;
	ASSERT AssertCapLen(t4, _textlen, _textlen);

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

	ASSERT GetTCharLenTest();
	ASSERT IsEmptyTest();
	ASSERT GetCapacityTest();
	ASSERT GetLengthTest();
	ASSERT GetTCharTest();

	ASSERT CompareTCharTest();
	ASSERT CompareStringTest();

	ASSERT OperatorEqualTest();
	ASSERT OperatorMoveTest();

	return result;
}
