#include "../Galatea.hpp"

using namespace Galatea;

namespace StringTestNamespace
{
	CStr _empty = Text("");
	CStr _space = Text(" ");
	CStr _text = Text("This is CoreLib");
	CStr _textSmaller = Text("A is smaller than T");
	CStr _textGreater = Text("V is Greater than T");
	CStr _textShorter = Text("Shorter");
	CStr _textLonger = Text("Very much larger than _text");
	UInt const _textcap = 16U;
	UInt const _textlen = 15U;

	/******************************************************************************/
	/* Testing Tools **************************************************************/
	/******************************************************************************/

	Bool CheckCapLen(String const & s, UInt capacity, UInt length)
	{
		return s.Capacity() == capacity && s.Length() == length;
	}

	/******************************************************************************/
	/* public static **************************************************************/
	/******************************************************************************/

	Bool CStrLengthTest()
	{
		Bool result = true;

		//Null
		CHECK_ASSERT(CHECK String::CStrLength(NULL) == 0U);

		//Empty
		CHECK String::CStrLength(_empty) == 0U;

		//Len == _textlen
		CHECK String::CStrLength(_text) == _textlen;

		return result;
	}

	Bool CStrByteSizeTest()
	{
		Bool result = true;

		//Null
		CHECK_ASSERT(CHECK String::CStrByteSize(NULL) == 0U);

		//Empty
		CHECK String::CStrByteSize(_empty) == 0U;

		//Len == _textlen
		CHECK String::CStrByteSize(_text) == _textlen * sizeof(TChar);

		return result;
	}

	Bool FormatBufferTest()
	{
		Bool result = true;

		CStr format = Text("One hundred fifty seven : %d - %s");

		//Invalid Parameters
		CHECK_ASSERT(String::FormatToBuffer(NULL, 0, NULL));

		//Buffer is large enough
		{
			UInt const buffer_size = 128U;
			TChar buffer[buffer_size];

			String::FormatToBuffer(buffer, buffer_size, format, 157, Text("Done"));

			CHECK 0 == String::Compare(Text("One hundred fifty seven : 157 - Done"), buffer);
		}

		//Buffer is too short, so the output was truncated
		{
			UInt const buffer_size = 24U;
			TChar buffer[buffer_size];

			String::FormatToBuffer(buffer, buffer_size, format, 157, Text("Done"));

			CHECK 0 == String::Compare(Text("One hundred fifty seven"), buffer);
		}

		return result;
	}

	Bool FormatStringTest()
	{
		Bool result = true;

		//Invalid Parameters
		CHECK_ASSERT(String::FormatToString(NULL));

		//All is good
		{
			CStr format = Text("One hundred fifty seven : %d - %s");

			String str = String::FormatToString(format, 157, Text("Done"));

			CHECK str.Length() == 36U;
			CHECK 0 == String::Compare(Text("One hundred fifty seven : 157 - Done"), str.CStrPtr());
		}

		return result;
	}

	Bool CompareTest()
	{
		Bool result = true;

		//static Compare -> source is null
		{
			CHECK_ASSERT(String::Compare(NULL, _empty));
		}

		//static Compare -> target is null
		{
			CHECK_ASSERT(String::Compare(_empty, NULL));
		}

		//instance Compare -> target is null
		{
			String s;
			CHECK_ASSERT(s.Compare(NULL));
		}

		//Empty to empty
		{
			String s;
			CHECK 0 == s.Compare(_empty);
		}

		//Empty to not empty
		{
			String s;
			CHECK -1 == s.Compare(Text("Not Empty"));
		}

		//Not Empty to empty
		{
			String s(_text);
			CHECK 1 == s.Compare(_empty);
		}

		//Not Empty to smaller
		{
			String s(_text);
			CHECK 1 == s.Compare(_textSmaller);
		}

		//Not Empty to greater
		{
			String s(_text);
			CHECK -1 == s.Compare(_textGreater);
		}

		//Not Empty to same
		{
			String s(_text);
			CHECK 0 == s.Compare(_text);
		}

		return result;
	}

	Bool MaxLengthTest()
	{
		Bool result = true;

		UInt noMatch = String::NoMatch;
		UInt maxSize = String::MaxSize;

		CHECK maxSize == noMatch - 1;

		return result;
	}

	/******************************************************************************/
	/* Constructors && Destructor *************************************************/
	/******************************************************************************/

	Bool CtorEmptyTest()
	{
		Bool result = true;

		String s;
		CHECK s.IsEmpty() == true;
		CHECK CheckCapLen(s, 0U, 0U);
		CHECK s.CStrPtr() == String::Empty;
		CHECK s == _empty;

		return result;
	}

	Bool CtorCapacityTest()
	{
		Bool result = true;

		//No Capacity
		{
			String s((UInt)0U);
			CHECK s.IsEmpty() == true;
			CHECK CheckCapLen(s, 0U, 0U);
			CHECK s.CStrPtr() == String::Empty;
			CHECK s == _empty;
		}

		//Capacity
		{
			String s(10U);
			CHECK s.IsEmpty() == true;
			CHECK CheckCapLen(s, 10U, 0U);
			CHECK s.CStrPtr() != 0;
			CHECK String::Compare(s, _empty) == 0;
		}

		return result;
	}

	Bool CtorCStrTest()
	{
		Bool result = true;

		//CStr Null
		{
			CHECK_ASSERT(String s((CStr)NULL));
		}

		//CStr Empty
		{
			String s(_empty);
			CHECK s.IsEmpty() == true;
			CHECK CheckCapLen(s, 0U, 0U);
			CHECK s.CStrPtr() == String::Empty;
		}

		//CStr not Empty
		{
			String s(_text);
			CHECK s.IsEmpty() == false;
			CHECK CheckCapLen(s, _textcap, _textlen);
			CHECK s == _text;
		}

		return result;
	}

	Bool CtorCStrLengthTest()
	{
		Bool result = true;

		//value null and length 10
		{
			CHECK_ASSERT(String s((CStr)NULL, 10U));
		}

		//CStr Null and Length 0
		{
			String s((CStr)NULL, (UInt)0U);
			CHECK s.IsEmpty() == true;
			CHECK CheckCapLen(s, 0U, 0U);
			CHECK s.CStrPtr() == String::Empty;
		}

		//CStr not Empty
		{
			String s(_text, _textlen);
			CHECK s.IsEmpty() == false;
			CHECK CheckCapLen(s, _textcap, _textlen);
			CHECK s == _text;
		}

		return result;
	}

