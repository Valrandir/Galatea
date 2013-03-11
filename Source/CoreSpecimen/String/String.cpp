#include "../Core.hpp"

using namespace Core;

namespace StringTestNamespace
{
	CStr _empty = Text("");
	CStr _text = Text("This is CoreLib");
	CStr _textSmaller = Text("A is smaller than T");
	CStr _textGreater = Text("V is Greater than T");
	CStr _textShorter = Text("Shorter");
	CStr _textBigger = Text("Very much larger than _text");
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

	Bool CStrPtrLenTest()
	{
		Bool result = true;

		//Null
		CHECK String::CStrLength(NULL) == 0U;

		//Empty string Len == 1 for terminating character
		CHECK String::CStrLength(_empty) == 0U;

		//Len == _textlen
		CHECK String::CStrLength(_text) == _textlen;

		return result;
	}

	Bool FormatBufferTest()
	{
		Bool result = true;

		CStr format = Text("One hundred fifty seven : %d - %s");

		//Buffer is large enough
		{
			UInt const buffer_size = 128U;
			TChar buffer[buffer_size];

			String::Format(buffer, buffer_size, format, 157, Text("Done"));

			CHECK 0 == String::Compare(Text("One hundred fifty seven : 157 - Done"), buffer);
		}

		//Buffer is too short, so the output was truncated
		{
			UInt const buffer_size = 24U;
			TChar buffer[buffer_size];

			String::Format(buffer, buffer_size, format, 157, Text("Done"));

			CHECK 0 == String::Compare(Text("One hundred fifty seven"), buffer);
		}

		return result;
	}

	Bool FormatStringTest()
	{
		Bool result = true;

		CStr format = Text("One hundred fifty seven : %d - %s");

		String str = String::FormatToStr(format, 157, Text("Done"));

		CHECK str.Capacity() == 37U + String::CStrLength(NewLine);
		CHECK str.Length() == 36U;
		CHECK 0 == String::Compare(Text("One hundred fifty seven : 157 - Done"), str.CStrPtr());

		return result;
	}

	Bool CompareTCharTest()
	{
		Bool result = true;

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
		}

		//Capacity
		{
			String s(10U);
			CHECK s.IsEmpty() == true;
			CHECK CheckCapLen(s, 10U, 0U);
		}

