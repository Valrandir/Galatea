#include <stdarg.h>
#include "String.hpp"
#include "../System/Assert/Assert.hpp"

void FormatImpl(Core::TChar* buffer, Core::UInt buffer_size, Core::CStr format, va_list args);
Core::UInt FormatImplGetRequiredSize(Core::CStr format, va_list args);

namespace Core
{
	UInt String::NewLineLength = String::GetCStrLength(NewLine);

	/******************************************************************************/
	/* StrPtrVec internal class ***************************************************/
	/******************************************************************************/

	String::StrPtrVec::StrPtrVec() : DataStruct::Vector<String*>(Pod)
	{
	}

	String::StrPtrVec::StrPtrVec(UInt capacity) : DataStruct::Vector<String*>(capacity, Pod)
	{
	}

	String::StrPtrVec::~StrPtrVec()
	{
		auto it = Begin();
		auto end = End();
		while(it < end)
		{
			delete *it;
			++it;
		}
	}

	/******************************************************************************/
	/* public static **************************************************************/
	/******************************************************************************/

	UInt String::GetCStrLength(CStr text)
	{
		UInt length = 0U;

		if(text)
			while(*text != '\0')
			{
				++text;
				++length;
			}

		return length;
	}

	void String::Format(TChar* buffer, UInt buffer_size, CStr format, ...)
	{
		Assert(buffer);
		Assert(buffer_size > 0);
		Assert(format);

		va_list args;
		va_start(args, format);
		FormatImpl(buffer, buffer_size, format, args);
		va_end(args);
	}

	String String::FormatToStr(CStr format, ...)
	{
		Assert(format);

		va_list args;
		UInt size;
		String str;

		va_start(args, format);
		size = FormatImplGetRequiredSize(format, args);
		va_end(args);

		str.Reserve(size);

		va_start(args, format);
		FormatImpl(str._vctr.DrivePointer(size), size, format, args);
		va_end(args);

		return str;
	}

	Int String::Compare(CStr source, CStr target)
	{
		//Return
		//	 0 when source == target
		//	 1 when source >  target
		//	-1 when source <  target

		CStr empty = Text("");

		if(source == NULL) source = empty;
		if(target == NULL) target = empty;

		while(true)
		{
			if(*source == '\0' && *target == '\0') return 0;
			if(*source == '\0') return -1;
			if(*target == '\0') return 1;
			if(*source < *target) return -1;
			if(*source > *target) return 1;
			++source;
			++target;
		}

		return 0;
	}

	UInt String::IndexOf(CStr text, UInt textLength, TChar const chr, UInt start)
	{
		CStr it, end;

		if(start >= textLength)
			return NoMatch;

		it = text + start;
		end = text + textLength;

		while(it < end)
		{
			if(*it == chr)
				return it - text;
			++it;
		}

		return NoMatch;
	}

	UInt String::IndexOf(CStr text, TChar const chr, UInt start)
	{
		return IndexOf(text, GetCStrLength(text), chr, start);
	}

	UInt String::LastIndexOf(CStr text, UInt textLength, TChar const chr, UInt start)
	{
		CStr rend, it;

		if(start >= textLength && start != NoMatch)
			return NoMatch;

		rend = text - 1;
		it = start == NoMatch ? text + textLength - 1 : text + start;

		while(rend < it)
		{
			if(*it == chr)
				return it - text;
			--it;
		}

		return NoMatch;
	}

	UInt String::LastIndexOf(CStr text, TChar const chr, UInt start)
	{
		return LastIndexOf(text, GetCStrLength(text), chr, start);
	}

	String String::SubString(CStr text, UInt textLength, UInt start, UInt length)
	{
		if(length > textLength) length = textLength;
		if(!text || !length || start + length > textLength) return String();
		return String(text + start, text + start + length);
	}

	String String::SubString(CStr text, UInt start, UInt length)
	{
		UInt textLength =  GetCStrLength(text);
		if(length > textLength) length = textLength;
		if(!text || !length || start + length > textLength) return String();
		return String(text + start, text + start + length);
	}

	String::StrPtrVec* String::Split(CStr text, UInt charCount, CStr delimiters)
	{
		StrPtrVec* vStr;
		UInt delimitersLength;
		CStr begin, it, end;
		UInt count;

		vStr = new StrPtrVec();

		if(!text || !charCount)
			return vStr;

		if(!delimiters || !(delimitersLength = GetCStrLength(delimiters)))
		{
			vStr->Add(new String(text));
			return vStr;
		}

		begin = text;
		it = text;
		end = text + charCount;
		count = 0U;

		while(it < end)
		{
			if(delimitersLength == 1 ? *it == *delimiters : IndexOf(delimiters, delimitersLength, *it) != NoMatch)
			{
				if(begin != it)
				{
					vStr->Add(new String(begin, it));
					begin = it + 1;
					++count;
				}
				else
					++begin;
			}
			++it;
		}

		if(begin != end)
		{
			vStr->Add(new String(begin, end));
			++count;
		}

		return vStr;
	}

	/******************************************************************************/
	/* Constructors && Destructor *************************************************/
	/******************************************************************************/