	Bool CtorRangeTest()
	{
		Bool result = true;

		//Invalid Parameters
		{
			CHECK_ASSERT(String s((CStr)0, (CStr)0));
			CHECK_ASSERT(String s((CStr)16, (CStr)8));
		}

		//Range makes empty string
		{
			String s(_text + 5, _text + 5);
			CHECK s == _empty;
		}

		//Range makes string
		{
			String s(_text + 5, _text + 7);
			CHECK s == Text("is");
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
			CHECK t.IsEmpty() == true;
			CHECK CheckCapLen(t, 0U, 0U);
		}

		//Copy not Empty
		{
			String s(_text);
			String t(s);
			CHECK t.IsEmpty() == false;
			CHECK CheckCapLen(t, _textcap, _textlen);
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
			CHECK s.IsEmpty() == true;
			CHECK CheckCapLen(s, 0U, 0U);
		}

		//Move not Empty
		{
			String s(_text);
			String t((String&&)s);
			CHECK s.IsEmpty() == true;
			CHECK CheckCapLen(s, 0U, 0U);
			CHECK t.IsEmpty() == false;
			CHECK CheckCapLen(t, _textcap, _textlen);
		}

		return result;
	}

	/******************************************************************************/
	/* Operators ******************************************************************/
	/******************************************************************************/

	Bool OperatorCastToCStrTest()
	{
		Bool result = true;

		String s(_text);
		CStr cstr = s;
		CHECK s.Compare(cstr) == 0;

		return result;
	}

	Bool OperatorAssignCStrTest()
	{
		Bool result = true;
		UInt capacity;

		//Assign Null
		{
			CHECK_ASSERT(String t = (CStr)NULL);
		}

		//Assign Empty to Empty
		{
			String t = _empty;
			CHECK t.IsEmpty() == true;
			CHECK CheckCapLen(t, 0U, 0U);
		}

		//Assign Empty to not Empty
		{
			String t(_text);
			capacity = t.Capacity();
			t = _empty;
			CHECK t.IsEmpty() == true;
			CHECK CheckCapLen(t, capacity, 0U);
		}

		//Assign not Empty to Empty
		{
			String t = _text;
			CHECK t.IsEmpty() == false;
			CHECK CheckCapLen(t, _textcap, _textlen);
		}

		//Assign bigger string to shorter string
		{
			String t(_text);
			t = _textLonger;
			capacity = String::CStrLength(_textLonger);
			CHECK t.IsEmpty() == false;
			CHECK CheckCapLen(t, capacity + 1, capacity);
		}

		//Assign shorter string to bigger string
		//Target capacity is same as before
		{
			String t(_text);
			capacity = t.Capacity();
			t = _textShorter;
			CHECK t.IsEmpty() == false;
			CHECK CheckCapLen(t, capacity, String::CStrLength(_textShorter));
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
			CHECK t.IsEmpty() == true;
			CHECK CheckCapLen(t, 0U, 0U);
		}

		//Assign Empty to not Empty
		{
			String s;
			String t(_text);
			capacity = t.Capacity();
			t = s;
			CHECK t.IsEmpty() == true;
			CHECK CheckCapLen(t, capacity, 0U);
		}

		//Assign not Empty to Empty
		{
			String s(_text);
			String t = s;
			CHECK t.IsEmpty() == false;
			CHECK CheckCapLen(t, _textcap, _textlen);
		}

		//Assign bigger string to shorter string
		{
			String s(_textLonger);
			String t(_text);
			t = s;
			CHECK t.IsEmpty() == false;
			CHECK CheckCapLen(t, s.Capacity(), s.Length());
		}

		//Assign shorter string to bigger string
		//Target capacity is same as before
		{
			String s(_textShorter);
			String t(_text);
			capacity = t.Capacity();
			t = s;
			CHECK t.IsEmpty() == false;
			CHECK CheckCapLen(t, capacity, s.Length());
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
			CHECK s.IsEmpty() == true;
			CHECK CheckCapLen(s, 0U, 0U);
		}

		//Move not Empty to Empty
		{
			String s(_text);
			String t((String&&)s);
			CHECK s.IsEmpty() == true;
			CHECK CheckCapLen(s, 0U, 0U);
			CHECK t.IsEmpty() == false;
			CHECK CheckCapLen(t, _textcap, _textlen);
		}

		//Move Empty to not Empty
		{
			String s;
			String t(_text);
			t = (String&&)s;
			CHECK s.IsEmpty() == true;
			CHECK CheckCapLen(s, 0U, 0U);
			CHECK t.IsEmpty() == true;
			CHECK CheckCapLen(t, 0U, 0U);
		}

		//Move not Empty to not Empty
		{
			String s(_text);
			String t(_text);
			t = (String&&)s;
			CHECK s.IsEmpty() == true;
			CHECK CheckCapLen(s, 0U, 0U);
			CHECK t.IsEmpty() == false;
			CHECK CheckCapLen(t, _textcap, _textlen);
		}

		return result;
	}

	Bool OperatorPlusEqualCStrTest()
	{
		Bool result = true;

		//Empty += NULL
		{
			String s;
			CHECK_ASSERT(s += (CStr)NULL);
		}

		//Empty += Empty
		{
			String s;
			s += _empty;
			CHECK s.IsEmpty() == true;
			CHECK CheckCapLen(s, 0U, 0U);
			CHECK s == _empty;
		}

		//Empty += Not Empty
		{
			String s;
			s += _text;
			CHECK s.IsEmpty() == false;
			CHECK CheckCapLen(s, _textcap, _textlen);
			CHECK s == _text;
		}

		//Not Empty += Empty
		{
			String s(_text);
			s += _empty;
			CHECK s.IsEmpty() == false;
			CHECK CheckCapLen(s, _textcap, _textlen);
			CHECK s == _text;
		}

		//Not Empty += Not Empty
		{
			String s(_text);
			s += _text;
			CHECK s.IsEmpty() == false;
			CHECK CheckCapLen(s, _textcap + _textcap - 1, _textlen + _textlen);
			CHECK s == String(_text) + _text;
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
			CHECK t.IsEmpty() == true;
			CHECK CheckCapLen(t, 0U, 0U);
			CHECK t == _empty;
		}

		//Empty += Not Empty
		{
			String t;
			String s(_text);
			t += s;
			CHECK t.IsEmpty() == false;
			CHECK CheckCapLen(t, _textcap, _textlen);
			CHECK t == _text;
		}

		//Not Empty += Empty
		{
			String t(_text);
			String s;
			t += s;
			CHECK t.IsEmpty() == false;
			CHECK CheckCapLen(t, _textcap, _textlen);
			CHECK t == _text;
		}

		//Not Empty += Not Empty
		{
			String t(_text);
			String s(_text);
			t += s;
			CHECK t.IsEmpty() == false;
			CHECK CheckCapLen(t, _textcap + _textcap - 1, _textlen + _textlen);
			CHECK t == String(_text) + _text;
		}

		return result;
	}

