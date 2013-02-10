#include "../Core.hpp"

using namespace Core;

TChar const * _empty = Text("");
TChar const * _text = Text("This is CoreLib");
TChar const * _textSmaller = Text("A is smaller than T");
TChar const * _textGreater = Text("V is Greater than T");
TChar const * _textShorter = Text("Shorter");
TChar const * _textBigger = Text("Very much larger than _text");
UInt const _textcap = 16U;
UInt const _textlen = 15U;

namespace StringTestNamespace {

Bool AssertCapLen(String const & s, UInt capacity, UInt length)
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

	//No Capacity
	{
		String s((UInt)0U);
		ASSERT s.IsEmpty() == true;
		ASSERT AssertCapLen(s, 0U, 0U);
	}

	//Capacity
	{
		String s(10U);
		ASSERT s.IsEmpty() == true;
		ASSERT AssertCapLen(s, 10U, 0U);
	}

	return result;
}

Bool CtorTCharTest()
{
	Bool result = true;
	TChar const * nullTChar = NULL;

	//TChar NULL
	{
		String s(nullTChar);
		ASSERT s.IsEmpty() == true;
		ASSERT AssertCapLen(s, 0U, 0U);
	}

	//TChar Empty
	{
		String s(_empty);
		ASSERT s.IsEmpty() == true;
		ASSERT AssertCapLen(s, 0U, 0U);
	}

	//TChar not Empty
	{
		String s(_text);
		ASSERT s.IsEmpty() == false;
		ASSERT AssertCapLen(s, _textcap, _textlen);
	}

	return result;
}

Bool CtorCopyTest()
{
	Bool result = true;

	//Copy Empty
	{
		String s;
		String t(s);
		ASSERT t.IsEmpty() == true;
		ASSERT AssertCapLen(t, 0U, 0U);
	}

	//Copy not Empty
	{
		String s(_text);
		String t(s);
		ASSERT t.IsEmpty() == false;
		ASSERT AssertCapLen(t, _textcap, _textlen);
	}

	return result;
}

Bool CtorMoveTest()
{
	Bool result = true;

	//Move Empty
	{
		String s;
		String t((String&&)s);
		ASSERT s.IsEmpty() == true;
		ASSERT AssertCapLen(s, 0U, 0U);
	}

	//Move not Empty
	{
		String s(_text);
		String t((String&&)s);
		ASSERT s.IsEmpty() == true;
		ASSERT AssertCapLen(s, 0U, 0U);
		ASSERT t.IsEmpty() == false;
		ASSERT AssertCapLen(t, _textcap, _textlen);
	}

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
	{
		String s;
		ASSERT s.IsEmpty() == true;
	}

	//Empty with Capacity
	{
		String s(10U);
		ASSERT s.IsEmpty() == true;
	}

	//Not Empty
	{
		String s(_text);
		ASSERT s.IsEmpty() == false;
	}

	return result;
}

Bool GetCapacityTest()
{
	Bool result = true;

	//Empty
	{
		String s;
		ASSERT s.GetCapacity() == 0U;
	}

	//Capacity
	{
		String s(10U);
		ASSERT s.GetCapacity() == 10U;
	}

	return result;
}

Bool GetLengthTest()
{
	Bool result = true;

	//Empty
	{
		String s;
		ASSERT s.GetLength() == 0U;
	}

	//Empty with Capacity
	{
		String s(10U);
		ASSERT s.GetLength() == 0U;
	}

	//Not Empty
	{
		String s(_text);
		ASSERT s.GetLength() == _textlen;
	}

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
	{
	String s;
	ASSERT 0 == s.Compare(_empty);
	}

	//Empty to not empty
	{
		String s;
		ASSERT -1 == s.Compare(Text("Not Empty"));
	}

	//Not Empty to empty
	{
		String s(_text);
		ASSERT 1 == s.Compare(_empty);
	}

	//Not Empty to smaller
	{
		String s(_text);
		ASSERT 1 == s.Compare(_textSmaller);
	}

	//Not Empty to greater
	{
		String s(_text);
		ASSERT -1 == s.Compare(_textGreater);
	}

	//Not Empty to same
	{
		String s(_text);
		ASSERT 0 == s.Compare(_text);
	}

	return result;
}