	String::String() : _vctr(Vector::CtorModeEnum::Pod)
	{
	}

	String::String(UInt capacity) : _vctr(capacity, Vector::CtorModeEnum::Pod)
	{
	}

	String::String(CStr text) : _vctr(Vector::CtorModeEnum::Pod)
	{
		UInt n = GetCStrLength(text);
		if(n) _vctr.AddRange(text, text + n + 1);
	}

	String::String(CStr begin, CStr end) : _vctr(Vector::CtorModeEnum::Pod)
	{
		_vctr.Reserve(end - begin + 1);
		_vctr.AddRange(begin, end);
		_vctr.Add(Text('\0'));
	}

	String::String(String const & text) : _vctr(text._vctr)
	{
	}

	String::String(String && text) : _vctr((Vector&&)text)
	{
	}

	String::~String()
	{
	}

	/******************************************************************************/
	/* Operators ******************************************************************/
	/******************************************************************************/

	String::operator CStr () const
	{
		return GetCStr();
	}

	String& String::operator=(CStr text)
	{
		UInt n = GetCStrLength(text);
		_vctr.Clear();
		if(n) _vctr.AddRange(text, text + n + 1);
		return *this;
	}

	String& String::operator=(String const & text)
	{
		if(this != &text)
		{
			if(text.IsEmpty())
				_vctr.Clear();
			else
				*this = text.GetCStr();
		}
	
		return *this;
	}

	String& String::operator=(String && text)
	{
		_vctr.operator=((Vector&&)text);
		return *this;
	}

	String& String::operator+=(CStr text)
	{
		Assert(text);
		UInt length = GetCStrLength(text);
		UInt current_length, new_length;
		Bool MaxSizeOverflow;

		if(length)
		{
			//Check for MaxSize overflow
			current_length = _vctr.GetLength();
			new_length = current_length + length;
			MaxSizeOverflow = !(new_length >= MaxSize || new_length < current_length);
			Assert(MaxSizeOverflow);

			_vctr.Remove(current_length - 1);
			_vctr.AddRange(text, text + length + 1);
		}
		return *this;
	}

	String& String::operator+=(String const & text)
	{
		if(!text.IsEmpty())
		{
			_vctr.Remove(_vctr.GetLength() - 1);
			_vctr.operator+=(text._vctr);
		}
		return *this;
	}

	String String::operator+(CStr text) const
	{
		Assert(text);
		return String(*this) += text;
	}

	String String::operator+(String const & text) const
	{
		return String(*this) += text;
	}

	Bool String::operator==(TChar  const * text) const { return Compare(text) ==  0; }
	Bool String::operator!=(TChar  const * text) const { return Compare(text) !=  0; }
	Bool String::operator> (TChar  const * text) const { return Compare(text) ==  1; }
	Bool String::operator< (TChar  const * text) const { return Compare(text) == -1; }
	Bool String::operator>=(TChar  const * text) const { return Compare(text) >=  0; }
	Bool String::operator<=(TChar  const * text) const { return Compare(text) <=  0; }

	TChar String::operator[](UInt index) const
	{
		return _vctr.operator[](index);
	}

	/******************************************************************************/
	/* Public Const Functions *****************************************************/
	/******************************************************************************/

	Bool String::IsEmpty() const
	{
		return _vctr.IsEmpty();
	}

	UInt String::GetCapacity() const
	{
		return _vctr.GetCapacity();
	}

	UInt String::GetLength() const
	{
		return _vctr.IsEmpty() ? 0U : _vctr.GetLength() - 1;
	}

	CStr String::GetCStr() const
	{
		return _vctr.Begin();
	}

	Int String::Compare(CStr target) const
	{
		return Compare(GetCStr(), target);
	}

	UInt String::IndexOf(TChar const chr, UInt start) const
	{
		return IndexOf(GetCStr(), chr, start);
	}

	UInt String::LastIndexOf(TChar const chr, UInt start) const
	{
		return LastIndexOf(GetCStr(), chr, start);
	}

	String String::SubString(UInt start, UInt length) const
	{
		return SubString(GetCStr(), GetLength(), start, length);
	}

	String::StrPtrVec* String::Split(CStr delimiters) const
	{
		return Split(GetCStr(), GetLength(), delimiters);
	}

	/******************************************************************************/
	/* Public Functions ***********************************************************/
	/******************************************************************************/

	void String::Reserve(UInt capacity)
	{
		_vctr.Reserve(capacity + NewLineLength);
	}

	void String::Shrink()
	{
		_vctr.Shrink();
	}

	void String::Append(CStr str)
	{
		Assert(str);
		*this += str;
	}

	void String::Append(String const & str)
	{
		*this += str;
	}

	void String::AppendLine(CStr str)
	{
		Assert(str);
		*this += str;
		*this += NewLine;
	}

	void String::AppendLine(String const & str)
	{
		*this += str;
		*this += NewLine;
	}

	TChar* String::DrivePointer(UInt future_length)
	{
		return _vctr.DrivePointer(future_length + 1);
	}
}
