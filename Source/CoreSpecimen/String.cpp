#include "Core.hpp"

using namespace Core;

#define ASSERT result = result && 
TChar const * _empty = Text("");
TChar const * _text = Text("This is CoreLib");
TChar const * _textSmaller = Text("A is smaller than T");
TChar const * _textGreater = Text("V is Greater than T");
TChar const * _textShorter = Text("Shorter");
TChar const * _textBigger = Text("Very much larger than _text");
UInt const _textcap = 16U;
UInt const _textlen = 15U;

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
	TChar const * nullTChar = NULL;

	//TChar NULL
	String s1(nullTChar);
	ASSERT s1.IsEmpty() == true;
	ASSERT AssertCapLen(s1, 0U, 0U);

	//TChar Empty
	String s2(_empty);
	ASSERT s2.IsEmpty() == true;
	ASSERT AssertCapLen(s2, 0U, 0U);

	//TChar not Empty
	String s3(_text);
	ASSERT s3.IsEmpty() == false;
	ASSERT AssertCapLen(s3, _textcap, _textlen);

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
	ASSERT AssertCapLen(t2, _textcap, _textlen);

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
	ASSERT AssertCapLen(t2, _textcap, _textlen);

	return result;
}

Bool GetTCharLenTest()
{
	Bool result = true;

	//Null
	ASSERT String::GetTCharLength(NULL) == 0U;

	//Empty string Len == 1 for terminating character
	ASSERT String::GetTCharLength(_empty) == 0U;

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
	ASSERT String::Compare(_text, tc) == 0U;

	return result;
}

Bool CompareTCharTest()
{
	Bool result = true;

	//Empty to empty
	String s1;
	ASSERT 0 == s1.Compare(_empty);

	//Empty to not empty
	String s2;
	ASSERT -1 == s2.Compare(Text("Not Empty"));

	//Not Empty to empty
	String s3(_text);
	ASSERT 1 == s3.Compare(_empty);

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
	ASSERT 0 == s1.Compare(String(_empty));

	//Empty to not empty
	String s2;
	ASSERT -1 == s2.Compare(String(Text("Not Empty")));

	//Not Empty to empty
	String s3(_text);
	ASSERT 1 == s3.Compare(String(_empty));

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

Bool OperatorEqualStringTest()
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
	ASSERT AssertCapLen(t3, _textcap, _textlen);

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

Bool OperatorMoveStringTest()
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
	ASSERT AssertCapLen(t2, _textcap, _textlen);

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
	ASSERT AssertCapLen(t4, _textcap, _textlen);

	return result;
}

Bool OperatorEqualTCharTest()
{
	Bool result = true;
	UInt capacity;

	//Assign Empty to Empty
	String t1 = _empty;
	ASSERT t1.IsEmpty() == true;
	ASSERT AssertCapLen(t1, 0U, 0U);

	//Assign Empty to not Empty
	String t2(_text);
	capacity = t2.GetCapacity();
	t2 = _empty;
	ASSERT t2.IsEmpty() == true;
	ASSERT AssertCapLen(t2, capacity, 0U);

	//Assign not Empty to Empty
	String t3 = _text;
	ASSERT t3.IsEmpty() == false;
	ASSERT AssertCapLen(t3, _textcap, _textlen);

	//Assign bigger string to shorter string
	String t4(_text);
	t4 = _textBigger;
	capacity = String::GetTCharLength(_textBigger);
	ASSERT t4.IsEmpty() == false;
	ASSERT AssertCapLen(t4, capacity + 1, capacity);

	//Assign shorter string to bigger string
	//Target capacity is same as before
	String t5(_text);
	capacity = t5.GetCapacity();
	t5 = _textShorter;
	ASSERT t5.IsEmpty() == false;
	ASSERT AssertCapLen(t5, capacity, String::GetTCharLength(_textShorter));

	return result;
}