Bool CompareStringTest()
{
	Bool result = true;

	//Empty to empty
	{
		String s;
		ASSERT 0 == s.Compare(String(_empty));
	}

	//Empty to not empty
	{
		String s;
		ASSERT -1 == s.Compare(String(Text("Not Empty")));
	}

	//Not Empty to empty
	{
		String s(_text);
		ASSERT 1 == s.Compare(String(_empty));
	}

	//Not Empty to smaller
	{
		String s(_text);
		ASSERT 1 == s.Compare(String(_textSmaller));
	}

	//Not Empty to greater
	{
		String s(_text);
		ASSERT -1 == s.Compare(String(_textGreater));
	}

	//Not Empty to same
	{
		String s(_text);
		ASSERT 0 == s.Compare(String(_text));
	}

	return result;
}

Bool OperatorAssignTCharTest()
{
	Bool result = true;
	UInt capacity;

	//Assign Empty to Empty
	{
		String t = _empty;
		ASSERT t.IsEmpty() == true;
		ASSERT AssertCapLen(t, 0U, 0U);
	}

	//Assign Empty to not Empty
	{
		String t(_text);
		capacity = t.GetCapacity();
		t = _empty;
		ASSERT t.IsEmpty() == true;
		ASSERT AssertCapLen(t, capacity, 0U);
	}

	//Assign not Empty to Empty
	{
		String t = _text;
		ASSERT t.IsEmpty() == false;
		ASSERT AssertCapLen(t, _textcap, _textlen);
	}

	//Assign bigger string to shorter string
	{
		String t(_text);
		t = _textBigger;
		capacity = String::GetTCharLength(_textBigger);
		ASSERT t.IsEmpty() == false;
		ASSERT AssertCapLen(t, capacity + 1, capacity);
	}

	//Assign shorter string to bigger string
	//Target capacity is same as before
	{
		String t(_text);
		capacity = t.GetCapacity();
		t = _textShorter;
		ASSERT t.IsEmpty() == false;
		ASSERT AssertCapLen(t, capacity, String::GetTCharLength(_textShorter));
	}

	return result;
}

Bool OperatorAssignStringTest()
{
	Bool result = true;
	UInt capacity;

	//Assign Empty to Empty
	{
		String s;
		String t = s;
		ASSERT t.IsEmpty() == true;
		ASSERT AssertCapLen(t, 0U, 0U);
	}

	//Assign Empty to not Empty
	{
		String s;
		String t(_text);
		capacity = t.GetCapacity();
		t = s;
		ASSERT t.IsEmpty() == true;
		ASSERT AssertCapLen(t, capacity, 0U);
	}

	//Assign not Empty to Empty
	{
		String s(_text);
		String t = s;
		ASSERT t.IsEmpty() == false;
		ASSERT AssertCapLen(t, _textcap, _textlen);
	}

	//Assign bigger string to shorter string
	{
		String s(_textBigger);
		String t(_text);
		t = s;
		ASSERT t.IsEmpty() == false;
		ASSERT AssertCapLen(t, s.GetCapacity(), s.GetLength());
	}

	//Assign shorter string to bigger string
	//Target capacity is same as before
	{
		String s(_textShorter);
		String t(_text);
		capacity = t.GetCapacity();
		t = s;
		ASSERT t.IsEmpty() == false;
		ASSERT AssertCapLen(t, capacity, s.GetLength());
	}

	return result;
}

Bool OperatorMoveStringTest()
{
	Bool result = true;

	//Move Empty to Empty
	{
		String s;
		String t((String&&)s);
		ASSERT s.IsEmpty() == true;
		ASSERT AssertCapLen(s, 0U, 0U);
	}

	//Move not Empty to Empty
	{
		String s(_text);
		String t((String&&)s);
		ASSERT s.IsEmpty() == true;
		ASSERT AssertCapLen(s, 0U, 0U);
		ASSERT t.IsEmpty() == false;
		ASSERT AssertCapLen(t, _textcap, _textlen);
	}

	//Move Empty to not Empty
	{
		String s;
		String t(_text);
		t = (String&&)s;
		ASSERT s.IsEmpty() == true;
		ASSERT AssertCapLen(s, 0U, 0U);
		ASSERT t.IsEmpty() == true;
		ASSERT AssertCapLen(t, 0U, 0U);
	}

	//Move not Empty to not Empty
	{
		String s(_text);
		String t(_text);
		t = (String&&)s;
		ASSERT s.IsEmpty() == true;
		ASSERT AssertCapLen(s, 0U, 0U);
		ASSERT t.IsEmpty() == false;
		ASSERT AssertCapLen(t, _textcap, _textlen);
	}

	return result;
}