	Bool OperatorPlusCStrTest()
	{
		Bool result = true;

		//Empty += NULL
		{
			String s;
			CHECK_ASSERT(String const & ref = s + (CStr)NULL);
		}

		//Empty + Empty
		{
			String s;
			String const & ref = s + _empty;
			CHECK ref.IsEmpty() == true;
			CHECK CheckCapLen(ref, 0U, 0U);
		}

		//Empty + Not Empty
		{
			String s;
			String const & ref = s + _text;
			CHECK ref.IsEmpty() == false;
			CHECK CheckCapLen(ref, _textcap, _textlen);
		}

		//Not Empty + Empty
		{
			String s(_text);
			String const & ref = s + _empty;
			CHECK ref.IsEmpty() == false;
			CHECK CheckCapLen(ref, _textcap, _textlen);
		}

		//Not Empty + Not Empty
		{
			String s(_text);
			String const & ref = s + _text;
			CHECK ref.IsEmpty() == false;
			CHECK CheckCapLen(ref, _textcap + _textcap - 1, _textlen + _textlen);
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
			CHECK ref.IsEmpty() == true;
			CHECK CheckCapLen(ref, 0U, 0U);
		}

		//Empty + Not Empty
		{
			String l;
			String r(_text);
			String const & ref = l + r;
			CHECK ref.IsEmpty() == false;
			CHECK CheckCapLen(ref, _textcap, _textlen);
		}

		//Not Empty + Empty
		{
			String l(_text);
			String r;
			String const & ref = l + r;
			CHECK ref.IsEmpty() == false;
			CHECK CheckCapLen(ref, _textcap, _textlen);
		}

		//Not Empty + Not Empty
		{
			String l(_text);
			String r(_text);
			String const & ref = l + r;
			CHECK ref.IsEmpty() == false;
			CHECK CheckCapLen(ref, _textcap + _textcap - 1, _textlen + _textlen);
		}

		return result;
	}

	Bool OperatorEqualCStrTest()
	{
		Bool result = true;

		//Empty == Empty
		{
			String s;
			CHECK s == _empty;
		}

		//Empty == Not Empty
		{
			String s;
			CHECK !(s == _text);
		}

		//Not Empty == Empty
		{
			String s(_text);
			CHECK !(s == _empty);
		}

		//Not Empty == Same
		{
			String s(_text);
			CHECK s == _text;
		}

		//Not Empty == Different
		{
			String s(_text);
			CHECK !(s == _textSmaller);
		}

		return result;
	}

	Bool OperatorNotEqualCStrTest()
	{
		Bool result = true;

		//Empty != Empty
		{
			String s;
			CHECK !(s != _empty);
		}

		//Empty != Not Empty
		{
			String s;
			CHECK s != _text;
		}

		//Not Empty != Empty
		{
			String s(_text);
			CHECK s != _empty;
		}

		//Not Empty != Same
		{
			String s(_text);
			CHECK !(s != _text);
		}

		//Not Empty != Different
		{
			String s(_text);
			CHECK s != _textSmaller;
		}

		return result;
	}

	Bool OperatorGreaterCStrTest()
	{
		Bool result = true;

		//Empty > Empty
		{
			String s;
			CHECK !(s > _empty);
		}

		//Empty > Not Empty
		{
			String s;
			CHECK !(s > _text);
		}

		//Not Empty > Empty
		{
			String s(_text);
			CHECK s > _empty;
		}

		//Not Empty > Same
		{
			String s(_text);
			CHECK !(s > _text);
		}

		//Not Empty > Greater
		{
			String s(_text);
			CHECK !(s > _textGreater);
		}

		//Not Empty > Smaller
		{
			String s(_text);
			CHECK s > _textSmaller;
		}

		return result;
	}

	Bool OperatorSmallerCStrTest()
	{
		Bool result = true;

		//Empty < Empty
		{
			String s;
			CHECK !(s < _empty);
		}

		//Empty < Not Empty
		{
			String s;
			CHECK s < _text;
		}

		//Not Empty < Empty
		{
			String s(_text);
			CHECK !(s < _empty);
		}

		//Not Empty < Same
		{
			String s(_text);
			CHECK !(s < _text);
		}

		//Not Empty < Greater
		{
			String s(_text);
			CHECK s < _textGreater;
		}

		//Not Empty < Smaller
		{
			String s(_text);
			CHECK !(s < _textSmaller);
		}

		return result;
	}

	Bool OperatorGreaterOrEqualCStrTest()
	{
		Bool result = true;

		//Empty >= Empty
		{
			String s;
			CHECK s >= _empty;
		}

		//Empty >= Not Empty
		{
			String s;
			CHECK !(s >= _text);
		}

		//Not Empty >= Empty
		{
			String s(_text);
			CHECK s >= _empty;
		}

		//Not Empty >= Same
		{
			String s(_text);
			CHECK s >= _text;
		}

		//Not Empty >= Greater
		{
			String s(_text);
			CHECK !(s >= _textGreater);
		}

		//Not Empty >= Smaller
		{
			String s(_text);
			CHECK s >= _textSmaller;
		}

		return result;
	}

	Bool OperatorSmallerOrEqualCStrTest()
	{
		Bool result = true;

		//Empty <= Empty
		{
			String s;
			CHECK s <= _empty;
		}

		//Empty <= Not Empty
		{
			String s;
			CHECK s <= _text;
		}

		//Not Empty <= Empty
		{
			String s(_text);
			CHECK !(s <= _empty);
		}

		//Not Empty <= Same
		{
			String s(_text);
			CHECK s <= _text;
		}

		//Not Empty <= Greater
		{
			String s(_text);
			CHECK s <= _textGreater;
		}

		//Not Empty <= Smaller
		{
			String s(_text);
			CHECK !(s <= _textSmaller);
		}

		return result;
	}

