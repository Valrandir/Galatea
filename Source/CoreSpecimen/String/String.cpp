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
		return s.GetCapacity() == capacity && s.GetLength() == length;
	}

	/******************************************************************************/
	/* public static **************************************************************/
	/******************************************************************************/

	Bool GetTCharLenTest()
	{
		Bool result = true;

		//Null
		CHECK String::GetTCharLength(NULL) == 0U;

		//Empty string Len == 1 for terminating character
		CHECK String::GetTCharLength(_empty) == 0U;

		//Len == _textlen
		CHECK String::GetTCharLength(_text) == _textlen;

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

		CHECK str.GetCapacity() == 37U + String::GetTCharLength(NewLine);
		CHECK str.GetLength() == 36U;
		CHECK 0 == String::Compare(Text("One hundred fifty seven : 157 - Done"), str.GetTChar());

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
			capacity = t.GetCapacity();
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
			capacity = String::GetTCharLength(_textBigger);
			CHECK t.IsEmpty() == false;
			CHECK CheckCapLen(t, capacity + 1, capacity);
		}

		//Assign shorter string to bigger string
		//Target capacity is same as before
		{
			String t(_text);
			capacity = t.GetCapacity();
			t = _textShorter;
			CHECK t.IsEmpty() == false;
			CHECK CheckCapLen(t, capacity, String::GetTCharLength(_textShorter));
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
			capacity = t.GetCapacity();
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
			CHECK CheckCapLen(t, s.GetCapacity(), s.GetLength());
		}

		//Assign shorter string to bigger string
		//Target capacity is same as before
		{
			String s(_textShorter);
			String t(_text);
			capacity = t.GetCapacity();
			t = s;
			CHECK t.IsEmpty() == false;
			CHECK CheckCapLen(t, capacity, s.GetLength());
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
			CHECK String::Compare(s.GetTChar(), _empty) == 0;
		}

		//Empty += Not Empty
		{
			String s;
			s += _text;
			CHECK s.IsEmpty() == false;
			CHECK CheckCapLen(s, _textcap, _textlen);
			CHECK String::Compare(s.GetTChar(), _text) == 0;
		}

		//Not Empty += Empty
		{
			String s(_text);
			s += _empty;
			CHECK s.IsEmpty() == false;
			CHECK CheckCapLen(s, _textcap, _textlen);
			CHECK String::Compare(s.GetTChar(), _text) == 0;
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
			CHECK String::Compare(t.GetTChar(), _empty) == 0;
		}

		//Empty += Not Empty
		{
			String t;
			String s(_text);
			t += s;
			CHECK t.IsEmpty() == false;
			CHECK CheckCapLen(t, _textcap, _textlen);
			CHECK String::Compare(t.GetTChar(), _text) == 0;
		}

		//Not Empty += Empty
		{
			String t(_text);
			String s;
			t += s;
			CHECK t.IsEmpty() == false;
			CHECK CheckCapLen(t, _textcap, _textlen);
			CHECK String::Compare(t.GetTChar(), _text) == 0;
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

	Bool GetCapacityTest()
	{
		Bool result = true;

		//Empty
		{
			String s;
			CHECK s.GetCapacity() == 0U;
		}

		//Capacity
		{
			String s(10U);
			CHECK s.GetCapacity() == 10U;
		}

		return result;
	}

	Bool GetLengthTest()
	{
		Bool result = true;

		//Empty
		{
			String s;
			CHECK s.GetLength() == 0U;
		}

		//Empty with Capacity
		{
			String s(10U);
			CHECK s.GetLength() == 0U;
		}

		//Not Empty
		{
			String s(_text);
			CHECK s.GetLength() == _textlen;
		}

		return result;
	}

	Bool GetTCharTest()
	{
		Bool result = true;

		String s(_text);
		CStr tc = s.GetTChar();
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
			String s = text.SubString(text.GetLength() - 5U, 5U);
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

	Bool SplitTest(String text)
	{
		Bool result = true;
		String::StringPtrVector* vStr;

		vStr = text.Split(Text('='));

		CHECK vStr->GetLength() == 4;
		CHECK 0 == String::Compare(*(*vStr)[0], Text("ScrResX "));
		CHECK 0 == String::Compare(*(*vStr)[1], Text(" 1280 "));
		CHECK 0 == String::Compare(*(*vStr)[2], Text(" ScrResY "));
		CHECK 0 == String::Compare(*(*vStr)[3], Text(" 1024"));

		for(auto it = vStr->Begin(); it < vStr->End(); ++it) delete (*it);
		DeletePtr(vStr);

		return result;
	}

	Bool SplitTest()
	{
		Bool result = true;

		CHECK SplitTest(Text("ScrResX = 1280 = ScrResY = 1024"));
		CHECK SplitTest(Text("ScrResX = 1280 = ScrResY = 1024="));
		CHECK SplitTest(Text("=ScrResX = 1280 = ScrResY = 1024"));
		CHECK SplitTest(Text("=ScrResX = 1280 = ScrResY = 1024="));

		CHECK SplitTest(Text("ScrResX == 1280 == ScrResY == 1024"));
		CHECK SplitTest(Text("ScrResX == 1280 == ScrResY == 1024=="));
		CHECK SplitTest(Text("==ScrResX == 1280 == ScrResY == 1024"));
		CHECK SplitTest(Text("==ScrResX == 1280 == ScrResY == 1024=="));

		CHECK SplitTest(Text("ScrResX === 1280 === ScrResY === 1024"));
		CHECK SplitTest(Text("ScrResX === 1280 === ScrResY === 1024==="));
		CHECK SplitTest(Text("===ScrResX === 1280 === ScrResY === 1024"));
		CHECK SplitTest(Text("===ScrResX === 1280 === ScrResY === 1024==="));

		return result;
	}

	Bool SplitAnyTest(String text)
	{
		Bool result = true;
		String::StringPtrVector* vStr;

		vStr = text.SplitAny(Text("|;\t"));

		CHECK vStr->GetLength() == 5;
		CHECK 0 == String::Compare(*(*vStr)[0], Text("Word 1 "));
		CHECK 0 == String::Compare(*(*vStr)[1], Text(" Word 2 "));
		CHECK 0 == String::Compare(*(*vStr)[2], Text(" Word 3 "));
		CHECK 0 == String::Compare(*(*vStr)[3], Text(" Word 4 "));
		CHECK 0 == String::Compare(*(*vStr)[4], Text(" Word 5"));

		for(auto it = vStr->Begin(); it < vStr->End(); ++it) delete (*it);
		DeletePtr(vStr);

		return result;
	}

	Bool SplitAnyTest()
	{
		Bool result = true;

		CHECK SplitAnyTest(Text("Word 1 | Word 2 | Word 3 ; Word 4 \t Word 5"));
		CHECK SplitAnyTest(Text("Word 1 ;| Word 2 |\t Word 3 \t\t Word 4 ;;;;;; Word 5"));
		CHECK SplitAnyTest(Text(";Word 1 | Word 2 | Word 3 ; Word 4 \t Word 5"));
		CHECK SplitAnyTest(Text("Word 1 | Word 2 | Word 3 ; Word 4 \t Word 5|"));
		CHECK SplitAnyTest(Text("||Word 1 | Word 2 | Word 3 ; Word 4 \t Word 5"));
		CHECK SplitAnyTest(Text("Word 1 | Word 2 | Word 3 ; Word 4 \t Word 5||"));
		CHECK SplitAnyTest(Text("||Word 1 | Word 2 | Word 3 ; Word 4 \t Word 5||"));
		CHECK SplitAnyTest(Text(";|Word 1 | Word 2 | Word 3 ; Word 4 \t Word 5"));
		CHECK SplitAnyTest(Text("Word 1 | Word 2 | Word 3 ; Word 4 \t Word 5;|\t"));
		CHECK SplitAnyTest(Text(";\t\t|Word 1 | Word 2 | Word 3 ; Word 4 \t Word 5\t;;;|"));

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
			CHECK String::Compare(s.GetTChar(), _empty) == 0;
		}

		//Empty += Not Empty
		{
			String s;
			s.Append(_text);
			CHECK s.IsEmpty() == false;
			CHECK CheckCapLen(s, _textcap, _textlen);
			CHECK String::Compare(s.GetTChar(), _text) == 0;
		}

		//Not Empty += Empty
		{
			String s(_text);
			s.Append(_empty);
			CHECK s.IsEmpty() == false;
			CHECK CheckCapLen(s, _textcap, _textlen);
			CHECK String::Compare(s.GetTChar(), _text) == 0;
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
			CHECK String::Compare(t.GetTChar(), _empty) == 0;
		}

		//Empty += Not Empty
		{
			String t;
			String s(_text);
			t.Append(s);
			CHECK t.IsEmpty() == false;
			CHECK CheckCapLen(t, _textcap, _textlen);
			CHECK String::Compare(t.GetTChar(), _text) == 0;
		}

		//Not Empty += Empty
		{
			String t(_text);
			String s;
			t.Append(s);
			CHECK t.IsEmpty() == false;
			CHECK CheckCapLen(t, _textcap, _textlen);
			CHECK String::Compare(t.GetTChar(), _text) == 0;
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
		UInt nlLength = String::GetTCharLength(NewLine);
		
		//Empty += Empty
		{
			String s;
			s.AppendLine(_empty);
			CHECK s.IsEmpty() == false;
			CHECK CheckCapLen(s, 1U + nlLength, nlLength);
			CHECK String::Compare(s.GetTChar(), NewLine) == 0;
		}

		//Empty += Not Empty
		{
			String s;
			s.AppendLine(_text);
			CHECK s.IsEmpty() == false;
			CHECK CheckCapLen(s, _textcap + nlLength, _textlen + nlLength);
			CHECK String::Compare(s.GetTChar(), String(_text) + NewLine) == 0;
		}

		//Not Empty += Empty
		{
			String s(_text);
			s.AppendLine(_empty);
			CHECK s.IsEmpty() == false;
			CHECK CheckCapLen(s, _textcap + nlLength, _textlen + nlLength);
			CHECK String::Compare(s.GetTChar(), String(_text) + NewLine) == 0;
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
		UInt nlLength = String::GetTCharLength(NewLine);

		//Empty += Empty
		{
			String t;
			String s;
			t.AppendLine(s);
			CHECK t.IsEmpty() == false;
			CHECK CheckCapLen(t, 1U + nlLength, nlLength);
			CHECK String::Compare(t.GetTChar(), NewLine) == 0;
		}

		//Empty += Not Empty
		{
			String t;
			String s(_text);
			t.AppendLine(s);
			CHECK t.IsEmpty() == false;
			CHECK CheckCapLen(t, _textcap + nlLength, _textlen + nlLength);
			CHECK String::Compare(t.GetTChar(), String(_text) + NewLine) == 0;
		}

		//Not Empty += Empty
		{
			String t(_text);
			String s;
			t.AppendLine(s);
			CHECK t.IsEmpty() == false;
			CHECK CheckCapLen(t, _textcap + nlLength, _textlen + nlLength);
			CHECK String::Compare(t.GetTChar(), String(_text) + NewLine) == 0;
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
}

Bool StringTest()
{
	using namespace StringTestNamespace;
	Bool result = true;

	CHECK GetTCharLenTest();
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
	CHECK GetCapacityTest();
	CHECK GetLengthTest();
	CHECK GetTCharTest();
	CHECK IndexOfTest();
	CHECK LastIndexOfTest();
	CHECK SubStringTest();
	CHECK SplitTest();
	CHECK SplitAnyTest();

	CHECK AppendTCharTest();
	CHECK AppendStringTest();
	CHECK AppendLineTCharTest();
	CHECK AppendLineStringTest();

	return result;
}
