#include <stdarg.h>
#include "String.hpp"
#include "../Assert/Assert.hpp"

void FormatImpl(Core::TChar* buffer, Core::UInt buffer_size, Core::CStr format, va_list args);
Core::UInt FormatImplGetRequiredSize(Core::CStr format, va_list args);

namespace Core
{
	UInt String::NewLineLength = String::CStrLength(NewLine);

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

	UInt String::CStrLength(CStr text)
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

	UInt String::CStrByteSize(CStr text)
	{
		return CStrLength(text) * sizeof(TChar);
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
		return IndexOf(text, CStrLength(text), chr, start);
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
		return LastIndexOf(text, CStrLength(text), chr, start);
	}

	Bool String::StartsWith(CStr text, CStr startText)
	{
		auto src = text;
		auto trg = startText;

		if(!src || !trg)
			return false;

		while(*src && *trg && *src == *trg)
		{
			++src;
			++trg;
		}

		return !*trg;
	}

	Bool String::EndsWith(CStr text, UInt textLength, CStr endText)
	{
		return text ? StartsWith(text + textLength - CStrLength(endText), endText) : false;
	}

	Bool String::EndsWith(CStr text, CStr endText)
	{
		return EndsWith(text, CStrLength(text), endText);
	}

	String String::SubString(CStr text, UInt textLength, UInt start, UInt length)
	{
		if(length > textLength) length = textLength;
		if(!text || !length || start + length > textLength) return String();
		return String(text + start, text + start + length);
	}

	String String::SubString(CStr text, UInt start, UInt length)
	{
		UInt textLength =  CStrLength(text);
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

		if(!delimiters || !(delimitersLength = CStrLength(delimiters)))
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

	//Digits are 0123456789
	Bool String::IsDigit(TChar chr)
	{
		return String::IndexOf(Text("0123456789"), 10U, chr) != -1;
	}

	Bool String::IsDigit(CStr text, UInt textLength)
	{
		CStr it = text;
		CStr end = text + textLength;

		while(it < end)
			if(!IsDigit(*it++))
				return false;

		return true;
	}
	
	Bool String::IsDigit(CStr text)
	{
		return IsDigit(text, CStrLength(text));
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
		UInt n = CStrLength(text);
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
		return CStrPtr();
	}

	String& String::operator=(CStr text)
	{
		UInt n = CStrLength(text);
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
				*this = text.CStrPtr();
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
		UInt length = CStrLength(text);
		UInt current_length, new_length;
		Bool MaxSizeOverflow;

		if(length)
		{
			//Check for MaxSize overflow
			current_length = _vctr.Length();
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
			_vctr.Remove(_vctr.Length() - 1);
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

	UInt String::Capacity() const
	{
		return _vctr.Capacity();
	}

	UInt String::Length() const
	{
		return _vctr.IsEmpty() ? 0U : _vctr.Length() - 1;
	}

	UInt String::ByteSize() const
	{
		return Length() * sizeof(TChar);
	}

	CStr String::CStrPtr() const
	{
		return _vctr.Begin();
	}

	Int String::Compare(CStr target) const
	{
		return Compare(CStrPtr(), target);
	}

	UInt String::IndexOf(TChar const chr, UInt start) const
	{
		return IndexOf(CStrPtr(), chr, start);
	}

	UInt String::LastIndexOf(TChar const chr, UInt start) const
	{
		return LastIndexOf(CStrPtr(), chr, start);
	}

	Bool String::StartsWith(CStr startText)
	{
		return StartsWith(CStrPtr(), startText);
	}

	Bool String::EndsWith(CStr endText)
	{
		return EndsWith(CStrPtr(), Length(), endText);
	}

	String String::SubString(UInt start, UInt length) const
	{
		return SubString(CStrPtr(), Length(), start, length);
	}

	String::StrPtrVec* String::Split(CStr delimiters) const
	{
		return Split(CStrPtr(), Length(), delimiters);
	}

	/******************************************************************************/
	/* Public Functions ***********************************************************/
	/******************************************************************************/

	void String::Clear()
	{
		if(!IsEmpty())
		{
			_vctr.Clear();
			*_vctr.Begin() = 0;
		}
	}

	void String::Reserve(UInt capacity)
	{
		_vctr.Reserve(capacity + sizeof(TChar));
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
		auto buffer = _vctr.DrivePointer(future_length + 1);
		buffer[future_length] = Text('\0');
		return buffer;
	}

	String& String::TrimLeft()
	{
		auto it = _vctr.Begin();
		UInt size;

		while(it < _vctr.End() && *it == 32)
			++it;

		if(it != _vctr.Begin())
		{
			size = _vctr.End() - it;
			Memory::Move(it, _vctr.DrivePointer(size), size * sizeof(TChar));
		}

		return *this;
	}

	String& String::TrimRight()
	{
		Vector::Element* it;

		while((it = _vctr.RBegin() - 1) > _vctr.REnd() && *it == 32)
			_vctr.Remove(*it);

		return *this;
	}

	String& String::Trim()
	{
		return TrimRight().TrimLeft();
	}

	Bool String::IsDigit()
	{
		return IsDigit(CStr(), Length());
	}
}