	Bool OperatorSubscriptTest()
	{
		Bool result = true;

		//Empty String, Assert
		{
			String s;
			CHECK_ASSERT(s[0U]);
		}

		//Index Out of Range, Assert
		{
			String s(_text);
			CHECK_ASSERT(s[512U]);
		}

		//Return Element
		{
			String s(_text);
			CHECK s[0U] == Text('T');
			CHECK s[10U] == Text('r');
		}

		return result;
	}

	/******************************************************************************/
	/* Public Const Functions *****************************************************/
	/******************************************************************************/

	Bool IsEmptyTest()
	{
		Bool result = true;

		//Empty
		{
			String s;
			CHECK s.IsEmpty() == true;
		}

		//Empty with Capacity
		{
			String s(10U);
			CHECK s.IsEmpty() == true;
		}

		//Not Empty
		{
			String s(_text);
			CHECK s.IsEmpty() == false;
		}

		return result;
	}

	Bool CapacityTest()
	{
		Bool result = true;

		//Empty
		{
			String s;
			CHECK s.Capacity() == 0U;
		}

		//Capacity
		{
			String s(10U);
			CHECK s.Capacity() == 10U;
		}

		return result;
	}

	Bool LengthTest()
	{
		Bool result = true;

		//Empty
		{
			String s;
			CHECK s.Length() == 0U;
		}

		//Empty with Capacity
		{
			String s(10U);
			CHECK s.Length() == 0U;
		}

		//Not Empty
		{
			String s(_text);
			CHECK s.Length() == _textlen;
		}

		return result;
	}

	Bool CStrPtrTest()
	{
		Bool result = true;

		//String Empty
		{
			String s;
			CHECK String::Compare(s.CStrPtr(), String::Empty) == 0;
		}

		//String Not Empty
		{
			String s(_text);
			CHECK String::Compare(s.CStrPtr(), _text) == 0;
		}

		return result;
	}

	Bool ClearTest()
	{
		Bool result = true;

		//Clear on empty string
		{
			String s;
			s.Clear();
			CHECK CheckCapLen(s, 0U, 0U);
		}

		//Clear on non-empty string
		{
			String s = _text;
			s.Clear();
			CHECK CheckCapLen(s, _textcap, 0U);
			CHECK s == _empty;
		}

		return result;
	}

	Bool StartsWithLengthTest()
	{
		Bool result = true;
		String text;
		UInt length;

		//text is empty
		CHECK String::StartsWith(_empty, 0U, _space) == false;

		//text is empty, startText is empty
		CHECK String::StartsWith(_empty, 0U, _empty) == true;

		text = Text("[Hello]");
		length = 7U;

		//text not empty, startText empty
		CHECK String::StartsWith(text, length, _empty) == true;

		//startText is unmatching single character
		CHECK String::StartsWith(text, length, Text("{")) == false;

		//startText is unmatching multiple character
		CHECK String::StartsWith(text, length, Text("//")) == false;

		//startText is matching single character
		CHECK String::StartsWith(text, length, Text("[")) == true;

		//startText is matching multiple character
		CHECK String::StartsWith(text, length, Text("[Hello]")) == true;

		return result;
	}

	Bool StartsWithTest()
	{
		Bool result = true;
		String text;

		//text is empty
		CHECK text.StartsWith(_space) == false;

		//text is empty, startText is empty
		CHECK text.StartsWith(_empty) == true;

		text = Text("[Hello]");

		//text not empty, startText empty
		CHECK text.StartsWith(_empty) == true;

		//startText is unmatching single character
		CHECK text.StartsWith(Text("{")) == false;

		//startText is unmatching multiple character
		CHECK text.StartsWith(Text("//")) == false;

		//startText is matching single character
		CHECK text.StartsWith(Text("[")) == true;

		//startText is matching multiple character
		CHECK text.StartsWith(Text("[Hello]")) == true;

		return result;
	}

	Bool EndsWithTest()
	{
		Bool result = true;
		String text;

		//text is empty, return false
		CHECK text.EndsWith(_space) == false;

		//text is empty, endText is empty
		CHECK text.EndsWith(_empty) == true;

		text = Text("[Hello]");

		//text not empty, endText empty
		CHECK text.EndsWith(_empty) == true;

		//endText is unmatching single character
		CHECK text.EndsWith(Text("}")) == false;

		//endText is unmatching multiple character
		CHECK text.EndsWith(Text("*/")) == false;

		//endText is matching single character
		CHECK text.EndsWith(Text("]")) == true;

		//endText is matching multiple character
		CHECK text.EndsWith(Text("[Hello]")) == true;

		//endText is longer than start text
		CHECK text.EndsWith(Text("oh![Hello]")) == false;

		return result;
	}

	Bool IndexOfSingleTest()
	{
		Bool result = true;

		String empty;
		String len[] = {Text("0"), Text("01"), Text("012")};
		CStr of[] = {Text("0"), Text("1"), Text("2")};

		//Null string
		CHECK_ASSERT(empty.IndexOf((CStr)NULL));

		//Empty string
		CHECK empty.IndexOf(of[0]) == String::NoMatch;

		//Position too small
		CHECK len[0].IndexOf(of[0], -10) == String::NoMatch;

		//Position too big
		CHECK len[0].IndexOf(of[0], 10) == String::NoMatch;

		//Length 1 - Not Found
		CHECK len[0].IndexOf(of[1]) == String::NoMatch;

		//Length 1 - Found
		CHECK len[0].IndexOf(of[0]) == 0;

		//Length 2 - Found at beginning
		CHECK len[1].IndexOf(of[0]) == 0;

		//Length 2 - Found at end
		CHECK len[1].IndexOf(of[1]) == 1;

		//Length 2 - Not Found because of Position
		CHECK len[1].IndexOf(of[0], 1) == String::NoMatch;

		//Length 2 - Found at Position
		CHECK len[1].IndexOf(of[1], 1) == 1;

		//Length 3 - Found at beginning
		CHECK len[2].IndexOf(of[0]) == 0;

		//Length 3 - Not Found because of Position
		CHECK len[2].IndexOf(of[0], 1) == String::NoMatch;

		//Length 3 - Found at Position
		CHECK len[2].IndexOf(of[1], 1) == 1;

		//Length 3 - Found after Position
		CHECK len[2].IndexOf(of[2], 1) == 2;

		return result;
	}