Bool OperatorPlusEqualTCharTest()
{
	Bool result = true;

	//Empty += Empty
	{
		String s;
		s += _empty;
		ASSERT s.IsEmpty() == true;
		ASSERT AssertCapLen(s, 0U, 0U);
	}

	//Empty += Not Empty
	{
		String s;
		s += _text;
		ASSERT s.IsEmpty() == false;
		ASSERT AssertCapLen(s, _textcap, _textlen);
	}

	//Not Empty += Empty
	{
		String s(_text);
		s += _empty;
		ASSERT s.IsEmpty() == false;
		ASSERT AssertCapLen(s, _textcap, _textlen);
	}

	//Not Empty += Not Empty
	{
		String s(_text);
		s += _text;
		ASSERT s.IsEmpty() == false;
		ASSERT AssertCapLen(s, _textcap + _textcap - 1, _textlen + _textlen);
	}

	return result;
}

Bool OperatorPlusEqualStringTest()
{
	Bool result = true;

	//Empty += Empty
	{
		String t;
		String s;
		t += s;
		ASSERT t.IsEmpty() == true;
		ASSERT AssertCapLen(t, 0U, 0U);
	}

	//Empty += Not Empty
	{
		String t;
		String s(_text);
		t += s;
		ASSERT t.IsEmpty() == false;
		ASSERT AssertCapLen(t, _textcap, _textlen);
	}

	//Not Empty += Empty
	{
		String t(_text);
		String s;
		t += s;
		ASSERT t.IsEmpty() == false;
		ASSERT AssertCapLen(t, _textcap, _textlen);
	}

	//Not Empty += Not Empty
	{
		String t(_text);
		String s(_text);
		t += s;
		ASSERT t.IsEmpty() == false;
		ASSERT AssertCapLen(t, _textcap + _textcap - 1, _textlen + _textlen);
	}

	return result;
}

Bool OperatorPlusTCharTest()
{
	Bool result = true;

	//Empty + Empty
	{
		String s;
		String const & ref = s + _empty;
		ASSERT ref.IsEmpty() == true;
		ASSERT AssertCapLen(ref, 0U, 0U);
	}

	//Empty + Not Empty
	{
		String s;
		String const & ref = s + _text;
		ASSERT ref.IsEmpty() == false;
		ASSERT AssertCapLen(ref, _textcap, _textlen);
	}

	//Not Empty + Empty
	{
		String s(_text);
		String const & ref = s + _empty;
		ASSERT ref.IsEmpty() == false;
		ASSERT AssertCapLen(ref, _textcap, _textlen);
	}

	//Not Empty + Not Empty
	{
		String s(_text);
		String const & ref = s + _text;
		ASSERT ref.IsEmpty() == false;
		ASSERT AssertCapLen(ref, _textcap + _textcap - 1, _textlen + _textlen);
	}

	return result;
}

Bool OperatorPlusStringTest()
{
	Bool result = true;

	//Empty + Empty
	{
		String l;
		String r;
		String const & ref = l + r;
		ASSERT ref.IsEmpty() == true;
		ASSERT AssertCapLen(ref, 0U, 0U);
	}

	//Empty + Not Empty
	{
		String l;
		String r(_text);
		String const & ref = l + r;
		ASSERT ref.IsEmpty() == false;
		ASSERT AssertCapLen(ref, _textcap, _textlen);
	}

	//Not Empty + Empty
	{
		String l(_text);
		String r;
		String const & ref = l + r;
		ASSERT ref.IsEmpty() == false;
		ASSERT AssertCapLen(ref, _textcap, _textlen);
	}

	//Not Empty + Not Empty
	{
		String l(_text);
		String r(_text);
		String const & ref = l + r;
		ASSERT ref.IsEmpty() == false;
		ASSERT AssertCapLen(ref, _textcap + _textcap - 1, _textlen + _textlen);
	}

	return result;
}

Bool OperatorEqualTCharTest()
{
	Bool result = true;

	//Empty == Empty
	{
		String s;
		ASSERT s == _empty;
	}

	//Empty == Not Empty
	{
		String s;
		ASSERT !(s == _text);
	}

	//Not Empty == Empty
	{
		String s(_text);
		ASSERT !(s == _empty);
	}

	//Not Empty == Same
	{
		String s(_text);
		ASSERT s == _text;
	}

	//Not Empty == Different
	{
		String s(_text);
		ASSERT !(s == _textSmaller);
	}

	return result;
}

