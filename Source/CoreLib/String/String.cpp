#include <stdarg.h>
#include "String.hpp"
#include "../Assert/Assert.hpp"

void FormatImpl(Core::TChar* buffer, Core::UInt buffer_size, Core::CStr format, va_list args);
Core::UInt FormatImplGetRequiredSize(Core::CStr format, va_list args);

namespace Core
{
	UInt String::NewLineLength = String::CStrLength(NewLine);
	CStr const String::Empty = Text("");

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
		ASSERT_PARAMETER(text);

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
		ASSERT_PARAMETER(text);
		return CStrLength(text) * sizeof(TChar);
	}

	void String::FormatToBuffer(TChar* buffer, UInt buffer_size, CStr format, ...)
	{
		ASSERT_PARAMETER(buffer);
		ASSERT_PARAMETER(format);

		va_list args;
		va_start(args, format);
		FormatImpl(buffer, buffer_size, format, args);
		va_end(args);
	}

	String String::FormatToString(CStr format, ...)
	{
		ASSERT_PARAMETER(format);

		va_list args;
		UInt size;
		String value;

		va_start(args, format);
		size = FormatImplGetRequiredSize(format, args);
		va_end(args);

		value.Reserve(size);

		va_start(args, format);
		FormatImpl(value._vctr.DrivePointer(size), size, format, args);
		va_end(args);

		return value;
	}

	Int String::Compare(CStr source, CStr target)
	{
		//Return
		//	 0 when source == target
		//	 1 when source >  target
		//	-1 when source <  target

		ASSERT_PARAMETER(source);
		ASSERT_PARAMETER(target);

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

	Bool String::StartsWith(CStr text, UInt textLength, CStr value)
	{
		ASSERT_PARAMETER(text);
		ASSERT_PARAMETER(value);

		CStr end = text + textLength;

		while(text < end && *value && *text == *value)
		{
			++text;
			++value;
		}

		return !*value;
	}

	Bool String::StartsWith(CStr text, CStr value)
	{
		ASSERT_PARAMETER(text);
		ASSERT_PARAMETER(value);

		while(*text && *value && *text == *value)
		{
			++text;
			++value;
		}

		return !*value;
	}

	Bool String::EndsWith(CStr text, UInt textLength, CStr value)
	{
		ASSERT_PARAMETER(text);
		ASSERT_PARAMETER(value);
		CStr it = text + textLength - CStrLength(value);
		return it >= text ? StartsWith(it, value) : false;
	}

	Bool String::EndsWith(CStr text, CStr value)
	{
		ASSERT_PARAMETER(text);
		ASSERT_PARAMETER(value);
		return EndsWith(text, CStrLength(text), value);
	}

	UInt String::IndexOf(CStr text, UInt textLength, CStr value, UInt valueLength, UInt start)
	{
		ASSERT_PARAMETER(text);
		ASSERT_PARAMETER(value);

		CStr it, end;

		if(start >= textLength || textLength < valueLength)
			return NoMatch;

		it = text + start;
		end = text + textLength;

		while(it < end)
		{
			if(valueLength == 1 ? *it == *value : StartsWith(it, value))
				return it - text;
			++it;
		}

		return NoMatch;
	}

	UInt String::IndexOf(CStr text, UInt textLength, CStr value, UInt start)
	{
		ASSERT_PARAMETER(text);
		ASSERT_PARAMETER(value);
		return IndexOf(text, textLength, value, CStrLength(value), start);
	}

	UInt String::IndexOf(CStr text, CStr value, UInt start)
	{
		ASSERT_PARAMETER(text);
		ASSERT_PARAMETER(value);
		return IndexOf(text, CStrLength(text), value, CStrLength(value), start);
	}

	UInt String::LastIndexOf(CStr text, UInt textLength, CStr value, UInt valueLength, UInt start)
	{
		ASSERT_PARAMETER(text);
		ASSERT_PARAMETER(value);

		if(start != Default)
		{
			if(start > textLength)
				return NoMatch;
			else
				textLength = start;
		}

		if(valueLength > textLength)
			return NoMatch;

		CStr rend = text - 1;
		CStr it = text + textLength - valueLength;

		while(rend < it)
		{
			if(valueLength == 1 ? *it == *value : StartsWith(it, valueLength, value))
				return it - text;
			--it;
		}

		return NoMatch;
	}

	//UInt String::LastIndexOf(CStr text, UInt textLength, CStr value, UInt valueLength, UInt start)
	//{
	//	ASSERT_PARAMETER(text);
	//	ASSERT_PARAMETER(value);

	//	CStr rend, it;

	//	if(start >= textLength && start != NoMatch)
	//		return NoMatch;

	//	if(start == NoMatch)
	//		start = textLength - valueLength;

	//	if(start < 0)
	//		return NoMatch;

	//	rend = text - 1;
	//	it = text + start;

	//	//it = start == NoMatch ? text + textLength - valueLength : text + start;

	//	while(rend < it)
	//	{
	//		if(valueLength == 1 ? *it == *value : StartsWith(it, value))
	//			return it - text;
	//		--it;
	//	}

	//	return NoMatch;
	//}

	UInt String::LastIndexOf(CStr text, UInt textLength, CStr value, UInt start)
	{
		ASSERT_PARAMETER(text);
		ASSERT_PARAMETER(value);
		return LastIndexOf(text, textLength, value, CStrLength(value), start);
	}

	UInt String::LastIndexOf(CStr text, CStr value, UInt start)
	{
		ASSERT_PARAMETER(text);
		ASSERT_PARAMETER(value);
		return LastIndexOf(text, CStrLength(text), value, CStrLength(value), start);
	}

	String String::SubString(CStr text, UInt textLength, UInt start, UInt length)
	{
		ASSERT_PARAMETER(text);

		if(length > textLength) length = textLength;
		if(!text || !length || start + length > textLength) return String();
		return String(text + start, text + start + length);
	}

	String String::SubString(CStr text, UInt start, UInt length)
	{
		ASSERT_PARAMETER(text);
		return SubString(text, CStrLength(text), start, length);
	}

	String::StrPtrVec* String::Split(CStr text, UInt textLength, CStr delimiters, UInt delimitersLength)
	{
		ASSERT_PARAMETER(text);
		ASSERT_PARAMETER(delimiters);

		StrPtrVec* vStr;
		CStr begin, it, end;
		UInt count;

		vStr = new StrPtrVec();

		if(!textLength)
			return vStr;

		if(!delimitersLength)
		{
			vStr->Add(new String(text));
			return vStr;
		}

		begin = text;
		it = text;
		end = text + textLength;
		count = 0U;

		while(it < end)
		{
			if(delimitersLength == 1 ? *it == *delimiters : IndexOf(delimiters, delimitersLength, it, 1U, 0U) != NoMatch)
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

	String::StrPtrVec* String::Split(CStr text, UInt textLength, CStr delimiters)
	{
		ASSERT_PARAMETER(text);
		ASSERT_PARAMETER(delimiters);
		return Split(text, textLength, delimiters, CStrLength(delimiters));
	}

	String::StrPtrVec* String::Split(CStr text, CStr delimiters)
	{
		ASSERT_PARAMETER(text);
		ASSERT_PARAMETER(delimiters);
		return Split(text, CStrLength(text), delimiters, CStrLength(delimiters));
	}

	//Digits are 0123456789
	Bool String::IsDigit(TChar chr)
	{
		return String::IndexOf(Text("0123456789"), 10U, (CStr)&chr) != -1;
	}

	Bool String::IsDigit(CStr text, UInt textLength)
	{
		ASSERT_PARAMETER(text);
		CStr it = text;
		CStr end = text + textLength;

		while(it < end)
			if(!IsDigit(*it++))
				return false;

		return true;
	}
	
	Bool String::IsDigit(CStr text)
	{
		ASSERT_PARAMETER(text);
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

	//value must be null terminated
	String::String(CStr value) : _vctr(Vector::CtorModeEnum::Pod)
	{
		ASSERT_PARAMETER(value);
		UInt length = CStrLength(value);
		if(length)
			_vctr.AddRange(value, value + length + 1);
	}

	//if length > 0 value must not be null
	String::String(CStr value, UInt length) : _vctr(Vector::CtorModeEnum::Pod)
	{
		ASSERT_PARAMETER(length == 0 || value);
		if(length)
			_vctr.AddRange(value, value + length + 1);
	}

	String::String(CStr begin, CStr end) : _vctr(Vector::CtorModeEnum::Pod)
	{
		ASSERT_PARAMETER(begin);
		ASSERT_PARAMETER(end);
		ASSERT(begin <= end);

		if(begin != end)
			_vctr.AddRange(begin, end);

		_vctr.Add(Text('\0'));
	}

	String::String(String const & value) : _vctr(value._vctr)
	{
	}

	String::String(String && value) : _vctr((Vector&&)value)
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
		ASSERT_PARAMETER(text);

		UInt n = CStrLength(text);
		_vctr.Clear();

		if(n)
			_vctr.AddRange(text, text + n + 1);

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
		//ASSERT_PARAMETER(text);
		UInt length = CStrLength(text);
		UInt current_length, new_length;
		Bool MaxSizeOverflow;

		if(length)
		{
			//Check for MaxSize overflow
			current_length = _vctr.Length();
			new_length = current_length + length;
			MaxSizeOverflow = !(new_length >= MaxSize || new_length < current_length);
			ASSERT(MaxSizeOverflow);

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
		ASSERT_PARAMETER(text);
		return String(*this) += text;
	}

	String String::operator+(String const & text) const
	{
		return String(*this) += text;
	}

	Bool String::operator==(CStr text) const { ASSERT_PARAMETER(text); return Compare(text) ==  0; }
	Bool String::operator!=(CStr text) const { ASSERT_PARAMETER(text); return Compare(text) !=  0; }
	Bool String::operator> (CStr text) const { ASSERT_PARAMETER(text); return Compare(text) ==  1; }
	Bool String::operator< (CStr text) const { ASSERT_PARAMETER(text); return Compare(text) == -1; }
	Bool String::operator>=(CStr text) const { ASSERT_PARAMETER(text); return Compare(text) >=  0; }
	Bool String::operator<=(CStr text) const { ASSERT_PARAMETER(text); return Compare(text) <=  0; }

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
		return IsEmpty() ? String::Empty : _vctr.Begin();
	}

	Int String::Compare(CStr value) const
	{
		ASSERT_PARAMETER(value);
		return Compare(CStrPtr(), value);
	}

	Bool String::StartsWith(CStr value)
	{
		ASSERT_PARAMETER(value);
		return StartsWith(CStrPtr(), value);
	}

	Bool String::EndsWith(CStr value)
	{
		ASSERT_PARAMETER(value);
		return EndsWith(CStrPtr(), Length(), value);
	}

	UInt String::IndexOf(CStr value, UInt start) const
	{
		ASSERT_PARAMETER(value);
		return IndexOf(CStrPtr(), Length(), value, CStrLength(value), start);
	}

	UInt String::LastIndexOf(CStr value, UInt start) const
	{
		ASSERT_PARAMETER(value);
		return LastIndexOf(CStrPtr(), Length(), value, CStrLength(value), start);
	}

	String String::SubString(UInt start, UInt length) const
	{
		return SubString(CStrPtr(), Length(), start, length);
	}

	String::StrPtrVec* String::Split(CStr delimiters) const
	{
		ASSERT_PARAMETER(delimiters);
		return Split(CStrPtr(), Length(), delimiters);
	}

	/******************************************************************************/
	/* Public Functions ***********************************************************/
	/******************************************************************************/

	//Clear does not deallocate memorys
	void String::Clear()
	{
		_vctr.Clear();
	}

	void String::Reserve(UInt capacity)
	{
		_vctr.Reserve(capacity + sizeof(TChar));
	}

	void String::Shrink()
	{
		_vctr.Shrink();
	}

	String& String::Append(CStr value)
	{
		ASSERT_PARAMETER(value);
		*this += value;
		return *this;
	}

	String& String::Append(String const & value)
	{
		*this += value;
		return *this;
	}

	String& String::AppendLine(CStr value)
	{
		ASSERT_PARAMETER(value);
		*this += value;
		*this += NewLine;
		return *this;
	}

	String& String::AppendLine(String const & value)
	{
		*this += value;
		*this += NewLine;
		return *this;
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

	UInt HowManyThereIs(CStr text, UInt textLength, CStr value, UInt valueLength)
	{
		UInt it = 0U, idx;
		UInt count = 0U;

		while(it < textLength)
		{
			idx = String::IndexOf(text, textLength, value, valueLength, it);
			if(idx != String::NoMatch)
			{
				it = idx + valueLength;
				++count;
			}
			else
				break;
		}

		return count;
	}

	String& String::Overwrite(UInt start, CStr begin, CStr end)
	{
		ASSERT_PARAMETER(begin);
		ASSERT_PARAMETER(end);
		ASSERT_RANGE(begin <= end);
		ASSERT_RANGE(start + (end - begin) < Length());
		Memory::Move((VoidPtr)begin, _vctr.Begin() + start, end - begin);
		return *this;
	}

	String& String::Replace(CStr oldValue, CStr newValue)
	{
		ASSERT_PARAMETER(oldValue);
		ASSERT_PARAMETER(newValue);

		if(CStrLength(oldValue) > Length())
			return *this;

		if(IndexOf(oldValue) == NoMatch)
			return *this;

		UInt oldValueLength = CStrLength(oldValue);
		UInt newValueLength = CStrLength(newValue);
		UInt count = HowManyThereIs(CStrPtr(), Length(), oldValue, oldValueLength);
		UInt newSize = (newValueLength - oldValueLength) * count;

		Reserve(newSize);

		return *this;
	}
}