	Bool IndexOfMultiTest()
	{
		Bool result = true;
		String text = _text;

		//value > text
		CHECK text.IndexOf(_textLonger) == String::NoMatch;
		CHECK text.IndexOf(text + _text) == String::NoMatch;

		//value + start > text
		CHECK text.IndexOf(_text, 5U) == String::NoMatch;

		//value == text
		CHECK text.IndexOf(_text) == 0U;
		CHECK text.IndexOf(_text, 1U) == String::NoMatch;

		//found at beginning
		CHECK text.IndexOf(Text("This is")) == 0U;
		CHECK text.IndexOf(Text("This is"), 1U) == String::NoMatch;

		//found in middle
		CHECK text.IndexOf(Text("is Core")) == 5U;
		CHECK text.IndexOf(Text("is Core"), 2U) == 5U;

		//found at end
		CHECK text.IndexOf(Text("Lib")) == 12U;
		CHECK text.IndexOf(Text("Lib"), 2U) == 12U;

		return result;
	}

	Bool LastIndexOfSingleTest()
	{
		Bool result = true;

		String empty;
		String len[] = {Text("0"), Text("01"), Text("012")};
		CStr of[] = {Text("0"), Text("1"), Text("2")};

		//Empty string
		CHECK empty.LastIndexOf(of[0]) == String::NoMatch;

		//Position too small
		CHECK len[0].LastIndexOf(of[0], -10) == String::NoMatch;

		//Position too big
		CHECK len[0].LastIndexOf(of[0], 10) == String::NoMatch;

		//Length 1 - Not Found
		CHECK len[0].LastIndexOf(of[1]) == String::NoMatch;

		//Length 1 - Found
		CHECK len[0].LastIndexOf(of[0]) == 0;

		//Length 2 - Found at beginning
		CHECK len[1].LastIndexOf(of[0]) == 0;

		//Length 2 - Found at end
		CHECK len[1].LastIndexOf(of[1]) == 1;

		//Length 2 - Not Found because of Position
		CHECK len[1].LastIndexOf(of[1], (UInt)0) == String::NoMatch;

		//Length 2 - Found at Position
		CHECK len[1].LastIndexOf(of[0], (UInt)1) == 0;

		//Length 3 - Found at end
		CHECK len[2].LastIndexOf(of[2]) == 2;

		//Length 3 - Not Found because of Position
		CHECK len[2].LastIndexOf(of[2], 1) == String::NoMatch;

		//Length 3 - Found at Position
		CHECK len[2].LastIndexOf(of[1], 2) == 1;

		//Length 3 - Found before Position
		CHECK len[2].LastIndexOf(of[0], 1) == 0;

		return result;
	}

	Bool LastIndexOfMultiTest()
	{
		Bool result = true;
		String text = _text;

		//value > text
		CHECK text.LastIndexOf(_textLonger) == String::NoMatch;
		CHECK text.LastIndexOf(text + _text) == String::NoMatch;

		//value + start > text
		CHECK text.LastIndexOf(_text, 5U) == String::NoMatch;

		//value == text
		CHECK text.LastIndexOf(_text) == 0U;
		CHECK text.LastIndexOf(_text, 1U) == String::NoMatch;

		//found at beginning
		CHECK text.LastIndexOf(Text("This is")) == 0U;
		CHECK text.LastIndexOf(Text("This is"), 1U) == String::NoMatch;

		//found in middle
		CHECK text.LastIndexOf(Text("is Core")) == 5U;
		CHECK text.LastIndexOf(Text("is Core"), _textlen - 2U) == 5U;

		//found at end
		CHECK text.LastIndexOf(Text("Lib")) == 12U;
		CHECK text.LastIndexOf(Text("Lib"), _textlen - 2U) == String::NoMatch;
		CHECK text.LastIndexOf(Text("Core"), _textlen - 2U) == 8U;

		return result;
	}

	Bool SubStringTest()
	{
		Bool result = true;
		String empty;
		String text(_text);

		//Return empty string when called on an empty string
		{
			String s = empty.SubString(0U, 5U);
			CHECK s.IsEmpty() == true;
		}

		//Length == 0 returns empty string
		{
			String s = text.SubString(0U, 0U);
			CHECK s.IsEmpty() == true;
		}

		//Return first 5 characters
		{
			String s = text.SubString(0U, 5U);
			CHECK s.Compare(Text("This ")) == 0;
		}

		//Return last 5 characters
		{
			String s = text.SubString(text.Length() - 5U, 5U);
			CHECK s.Compare(Text("reLib")) == 0;
		}

		//Return 5 characters starting at 7
		{
			String s = text.SubString(7U, 5U);
			CHECK s.Compare(Text(" Core")) == 0;
		}

		//Truncate when length is too big
		{
			String s = text.SubString(0U, 1000U);
			CHECK s.Compare(_text) == 0;
		}

		return result;
	}

	Bool SplitSingleTest(String text)
	{
		Bool result = true;
		String::StrPtrVec* vStr;

		vStr = text.Split(Text("="));

		CHECK vStr->Length() == 4;
		CHECK 0 == String::Compare(*(*vStr)[0], Text("ScrResX "));
		CHECK 0 == String::Compare(*(*vStr)[1], Text(" 1280 "));
		CHECK 0 == String::Compare(*(*vStr)[2], Text(" ScrResY "));
		CHECK 0 == String::Compare(*(*vStr)[3], Text(" 1024"));

		GALATEA_DELETE_PTR(vStr);

		return result;
	}

	Bool SplitSingleTest()
	{
		Bool result = true;

		CHECK SplitSingleTest(Text("ScrResX = 1280 = ScrResY = 1024"));
		CHECK SplitSingleTest(Text("ScrResX = 1280 = ScrResY = 1024="));
		CHECK SplitSingleTest(Text("=ScrResX = 1280 = ScrResY = 1024"));
		CHECK SplitSingleTest(Text("=ScrResX = 1280 = ScrResY = 1024="));

		CHECK SplitSingleTest(Text("ScrResX == 1280 == ScrResY == 1024"));
		CHECK SplitSingleTest(Text("ScrResX == 1280 == ScrResY == 1024=="));
		CHECK SplitSingleTest(Text("==ScrResX == 1280 == ScrResY == 1024"));
		CHECK SplitSingleTest(Text("==ScrResX == 1280 == ScrResY == 1024=="));

		CHECK SplitSingleTest(Text("ScrResX === 1280 === ScrResY === 1024"));
		CHECK SplitSingleTest(Text("ScrResX === 1280 === ScrResY === 1024==="));
		CHECK SplitSingleTest(Text("===ScrResX === 1280 === ScrResY === 1024"));
		CHECK SplitSingleTest(Text("===ScrResX === 1280 === ScrResY === 1024==="));

		return result;
	}