Bool OperatorEqualStringTest()
{
	Bool result = true;

	//Empty == Empty
	{
		String l;
		String r;
		ASSERT l == r;
	}

	//Empty == Not Empty
	{
		String l;
		String r(_text);
		ASSERT !(l == r);
	}

	//Not Empty == Empty
	{
		String l(_text);
		String r;
		ASSERT !(l == r);
	}

	//Not Empty == Same
	{
		String l(_text);
		String r(_text);
		ASSERT l == r;
	}

	//Not Empty == Different
	{
		String l(_text);
		String r(_textSmaller);
		ASSERT !(l == r);
	}

	return result;
}

Bool OperatorNotEqualTCharTest()
{
	Bool result = true;

	//Empty != Empty
	{
		String s;
		ASSERT !(s != _empty);
	}

	//Empty != Not Empty
	{
		String s;
		ASSERT s != _text;
	}

	//Not Empty != Empty
	{
		String s(_text);
		ASSERT s != _empty;
	}

	//Not Empty != Same
	{
		String s(_text);
		ASSERT !(s != _text);
	}

	//Not Empty != Different
	{
		String s(_text);
		ASSERT s != _textSmaller;
	}

	return result;
}

Bool OperatorNotEqualStringTest()
{
	Bool result = true;

	//Empty != Empty
	{
		String l;
		String r;
		ASSERT !(l != r);
	}

	//Empty != Not Empty
	{
		String l;
		String r(_text);
		ASSERT l != r;
	}

	//Not Empty != Empty
	{
		String l(_text);
		String r;
		ASSERT l != r;
	}

	//Not Empty != Same
	{
		String l(_text);
		String r(_text);
		ASSERT !(l != r);
	}

	//Not Empty != Different
	{
		String l(_text);
		String r(_textSmaller);
		ASSERT l != r;
	}

	return result;
}

Bool OperatorGreaterTCharTest()
{
	Bool result = true;

	//Empty > Empty
	{
		String s;
		ASSERT !(s > _empty);
	}

	//Empty > Not Empty
	{
		String s;
		ASSERT !(s > _text);
	}

	//Not Empty > Empty
	{
		String s(_text);
		ASSERT s > _empty;
	}

	//Not Empty > Same
	{
		String s(_text);
		ASSERT !(s > _text);
	}

	//Not Empty > Greater
	{
		String s(_text);
		ASSERT !(s > _textGreater);
	}

	//Not Empty > Smaller
	{
		String s(_text);
		ASSERT s > _textSmaller;
	}

	return result;
}

Bool OperatorGreaterStringTest()
{
	Bool result = true;

	//Empty > Empty
	{
		String s;
		String t;
		ASSERT !(s > t);
	}

	//Empty > Not Empty
	{
		String s;
		String t(_text);
		ASSERT !(s > t);
	}

	//Not Empty > Empty
	{
		String s(_text);
		String t;
		ASSERT s > t;
	}

	//Not Empty > Same
	{
		String s(_text);
		String t(_text);
		ASSERT !(s > t);
	}

	//Not Empty > Greater
	{
		String s(_text);
		String t(_textGreater);
		ASSERT !(s > t);
	}

	//Not Empty > Smaller
	{
		String s(_text);
		String t(_textSmaller);
		ASSERT s > t;
	}

	return result;
}

Bool OperatorSmallerTCharTest()
{
	Bool result = true;

	//Empty < Empty
	{
		String s;
		ASSERT !(s < _empty);
	}

	//Empty < Not Empty
	{
		String s;
		ASSERT s < _text;
	}

	//Not Empty < Empty
	{
		String s(_text);
		ASSERT !(s < _empty);
	}

	//Not Empty < Same
	{
		String s(_text);
		ASSERT !(s < _text);
	}

	//Not Empty < Greater
	{
		String s(_text);
		ASSERT s < _textGreater;
	}

	//Not Empty < Smaller
	{
		String s(_text);
		ASSERT !(s < _textSmaller);
	}

	return result;
}

Bool OperatorSmallerStringTest()
{
	Bool result = true;

	//Empty < Empty
	{
		String s;
		String t;
		ASSERT !(s < t);
	}

	//Empty < Not Empty
	{
		String s;
		String t(_text);
		ASSERT s < t;
	}

	//Not Empty < Empty
	{
		String s(_text);
		String t;
		ASSERT !(s < t);
	}

	//Not Empty < Same
	{
		String s(_text);
		String t(_text);
		ASSERT !(s < t);
	}

	//Not Empty < Greater
	{
		String s(_text);
		String t(_textGreater);
		ASSERT s < t;
	}

	//Not Empty < Smaller
	{
		String s(_text);
		String t(_textSmaller);
		ASSERT !(s < t);
	}

	return result;
}