		return result;
	}

	Bool CtorTCharTest()
	{
		Bool result = true;
		CStr nullTChar = NULL;

		//TChar NULL
		{
			String s(nullTChar);
			CHECK s.IsEmpty() == true;
			CHECK CheckCapLen(s, 0U, 0U);
		}

		//TChar Empty
		{
			String s(_empty);
			CHECK s.IsEmpty() == true;
			CHECK CheckCapLen(s, 0U, 0U);
		}

		//TChar not Empty
		{
			String s(_text);
			CHECK s.IsEmpty() == false;
			CHECK CheckCapLen(s, _textcap, _textlen);
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

	Bool OperatorAssignTCharTest()
	{
		Bool result = true;
		UInt capacity;

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
			t = _textBigger;
			capacity = String::CStrLength(_textBigger);
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
			String s(_textBigger);
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

	Bool OperatorPlusEqualTCharTest()
	{
		Bool result = true;

		//Empty += Empty
		{
			String s;
			s += _empty;
			CHECK s.IsEmpty() == true;
			CHECK CheckCapLen(s, 0U, 0U);
			CHECK String::Compare(s.CStrPtr(), _empty) == 0;
		}

		//Empty += Not Empty
		{
			String s;
			s += _text;
			CHECK s.IsEmpty() == false;
			CHECK CheckCapLen(s, _textcap, _textlen);
			CHECK String::Compare(s.CStrPtr(), _text) == 0;
		}

		//Not Empty += Empty
		{
			String s(_text);
			s += _empty;
			CHECK s.IsEmpty() == false;
			CHECK CheckCapLen(s, _textcap, _textlen);
			CHECK String::Compare(s.CStrPtr(), _text) == 0;
		}

		//Not Empty += Not Empty
		{
			String s(_text);
			s += _text;
			CHECK s.IsEmpty() == false;
			CHECK CheckCapLen(s, _textcap + _textcap - 1, _textlen + _textlen);
			CHECK String::Compare(s, String(_text) + _text) == 0;
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
			CHECK String::Compare(t.CStrPtr(), _empty) == 0;
		}

		//Empty += Not Empty
		{
			String t;
			String s(_text);
			t += s;
			CHECK t.IsEmpty() == false;
			CHECK CheckCapLen(t, _textcap, _textlen);
			CHECK String::Compare(t.CStrPtr(), _text) == 0;
		}

		//Not Empty += Empty
		{
			String t(_text);
			String s;
			t += s;
			CHECK t.IsEmpty() == false;
			CHECK CheckCapLen(t, _textcap, _textlen);
			CHECK String::Compare(t.CStrPtr(), _text) == 0;
		}

		//Not Empty += Not Empty
		{
			String t(_text);
			String s(_text);
			t += s;
			CHECK t.IsEmpty() == false;
			CHECK CheckCapLen(t, _textcap + _textcap - 1, _textlen + _textlen);
			CHECK String::Compare(t, String(_text) + _text) == 0;
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

	Bool OperatorEqualTCharTest()
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

	Bool OperatorNotEqualTCharTest()
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

	Bool OperatorGreaterTCharTest()
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

	Bool OperatorSmallerTCharTest()
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

	Bool OperatorGreaterOrEqualTCharTest()
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

	Bool OperatorSmallerOrEqualTCharTest()
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

		String s(_text);
		CHECK s[0U] == Text('T');
		CHECK s[10U] == Text('r');

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

		String s(_text);
		CStr tc = s.CStrPtr();
		CHECK String::Compare(_text, tc) == 0U;

		return result;
	}

	Bool IndexOfTest()
	{
		Bool result = true;

		String empty;
		String len[] = {Text("0"), Text("01"), Text("012")};
		TChar chr[] = {Text('0'), Text('1'), Text('2')};

		//Empty string
		CHECK empty.IndexOf(chr[0]) == String::NoMatch;

		//Position too small
		CHECK len[0].IndexOf(chr[0], -10) == String::NoMatch;

		//Position too big
		CHECK len[0].IndexOf(chr[0], 10) == String::NoMatch;

		//Length 1 - Not Found
		CHECK len[0].IndexOf(chr[1]) == String::NoMatch;

		//Length 1 - Found
		CHECK len[0].IndexOf(chr[0]) == 0;

		//Length 2 - Found at beginning
		CHECK len[1].IndexOf(chr[0]) == 0;

		//Length 2 - Found at end
		CHECK len[1].IndexOf(chr[1]) == 1;

		//Length 2 - Not Found because of Position
		CHECK len[1].IndexOf(chr[0], 1) == String::NoMatch;

		//Length 2 - Found at Position
		CHECK len[1].IndexOf(chr[1], 1) == 1;

		//Length 3 - Found at beginning
		CHECK len[2].IndexOf(chr[0]) == 0;

		//Length 3 - Not Found because of Position
		CHECK len[2].IndexOf(chr[0], 1) == String::NoMatch;

		//Length 3 - Found at Position
		CHECK len[2].IndexOf(chr[1], 1) == 1;

		//Length 3 - Found after Position
		CHECK len[2].IndexOf(chr[2], 1) == 2;

		return result;
	}

	Bool LastIndexOfTest()
	{
		Bool result = true;

		String empty;
		String len[] = {Text("0"), Text("01"), Text("012")};
		TChar chr[] = {Text('0'), Text('1'), Text('2')};

		//Empty string
		CHECK empty.LastIndexOf(chr[0]) == String::NoMatch;

		//Position too small
		CHECK len[0].LastIndexOf(chr[0], -10) == String::NoMatch;

		//Position too big
		CHECK len[0].LastIndexOf(chr[0], 10) == String::NoMatch;

		//Length 1 - Not Found
		CHECK len[0].LastIndexOf(chr[1]) == String::NoMatch;

		//Length 1 - Found
		CHECK len[0].LastIndexOf(chr[0]) == 0;

		//Length 2 - Found at beginning
		CHECK len[1].LastIndexOf(chr[0]) == 0;

		//Length 2 - Found at end
		CHECK len[1].LastIndexOf(chr[1]) == 1;

		//Length 2 - Not Found because of Position
		CHECK len[1].LastIndexOf(chr[1], 0) == String::NoMatch;

		//Length 2 - Found at Position
		CHECK len[1].LastIndexOf(chr[0], 0) == 0;

		//Length 3 - Found at end
		CHECK len[2].LastIndexOf(chr[2]) == 2;

		//Length 3 - Not Found because of Position
		CHECK len[2].LastIndexOf(chr[2], 1) == String::NoMatch;

		//Length 3 - Found at Position
		CHECK len[2].LastIndexOf(chr[1], 1) == 1;

		//Length 3 - Found before Position
		CHECK len[2].LastIndexOf(chr[0], 1) == 0;

		return result;
	}

	Bool StartsWithTest()
	{
		Bool result = true;
		String text;

		//text is empty, return false
		CHECK text.StartsWith(Text(" ")) == false;

		//text is empty, startText is empty, return true
		CHECK text.StartsWith(Text("")) == true;

		text = Text("[Hello]");

		//text not empty, startText empty, return false
		CHECK text.StartsWith(Text("")) == false;

		//startText is unmatching single character, return false
		CHECK text.StartsWith(Text("{")) == false;

		//startText is unmatching multiple character, return false
		CHECK text.StartsWith(Text("//")) == false;

		//startText is matching single character, return true
		CHECK text.StartsWith(Text("[")) == true;

		//startText is matching multiple character, return true
		CHECK text.StartsWith(Text("[Hello]")) == true;

		return result;
	}

	Bool EndsWithTest()
	{
		Bool result = true;
		String text;

		//text is empty, return false
		CHECK text.EndsWith(Text(" ")) == false;

		//text is empty, endText is empty, return true
		CHECK text.EndsWith(Text("")) == true;

		text = Text("[Hello]");

		//text not empty, endText empty, return false
		CHECK text.EndsWith(Text("")) == false;

		//endText is unmatching single character, return false
		CHECK text.EndsWith(Text("}")) == false;

		//endText is unmatching multiple character, return false
		CHECK text.EndsWith(Text("*/")) == false;

		//endText is matching single character, return true
		CHECK text.EndsWith(Text("]")) == true;

		//endText is matching multiple character, return true
		CHECK text.EndsWith(Text("[Hello]")) == true;

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

	Bool SplitTCharTest(String text)
	{
		Bool result = true;
		String::StrPtrVec* vStr;

		vStr = text.Split(Text("="));

		CHECK vStr->Length() == 4;
		CHECK 0 == String::Compare(*(*vStr)[0], Text("ScrResX "));
		CHECK 0 == String::Compare(*(*vStr)[1], Text(" 1280 "));
		CHECK 0 == String::Compare(*(*vStr)[2], Text(" ScrResY "));
		CHECK 0 == String::Compare(*(*vStr)[3], Text(" 1024"));

		DeletePtr(vStr);

		return result;
	}

	Bool SplitTCharTest()
	{
		Bool result = true;

		CHECK SplitTCharTest(Text("ScrResX = 1280 = ScrResY = 1024"));
		CHECK SplitTCharTest(Text("ScrResX = 1280 = ScrResY = 1024="));
		CHECK SplitTCharTest(Text("=ScrResX = 1280 = ScrResY = 1024"));
		CHECK SplitTCharTest(Text("=ScrResX = 1280 = ScrResY = 1024="));

		CHECK SplitTCharTest(Text("ScrResX == 1280 == ScrResY == 1024"));
		CHECK SplitTCharTest(Text("ScrResX == 1280 == ScrResY == 1024=="));
		CHECK SplitTCharTest(Text("==ScrResX == 1280 == ScrResY == 1024"));
		CHECK SplitTCharTest(Text("==ScrResX == 1280 == ScrResY == 1024=="));

		CHECK SplitTCharTest(Text("ScrResX === 1280 === ScrResY === 1024"));
		CHECK SplitTCharTest(Text("ScrResX === 1280 === ScrResY === 1024==="));
		CHECK SplitTCharTest(Text("===ScrResX === 1280 === ScrResY === 1024"));
		CHECK SplitTCharTest(Text("===ScrResX === 1280 === ScrResY === 1024==="));

		return result;
	}

	Bool SplitCStrTest(String text)
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

		DeletePtr(vStr);

		return result;
	}

	Bool SplitCStrTest()
	{
		Bool result = true;

		CHECK SplitCStrTest(Text("Word 1 | Word 2 | Word 3 ; Word 4 \t Word 5"));
		CHECK SplitCStrTest(Text("Word 1 ;| Word 2 |\t Word 3 \t\t Word 4 ;;;;;; Word 5"));
		CHECK SplitCStrTest(Text(";Word 1 | Word 2 | Word 3 ; Word 4 \t Word 5"));
		CHECK SplitCStrTest(Text("Word 1 | Word 2 | Word 3 ; Word 4 \t Word 5|"));
		CHECK SplitCStrTest(Text("||Word 1 | Word 2 | Word 3 ; Word 4 \t Word 5"));
		CHECK SplitCStrTest(Text("Word 1 | Word 2 | Word 3 ; Word 4 \t Word 5||"));
		CHECK SplitCStrTest(Text("||Word 1 | Word 2 | Word 3 ; Word 4 \t Word 5||"));
		CHECK SplitCStrTest(Text(";|Word 1 | Word 2 | Word 3 ; Word 4 \t Word 5"));
		CHECK SplitCStrTest(Text("Word 1 | Word 2 | Word 3 ; Word 4 \t Word 5;|\t"));
		CHECK SplitCStrTest(Text(";\t\t|Word 1 | Word 2 | Word 3 ; Word 4 \t Word 5\t;;;|"));

		return result;
	}

	/******************************************************************************/
	/* Public Functions ***********************************************************/
	/******************************************************************************/

	Bool AppendTCharTest()
	{
		Bool result = true;

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

	Bool AppendLineTCharTest()
	{
		Bool result = true;
		UInt nlLength = String::CStrLength(NewLine);
		
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

		(text = Text("")).TrimLeft();
		CHECK text.Length() == 0U;
		CHECK text.Compare(Text("")) == 0;

		(text = Text(" ")).TrimLeft();
		CHECK text.Length() == 0U;
		CHECK text.Compare(Text("")) == 0;

		(text = Text("    ")).TrimLeft();
		CHECK text.Length() == 0U;
		CHECK text.Compare(Text("")) == 0;

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

		(text = Text("")).TrimRight();
		CHECK text.Length() == 0U;
		CHECK text.Compare(Text("")) == 0;

		(text = Text(" ")).TrimRight();
		CHECK text.Length() == 0U;
		CHECK text.Compare(Text("")) == 0;

		(text = Text("    ")).TrimRight();
		CHECK text.Length() == 0U;
		CHECK text.Compare(Text("")) == 0;

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
		CStr empty = Text("");
		CStr trim = Text("Trim");

		(text = Text("")).Trim();
		CHECK text.Length() == 0U;
		CHECK text.Compare(empty) == 0;

		(text = Text(" ")).Trim();
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
}

Bool StringTest()
{
	using namespace StringTestNamespace;
	Bool result = true;

	CHECK CStrPtrLenTest();
	CHECK FormatBufferTest();
	CHECK FormatStringTest();
	CHECK CompareTCharTest();
	CHECK MaxLengthTest();

	CHECK CtorEmptyTest();
	CHECK CtorCapacityTest();
	CHECK CtorTCharTest();
	CHECK CtorCopyTest();
	CHECK CtorMoveTest();

	CHECK OperatorAssignTCharTest();
	CHECK OperatorAssignStringTest();
	CHECK OperatorMoveStringTest();
	CHECK OperatorPlusEqualTCharTest();
	CHECK OperatorPlusEqualStringTest();
	CHECK OperatorPlusTCharTest();
	CHECK OperatorPlusStringTest();
	CHECK OperatorEqualTCharTest();
	CHECK OperatorNotEqualTCharTest();
	CHECK OperatorGreaterTCharTest();
	CHECK OperatorSmallerTCharTest();
	CHECK OperatorGreaterOrEqualTCharTest();
	CHECK OperatorSmallerOrEqualTCharTest();
	CHECK OperatorSubscriptTest();

	CHECK IsEmptyTest();
	CHECK CapacityTest();
	CHECK LengthTest();
	CHECK CStrPtrTest();
	CHECK IndexOfTest();
	CHECK LastIndexOfTest();
	CHECK StartsWithTest();
	CHECK EndsWithTest();
	CHECK SubStringTest();
	CHECK SplitTCharTest();
	CHECK SplitCStrTest();
	CHECK TrimLeftTest();
	CHECK TrimRightTest();
	CHECK TrimTest();

	CHECK AppendTCharTest();
	CHECK AppendStringTest();
	CHECK AppendLineTCharTest();
	CHECK AppendLineStringTest();

	return result;
}
