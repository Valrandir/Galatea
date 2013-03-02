#include <stdarg.h>
#include "String.hpp"
#include "../System/Assert/Assert.hpp"

void FormatImpl(Core::TChar* buffer, Core::UInt buffer_size, Core::CStr format, va_list args);
Core::UInt FormatImplGetRequiredSize(Core::CStr format, va_list args);

namespace Core
{
	UInt String::NewLineLength = String::GetTCharLength(NewLine);

	/******************************************************************************/
	/* public static **************************************************************/
	/******************************************************************************/

	UInt String::GetTCharLength(CStr val)
	{
		UInt length = 0U;

		if(val == NULL)
			return 0U;

		while(*val != '\0')
		{
			++val;
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

	/******************************************************************************/
	/* Constructors && Destructor *************************************************/
	/******************************************************************************/

	String::String() : _vctr(Vector::CtorModeEnum::Pod)
	{
	}

	String::String(UInt capacity) : _vctr(capacity, Vector::CtorModeEnum::Pod)
	{
	}

	String::String(CStr val) : _vctr(Vector::CtorModeEnum::Pod)
	{
		UInt n = GetTCharLength(val);
		if(n) _vctr.AddRange(val, val + n + 1);
	}

	String::String(CStr begin, CStr end) : _vctr(Vector::CtorModeEnum::Pod)
	{
		_vctr.Reserve(end - begin + 1);
		_vctr.AddRange(begin, end);
		_vctr.Add(Text('\0'));
	}

	String::String(String const & val) : _vctr(val._vctr)
	{
	}

	String::String(String && val) : _vctr((Vector&&)val)
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
		return GetTChar();
	}

	String& String::operator=(CStr val)
	{
		UInt n = GetTCharLength(val);
		_vctr.Clear();
		if(n) _vctr.AddRange(val, val + n + 1);
		return *this;
	}

	String& String::operator=(String const & val)
	{
		if(this != &val)
		{
			if(val.IsEmpty())
				_vctr.Clear();
			else
				*this = val.GetTChar();
		}
	
		return *this;
	}

	String& String::operator=(String && val)
	{
		_vctr.operator=((Vector&&)val);
		return *this;
	}

	String& String::operator+=(CStr val)
	{
		Assert(val);
		UInt length = GetTCharLength(val);
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
			_vctr.AddRange(val, val + length + 1);
		}
		return *this;
	}

	String& String::operator+=(String const & val)
	{
		if(!val.IsEmpty())
		{
			_vctr.Remove(_vctr.GetLength() - 1);
			_vctr.operator+=(val._vctr);
		}
		return *this;
	}

	String String::operator+(CStr val) const
	{
		Assert(val);
		return String(*this) += val;
	}

	String String::operator+(String const & val) const
	{
		return String(*this) += val;
	}

	Bool String::operator==(TChar  const * val) const { return Compare(val) ==  0; }
	Bool String::operator!=(TChar  const * val) const { return Compare(val) !=  0; }
	Bool String::operator> (TChar  const * val) const { return Compare(val) ==  1; }
	Bool String::operator< (TChar  const * val) const { return Compare(val) == -1; }
	Bool String::operator>=(TChar  const * val) const { return Compare(val) >=  0; }
	Bool String::operator<=(TChar  const * val) const { return Compare(val) <=  0; }

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

	CStr String::GetTChar() const
	{
		return _vctr.Begin();
	}

	Int String::Compare(CStr target) const
	{
		return Compare(GetTChar(), target);
	}

	UInt String::IndexOf(TChar const chr, UInt position) const
	{
		UInt idx, length = GetLength();

		if(length == 0 || position < 0 || position > length) return NoMatch;

		for(idx = position; idx < length; ++idx)
			if(_vctr[idx] == chr)
				return idx;

		return NoMatch;
	}

	UInt String::LastIndexOf(TChar const chr, UInt position) const
	{
		UInt idx, length = GetLength();

		if(position == NoMatch) position = length - 1;
		if(length == 0 || position < 0 || position > length) return NoMatch;

		for(idx = position; idx >= 0 && idx != NoMatch; --idx)
		{
			if(_vctr[idx] == chr)
			{
				return idx;
			}
		}

		return NoMatch;
	}

	String String::SubString(UInt start, UInt length) const
	{
		UInt const self_length = GetLength();

		if(IsEmpty() || length == 0 || start < 0 || start >= self_length)
			return String();

		if(length >= self_length)
			length = self_length;

		return String(&_vctr[start], &_vctr[start + length]);
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