Bool OperatorPlusEqualStringTest()
{
	Bool result = true;

	//Empty += Empty
	String l1;
	String r1;
	l1 += r1;
	ASSERT l1.IsEmpty() == true;
	ASSERT AssertCapLen(l1, 0U, 0U);

	//Empty += Not Empty
	String l2;
	String r2(_text);
	l2 += r2;
	ASSERT l2.IsEmpty() == false;
	ASSERT AssertCapLen(l2, _textcap, _textlen);

	//Not Empty += Empty
	String l3(_text);
	String r3;
	l3 += r3;
	ASSERT l3.IsEmpty() == false;
	ASSERT AssertCapLen(l3, _textcap, _textlen);

	//Not Empty += Not Empty
	String l4(_text);
	String r4(_text);
	l4 += r4;
	ASSERT l4.IsEmpty() == false;
	ASSERT AssertCapLen(l4, _textcap + _textcap - 1, _textlen + _textlen);

	return result;
}

Bool OperatorPlusEqualTCharTest()
{
	Bool result = true;

	//Empty += Empty
	String l1;
	l1 += _empty;
	ASSERT l1.IsEmpty() == true;
	ASSERT AssertCapLen(l1, 0U, 0U);

	//Empty += Not Empty
	String l2;
	l2 += _text;
	ASSERT l2.IsEmpty() == false;
	ASSERT AssertCapLen(l2, _textcap, _textlen);

	//Not Empty += Empty
	String l3(_text);
	l3 += _empty;
	ASSERT l3.IsEmpty() == false;
	ASSERT AssertCapLen(l3, _textcap, _textlen);

	//Not Empty += Not Empty
	String l4(_text);
	l4 += _text;
	ASSERT l4.IsEmpty() == false;
	ASSERT AssertCapLen(l4, _textcap + _textcap - 1, _textlen + _textlen);

	return result;
}

Bool OperatorPlusStringTest()
{
	Bool result = true;

	//Empty + Empty
	String l1;
	String r1;
	String& s1 = l1 + r1;
	ASSERT s1.IsEmpty() == true;
	ASSERT AssertCapLen(s1, 0U, 0U);

	//Empty + Not Empty
	String l2;
	String r2(_text);
	String& s2 = l2 + r2;
	ASSERT s2.IsEmpty() == false;
	ASSERT AssertCapLen(s2, _textcap, _textlen);

	//Not Empty + Empty
	String l3(_text);
	String r3;
	String& s3 = l3 + r3;
	ASSERT s3.IsEmpty() == false;
	ASSERT AssertCapLen(s3, _textcap, _textlen);

	//Not Empty + Not Empty
	String l4(_text);
	String r4(_text);
	String& s4 = l4 + r4;
	ASSERT s4.IsEmpty() == false;
	ASSERT AssertCapLen(s4, _textcap + _textcap - 1, _textlen + _textlen);

	return result;
}

Bool OperatorPlusTCharTest()
{
	Bool result = true;

	//Empty + Empty
	String l1;
	String& s1 = l1 + _empty;
	ASSERT s1.IsEmpty() == true;
	ASSERT AssertCapLen(s1, 0U, 0U);

	//Empty + Not Empty
	String l2;
	String& s2 = l2 + _text;
	ASSERT s2.IsEmpty() == false;
	ASSERT AssertCapLen(s2, _textcap, _textlen);

	//Not Empty + Empty
	String l3(_text);
	String& s3 = l3 + _empty;
	ASSERT s3.IsEmpty() == false;
	ASSERT AssertCapLen(s3, _textcap, _textlen);

	//Not Empty + Not Empty
	String l4(_text);
	String& s4 = l4 + _text;
	ASSERT s4.IsEmpty() == false;
	ASSERT AssertCapLen(s4, _textcap + _textcap - 1, _textlen + _textlen);

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

	ASSERT OperatorEqualStringTest();
	ASSERT OperatorMoveStringTest();
	ASSERT OperatorEqualTCharTest();
	ASSERT OperatorPlusEqualStringTest();
	ASSERT OperatorPlusEqualTCharTest();
	ASSERT OperatorPlusStringTest();
	ASSERT OperatorPlusTCharTest();

	return result;
}