Bool OperatorGreaterOrEqualTCharTest()
{
	Bool result = true;

	//Empty >= Empty
	{
		String s;
		ASSERT s >= _empty;
	}

	//Empty >= Not Empty
	{
		String s;
		ASSERT !(s >= _text);
	}

	//Not Empty >= Empty
	{
		String s(_text);
		ASSERT s >= _empty;
	}

	//Not Empty >= Same
	{
		String s(_text);
		ASSERT s >= _text;
	}

	//Not Empty >= Greater
	{
		String s(_text);
		ASSERT !(s >= _textGreater);
	}

	//Not Empty >= Smaller
	{
		String s(_text);
		ASSERT s >= _textSmaller;
	}

	return result;
}

Bool OperatorGreaterOrEqualStringTest()
{
	Bool result = true;

	//Empty >= Empty
	{
		String s;
		String t;
		ASSERT s >= t;
	}

	//Empty >= Not Empty
	{
		String s;
		String t(_text);
		ASSERT !(s >= t);
	}

	//Not Empty >= Empty
	{
		String s(_text);
		String t;
		ASSERT s >= t;
	}

	//Not Empty >= Same
	{
		String s(_text);
		String t(_text);
		ASSERT s >= t;
	}

	//Not Empty >= Greater
	{
		String s(_text);
		String t(_textGreater);
		ASSERT !(s >= t);
	}

	//Not Empty >= Smaller
	{
		String s(_text);
		String t(_textSmaller);
		ASSERT s >= t;
	}

	return result;
}

Bool OperatorSmallerOrEqualTCharTest()
{
	Bool result = true;

	//Empty <= Empty
	{
		String s;
		ASSERT s <= _empty;
	}

	//Empty <= Not Empty
	{
		String s;
		ASSERT s <= _text;
	}

	//Not Empty <= Empty
	{
		String s(_text);
		ASSERT !(s <= _empty);
	}

	//Not Empty <= Same
	{
		String s(_text);
		ASSERT s <= _text;
	}

	//Not Empty <= Greater
	{
		String s(_text);
		ASSERT s <= _textGreater;
	}

	//Not Empty <= Smaller
	{
		String s(_text);
		ASSERT !(s <= _textSmaller);
	}

	return result;
}

Bool OperatorSmallerOrEqualStringTest()
{
	Bool result = true;

	//Empty <= Empty
	{
		String s;
		String t;
		ASSERT s <= t;
	}

	//Empty <= Not Empty
	{
		String s;
		String t(_text);
		ASSERT s <= t;
	}

	//Not Empty <= Empty
	{
		String s(_text);
		String t;
		ASSERT !(s <= t);
	}

	//Not Empty <= Same
	{
		String s(_text);
		String t(_text);
		ASSERT s <= t;
	}

	//Not Empty <= Greater
	{
		String s(_text);
		String t(_textGreater);
		ASSERT s <= t;
	}

	//Not Empty <= Smaller
	{
		String s(_text);
		String t(_textSmaller);
		ASSERT !(s <= t);
	}

	return result;
}

Bool OperatoSubscriptTest()
{
	Bool result = true;

	String s(_text);
	ASSERT s[0U] == Text('T');
	ASSERT s[10U] == Text('r');

	return result;
}

Bool FormatBufferTest()
{
	Bool result = true;

	TChar const * format = Text("One hundred fifty seven : %d - %s");

	//Buffer is large enough
	{
		UInt const buffer_size = 128U;
		TChar buffer[buffer_size];

		String::Format(buffer, buffer_size, format, 157, Text("Done"));

		ASSERT 0 == String::Compare(Text("One hundred fifty seven : 157 - Done"), buffer);
	}

	//Buffer is too short, so the output was truncated
	{
		UInt const buffer_size = 24U;
		TChar buffer[buffer_size];

		String::Format(buffer, buffer_size, format, 157, Text("Done"));

		ASSERT 0 == String::Compare(Text("One hundred fifty seven"), buffer);
	}

	return result;
}

Bool FormatStringTest()
{
	Bool result = true;

	TChar const * format = Text("One hundred fifty seven : %d - %s");

	String str = String::FormatStr(format, 157, Text("Done"));

	ASSERT str.GetCapacity() == 37;
	ASSERT str.GetLength() == 36;
	ASSERT 0 == String::Compare(Text("One hundred fifty seven : 157 - Done"), str.GetTChar());

	return result;
}