	Bool SplitMultiTest(String text)
	{
		Bool result = true;
		String::StrPtrVec* vStr;

		vStr = text.Split(Text("|;\t"));

		CHECK vStr->Length() == 5;
		CHECK 0 == String::Compare(*(*vStr)[0], Text("Word 1 "));
		CHECK 0 == String::Compare(*(*vStr)[1], Text(" Word 2 "));
		CHECK 0 == String::Compare(*(*vStr)[2], Text(" Word 3 "));
		CHECK 0 == String::Compare(*(*vStr)[3], Text(" Word 4 "));
		CHECK 0 == String::Compare(*(*vStr)[4], Text(" Word 5"));

		GALATEA_DELETE_PTR(vStr);

		return result;
	}

	Bool SplitMultiTest()
	{
		Bool result = true;

		CHECK SplitMultiTest(Text("Word 1 | Word 2 | Word 3 ; Word 4 \t Word 5"));
		CHECK SplitMultiTest(Text("Word 1 ;| Word 2 |\t Word 3 \t\t Word 4 ;;;;;; Word 5"));
		CHECK SplitMultiTest(Text(";Word 1 | Word 2 | Word 3 ; Word 4 \t Word 5"));
		CHECK SplitMultiTest(Text("Word 1 | Word 2 | Word 3 ; Word 4 \t Word 5|"));
		CHECK SplitMultiTest(Text("||Word 1 | Word 2 | Word 3 ; Word 4 \t Word 5"));
		CHECK SplitMultiTest(Text("Word 1 | Word 2 | Word 3 ; Word 4 \t Word 5||"));
		CHECK SplitMultiTest(Text("||Word 1 | Word 2 | Word 3 ; Word 4 \t Word 5||"));
		CHECK SplitMultiTest(Text(";|Word 1 | Word 2 | Word 3 ; Word 4 \t Word 5"));
		CHECK SplitMultiTest(Text("Word 1 | Word 2 | Word 3 ; Word 4 \t Word 5;|\t"));
		CHECK SplitMultiTest(Text(";\t\t|Word 1 | Word 2 | Word 3 ; Word 4 \t Word 5\t;;;|"));

		return result;
	}

	/******************************************************************************/
	/* Public Functions ***********************************************************/
	/******************************************************************************/

	Bool AppendCStrTest()
	{
		Bool result = true;

		//Append Null
		{
			String s;
			CHECK_ASSERT(s.Append((CStr)NULL));
		}

		//Empty += Empty
		{
			String s;
			s.Append(_empty);
			CHECK s.IsEmpty() == true;
			CHECK CheckCapLen(s, 0U, 0U);
			CHECK String::Compare(s.CStrPtr(), _empty) == 0;
		}

		//Empty += Not Empty
		{
			String s;
			s.Append(_text);
			CHECK s.IsEmpty() == false;
			CHECK CheckCapLen(s, _textcap, _textlen);
			CHECK String::Compare(s.CStrPtr(), _text) == 0;
		}

		//Not Empty += Empty
		{
			String s(_text);
			s.Append(_empty);
			CHECK s.IsEmpty() == false;
			CHECK CheckCapLen(s, _textcap, _textlen);
			CHECK String::Compare(s.CStrPtr(), _text) == 0;
		}

		//Not Empty += Not Empty
		{
			String s(_text);
			s.Append(_text);
			CHECK s.IsEmpty() == false;
			CHECK CheckCapLen(s, _textcap + _textcap - 1, _textlen + _textlen);
			CHECK String::Compare(s, String(_text) + _text) == 0;
		}

		return result;
	}

	Bool AppendStringTest()
	{
		Bool result = true;

		//Empty += Empty
		{
			String t;
			String s;
			t.Append(s);
			CHECK t.IsEmpty() == true;
			CHECK CheckCapLen(t, 0U, 0U);
			CHECK String::Compare(t.CStrPtr(), _empty) == 0;
		}

		//Empty += Not Empty
		{
			String t;
			String s(_text);
			t.Append(s);
			CHECK t.IsEmpty() == false;
			CHECK CheckCapLen(t, _textcap, _textlen);
			CHECK String::Compare(t.CStrPtr(), _text) == 0;
		}

		//Not Empty += Empty
		{
			String t(_text);
			String s;
			t.Append(s);
			CHECK t.IsEmpty() == false;
			CHECK CheckCapLen(t, _textcap, _textlen);
			CHECK String::Compare(t.CStrPtr(), _text) == 0;
		}

		//Not Empty += Not Empty
		{
			String t(_text);
			String s(_text);
			t.Append(s);
			CHECK t.IsEmpty() == false;
			CHECK CheckCapLen(t, _textcap + _textcap - 1, _textlen + _textlen);
			CHECK String::Compare(t, String(_text) + _text) == 0;
		}

		return result;
	}

	Bool AppendLineCStrTest()
	{
		Bool result = true;
		UInt nlLength = String::CStrLength(NewLine);

		//Append Null
		{
			String s;
			CHECK_ASSERT(s.AppendLine((CStr)NULL));
		}

		//Empty += Empty
		{
			String s;
			s.AppendLine(_empty);
			CHECK s.IsEmpty() == false;
			CHECK CheckCapLen(s, 1U + nlLength, nlLength);
			CHECK String::Compare(s.CStrPtr(), NewLine) == 0;
		}

		//Empty += Not Empty
		{
			String s;
			s.AppendLine(_text);
			CHECK s.IsEmpty() == false;
			CHECK CheckCapLen(s, _textcap + nlLength, _textlen + nlLength);
			CHECK String::Compare(s.CStrPtr(), String(_text) + NewLine) == 0;
		}

		//Not Empty += Empty
		{
			String s(_text);
			s.AppendLine(_empty);
			CHECK s.IsEmpty() == false;
			CHECK CheckCapLen(s, _textcap + nlLength, _textlen + nlLength);
			CHECK String::Compare(s.CStrPtr(), String(_text) + NewLine) == 0;
		}

		//Not Empty += Not Empty
		{
			String s(_text);
			s.AppendLine(_text);
			CHECK s.IsEmpty() == false;
			CHECK CheckCapLen(s, _textcap + _textcap - 1 + nlLength, _textlen + _textlen + nlLength);
			CHECK String::Compare(s, String(_text) + _text + NewLine) == 0;
		}

		return result;
	}

	Bool AppendLineStringTest()
	{
		Bool result = true;
		UInt nlLength = String::CStrLength(NewLine);

		//Empty += Empty
		{
			String t;
			String s;
			t.AppendLine(s);
			CHECK t.IsEmpty() == false;
			CHECK CheckCapLen(t, 1U + nlLength, nlLength);
			CHECK String::Compare(t.CStrPtr(), NewLine) == 0;
		}

		//Empty += Not Empty
		{
			String t;
			String s(_text);
			t.AppendLine(s);
			CHECK t.IsEmpty() == false;
			CHECK CheckCapLen(t, _textcap + nlLength, _textlen + nlLength);
			CHECK String::Compare(t.CStrPtr(), String(_text) + NewLine) == 0;
		}

		//Not Empty += Empty
		{
			String t(_text);
			String s;
			t.AppendLine(s);
			CHECK t.IsEmpty() == false;
			CHECK CheckCapLen(t, _textcap + nlLength, _textlen + nlLength);
			CHECK String::Compare(t.CStrPtr(), String(_text) + NewLine) == 0;
		}

		//Not Empty += Not Empty
		{
			String t(_text);
			String s(_text);
			t.AppendLine(s);
			CHECK t.IsEmpty() == false;
			CHECK CheckCapLen(t, _textcap + _textcap - 1 + nlLength, _textlen + _textlen + nlLength);
			CHECK String::Compare(t, String(_text) + _text + NewLine) == 0;
		}

		return result;
	}

	Bool TrimLeftTest()
	{
		Bool result = true;
		String text;

		(text = _empty).TrimLeft();
		CHECK text.Length() == 0U;
		CHECK text.Compare(_empty) == 0;

		(text = _space).TrimLeft();
		CHECK text.Length() == 0U;
		CHECK text.Compare(_empty) == 0;

		(text = Text("    ")).TrimLeft();
		CHECK text.Length() == 0U;
		CHECK text.Compare(_empty) == 0;

		(text = Text("Trim")).TrimLeft();
		CHECK text.Length() == 4U;
		CHECK text.Compare(Text("Trim")) == 0;

		(text = Text(" Trim")).TrimLeft();
		CHECK text.Length() == 4U;
		CHECK text.Compare(Text("Trim")) == 0;

		(text = Text("  Trim")).TrimLeft();
		CHECK text.Length() == 4U;
		CHECK text.Compare(Text("Trim")) == 0;

		(text = Text(" Trim ")).TrimLeft();
		CHECK text.Length() == 5U;
		CHECK text.Compare(Text("Trim ")) == 0;

		(text = Text("  Trim  ")).TrimLeft();
		CHECK text.Length() == 6U;
		CHECK text.Compare(Text("Trim  ")) == 0;

		return result;
	}

	Bool TrimRightTest()
	{
		Bool result = true;
		String text;

		(text = _empty).TrimRight();
		CHECK text.Length() == 0U;
		CHECK text.Compare(_empty) == 0;

		(text = _space).TrimRight();
		CHECK text.Length() == 0U;
		CHECK text.Compare(_empty) == 0;

		(text = Text("    ")).TrimRight();
		CHECK text.Length() == 0U;
		CHECK text.Compare(_empty) == 0;

		(text = Text("Trim")).TrimRight();
		CHECK text.Length() == 4U;
		CHECK text.Compare(Text("Trim")) == 0;

		(text = Text("Trim ")).TrimRight();
		CHECK text.Length() == 4U;
		CHECK text.Compare(Text("Trim")) == 0;

		(text = Text("Trim  ")).TrimRight();
		CHECK text.Length() == 4U;
		CHECK text.Compare(Text("Trim")) == 0;

		(text = Text(" Trim ")).TrimRight();
		CHECK text.Length() == 5U;
		CHECK text.Compare(Text(" Trim")) == 0;

		(text = Text("  Trim  ")).TrimRight();
		CHECK text.Length() == 6U;
		CHECK text.Compare(Text("  Trim")) == 0;

		return result;
	}

	Bool TrimTest()
	{
		Bool result = true;
		String text;
		CStr empty = _empty;
		CStr trim = Text("Trim");

		(text = _empty).Trim();
		CHECK text.Length() == 0U;
		CHECK text.Compare(empty) == 0;

		(text = _space).Trim();
		CHECK text.Length() == 0U;
		CHECK text.Compare(empty) == 0;

		(text = Text("    ")).Trim();
		CHECK text.Length() == 0U;
		CHECK text.Compare(empty) == 0;

		(text = Text("Trim")).Trim();
		CHECK text.Length() == 4U;
		CHECK text.Compare(trim) == 0;

		(text = Text("Trim ")).Trim();
		CHECK text.Length() == 4U;
		CHECK text.Compare(trim) == 0;

		(text = Text("Trim  ")).Trim();
		CHECK text.Length() == 4U;
		CHECK text.Compare(trim) == 0;

		(text = Text(" Trim")).Trim();
		CHECK text.Length() == 4U;
		CHECK text.Compare(trim) == 0;

		(text = Text("  Trim")).Trim();
		CHECK text.Length() == 4U;
		CHECK text.Compare(trim) == 0;

		(text = Text(" Trim ")).Trim();
		CHECK text.Length() == 4U;
		CHECK text.Compare(trim) == 0;

		(text = Text("  Trim  ")).Trim();
		CHECK text.Length() == 4U;
		CHECK text.Compare(trim) == 0;

		(text = Text("  Ha Ha Ha  ")).Trim();
		CHECK text.Length() == 8U;
		CHECK text.Compare(Text("Ha Ha Ha")) == 0;

		return result;
	}

	Bool IsDigitTCharTest()
	{
		Bool result = true;

		CHECK String::IsDigit(Text('0'));
		CHECK String::IsDigit(Text('1'));
		CHECK String::IsDigit(Text('2'));
		CHECK String::IsDigit(Text('3'));
		CHECK String::IsDigit(Text('4'));
		CHECK String::IsDigit(Text('5'));
		CHECK String::IsDigit(Text('6'));
		CHECK String::IsDigit(Text('7'));
		CHECK String::IsDigit(Text('8'));
		CHECK String::IsDigit(Text('9'));
		CHECK String::IsDigit(Text(' ')) == false;
		CHECK String::IsDigit(Text('.')) == false;
		CHECK String::IsDigit(Text('N')) == false;

		return result;
	}