Bool IndexOfTest()
{
	Bool result = true;

	String empty;
	String len[] = {Text("0"), Text("01"), Text("012")};
	TChar chr[] = {Text('0'), Text('1'), Text('2')};

	//Empty string
	ASSERT empty.IndexOf(chr[0]) == -1;

	//Position too small
	ASSERT len[0].IndexOf(chr[0], -10) == -1;

	//Position too big
	ASSERT len[0].IndexOf(chr[0], 10) == -1;

	//Length 1 - Not Found
	ASSERT len[0].IndexOf(chr[1]) == -1;

	//Length 1 - Found
	ASSERT len[0].IndexOf(chr[0]) == 0;

	//Length 2 - Found at beginning
	ASSERT len[1].IndexOf(chr[0]) == 0;

	//Length 2 - Found at end
	ASSERT len[1].IndexOf(chr[1]) == 1;

	//Length 2 - Not Found because of Position
	ASSERT len[1].IndexOf(chr[0], 1) == -1;

	//Length 2 - Found at Position
	ASSERT len[1].IndexOf(chr[1], 1) == 1;

	//Length 3 - Found at beginning
	ASSERT len[2].IndexOf(chr[0]) == 0;

	//Length 3 - Not Found because of Position
	ASSERT len[2].IndexOf(chr[0], 1) == -1;

	//Length 3 - Found at Position
	ASSERT len[2].IndexOf(chr[1], 1) == 1;

	//Length 3 - Found after Position
	ASSERT len[2].IndexOf(chr[2], 1) == 2;

	return result;
}

Bool LastIndexOfTest()
{
	Bool result = true;

	String empty;
	String len[] = {Text("0"), Text("01"), Text("012")};
	TChar chr[] = {Text('0'), Text('1'), Text('2')};

	//Empty string
	ASSERT empty.LastIndexOf(chr[0]) == -1;

	//Position too small
	ASSERT len[0].LastIndexOf(chr[0], -10) == -1;

	//Position too big
	ASSERT len[0].LastIndexOf(chr[0], 10) == -1;

	//Length 1 - Not Found
	ASSERT len[0].LastIndexOf(chr[1]) == -1;

	//Length 1 - Found
	ASSERT len[0].LastIndexOf(chr[0]) == 0;

	//Length 2 - Found at beginning
	ASSERT len[1].LastIndexOf(chr[0]) == 0;

	//Length 2 - Found at end
	ASSERT len[1].LastIndexOf(chr[1]) == 1;

	//Length 2 - Not Found because of Position
	ASSERT len[1].LastIndexOf(chr[0], 1) == -1;

	//Length 2 - Found at Position
	ASSERT len[1].LastIndexOf(chr[1], 1) == 1;

	//Length 3 - Found at beginning
	ASSERT len[2].LastIndexOf(chr[0]) == 0;

	//Length 3 - Not Found because of Position
	ASSERT len[2].LastIndexOf(chr[0], 1) == -1;

	//Length 3 - Found at Position
	ASSERT len[2].LastIndexOf(chr[1], 1) == 1;

	//Length 3 - Found after Position
	ASSERT len[2].LastIndexOf(chr[2], 1) == 2;

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

	ASSERT OperatorAssignTCharTest();
	ASSERT OperatorAssignStringTest();
	ASSERT OperatorMoveStringTest();
	ASSERT OperatorPlusEqualTCharTest();
	ASSERT OperatorPlusEqualStringTest();
	ASSERT OperatorPlusTCharTest();
	ASSERT OperatorPlusStringTest();

	ASSERT OperatorEqualTCharTest();
	ASSERT OperatorEqualStringTest();
	ASSERT OperatorNotEqualTCharTest();
	ASSERT OperatorNotEqualStringTest();

	ASSERT OperatorGreaterTCharTest();
	ASSERT OperatorGreaterStringTest();
	ASSERT OperatorSmallerTCharTest();
	ASSERT OperatorSmallerStringTest();

	ASSERT OperatorGreaterOrEqualTCharTest();
	ASSERT OperatorGreaterOrEqualStringTest();
	ASSERT OperatorSmallerOrEqualTCharTest();
	ASSERT OperatorSmallerOrEqualStringTest();

	ASSERT OperatoSubscriptTest();

	ASSERT FormatBufferTest();
	ASSERT FormatStringTest();

	ASSERT IndexOfTest();
	ASSERT LastIndexOfTest();

	return result;
}