	Bool IsDigitTest()
	{
		Bool result = true;

		CHECK String::IsDigit(Text("0123456789"));
		CHECK String::IsDigit(Text("0"));
		CHECK String::IsDigit(Text("29"));
		CHECK String::IsDigit(Text(" ")) == false;
		CHECK String::IsDigit(Text("haha")) == false;
		CHECK String::IsDigit(Text("a10")) == false;
		CHECK String::IsDigit(Text("10a")) == false;

		return result;
	}

	Bool ReplaceTest()
	{
		Bool result = true;
		CStr mark1 = Text("!");
		CStr mark3 = Text("!!!");

		//---------------- Concept LeftToRight ----------------
		{
			String s = Text("123 CoreLib 123-End");
			s.Replace(Text("123"), Text("AB"));
			CHECK s.Length() == 17U;
			CHECK s == Text("AB CoreLib AB-End");
		}

		//---------------- Concept RightToLeft ----------------
		{
			String s = Text("AB CoreLib AB-End");
			s.Replace(Text("AB"), Text("123"));
			CHECK s.Length() == 19U;
			CHECK s == Text("123 CoreLib 123-End");
		}

		//---------------- Generic ----------------
		{
			//String is empty, return itself
			CHECK String().Replace(_space, _space).IsEmpty();

			//param "oldValue" is null, Assert
			CHECK_ASSERT(String().Replace((CStr)NULL, _empty));

			//param "newValue" is null, Assert
			CHECK_ASSERT(String().Replace(_empty, (CStr)NULL));

			//param "oldValue" has more characters than the string, return itself
			CHECK String(_text).Replace(_textLonger, _space) == _text;

			//replace by single char, not found
			CHECK String(_text).Replace(Text("!"), _empty) == _text;

			//replace by string, not found
			CHECK String(_text).Replace(Text("DF is best"), _empty) == _text;
		}

		//---------------- single by single ----------------
		{
			//replace single by single char, found at beginning
			CHECK String(_text).Replace(Text("T"), mark1) == Text("!his is CoreLib");

			//replace single by single char, found in middle
			CHECK String(_text).Replace(Text("C"), mark1) == Text("This is !oreLib");

			//replace single by single char, found at end
			CHECK String(_text).Replace(Text("b"), mark1) == Text("This is CoreLi!");

			//replace single by single char, beginning, middle and end
			CHECK String(Text("# DF # best #")).Replace(Text("#"), mark1) == Text("! DF ! best !");
		}

		//---------------- multi by single ----------------
		{
			//replace multi by single char, found at beginning
			CHECK String(_text).Replace(Text("This"), mark1) == Text("! is CoreLib");

			//replace multi by single char, found in middle
			CHECK String(_text).Replace(Text(" is "), mark1) == Text("This!CoreLib");

			//replace multi by single char, found at end
			CHECK String(_text).Replace(Text("Lib"), mark1) == Text("This is Core!");

			//replace multi by single char, beginning, middle and end
			CHECK String(Text("### DF ### best ###")).Replace(Text("###"), mark1) == Text("! DF ! best !");
		}

		//---------------- single by multi ----------------
		{
			//replace single by multi char, found at beginning
			CHECK String(_text).Replace(Text("T"), mark3) == Text("!!!his is CoreLib");

			//replace single by multi char, found in middle
			CHECK String(_text).Replace(Text("C"), mark3) == Text("This is !!!oreLib");

			//replace single by multi char, found at end
			CHECK String(_text).Replace(Text("b"), mark3) == Text("This is CoreLi!!!");

			//replace single by multi char, beginning, middle and end
			CHECK String(Text("# DF # best #")).Replace(Text("#"), mark3) == Text("!!! DF !!! best !!!");
		}

		//---------------- multi by multi ----------------
		{
			//replace multi by multi char, found at beginning
			CHECK String(_text).Replace(Text("This"), mark3) == Text("!!! is CoreLib");

			//replace multi by multi char, found in middle
			CHECK String(_text).Replace(Text(" is "), mark3) == Text("This!!!CoreLib");

			//replace multi by multi char, found at end
			CHECK String(_text).Replace(Text("Lib"), mark3) == Text("This is Core!!!");

			//replace multi by multi char, beginning, middle and end
			CHECK String(Text("### DF ### best ###")).Replace(Text("###"), mark3) == Text("!!! DF !!! best !!!");
		}

		return result;
	}
}

Bool StringTest()
{
	using namespace StringTestNamespace;
	Bool result = true;

	CHECK CStrLengthTest();
	CHECK CStrByteSizeTest();
	CHECK FormatBufferTest();
	CHECK FormatStringTest();
	CHECK CompareTest();
	CHECK MaxLengthTest();

	CHECK CtorEmptyTest();
	CHECK CtorCapacityTest();
	CHECK CtorCStrTest();
	CHECK CtorCStrLengthTest();
	CHECK CtorRangeTest();
	CHECK CtorCopyTest();
	CHECK CtorMoveTest();

	CHECK OperatorCastToCStrTest();
	CHECK OperatorAssignCStrTest();
	CHECK OperatorAssignStringTest();
	CHECK OperatorMoveStringTest();
	CHECK OperatorPlusEqualCStrTest();
	CHECK OperatorPlusEqualStringTest();
	CHECK OperatorPlusCStrTest();
	CHECK OperatorPlusStringTest();
	CHECK OperatorEqualCStrTest();
	CHECK OperatorNotEqualCStrTest();
	CHECK OperatorGreaterCStrTest();
	CHECK OperatorSmallerCStrTest();
	CHECK OperatorGreaterOrEqualCStrTest();
	CHECK OperatorSmallerOrEqualCStrTest();
	CHECK OperatorSubscriptTest();

	CHECK IsEmptyTest();
	CHECK CapacityTest();
	CHECK LengthTest();
	CHECK CStrPtrTest();
	CHECK ClearTest();
	CHECK StartsWithLengthTest();
	CHECK StartsWithTest();
	CHECK EndsWithTest();
	CHECK IndexOfSingleTest();
	CHECK IndexOfMultiTest();
	CHECK LastIndexOfSingleTest();
	CHECK LastIndexOfMultiTest();
	CHECK SubStringTest();
	CHECK SplitSingleTest();
	CHECK SplitMultiTest();

	CHECK AppendCStrTest();
	CHECK AppendStringTest();
	CHECK AppendLineCStrTest();
	CHECK AppendLineStringTest();
	CHECK TrimLeftTest();
	CHECK TrimRightTest();
	CHECK TrimTest();
	CHECK IsDigitTCharTest();
	CHECK IsDigitTest();
	CHECK ReplaceTest();

	return result;
}
