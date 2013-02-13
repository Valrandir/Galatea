#include <stdarg.h>
#include "String.hpp"

void FormatImpl(Core::TChar* buffer, Core::UInt buffer_size, Core::TChar const * format, va_list args);
Core::UInt FormatImplGetRequiredSize(Core::TChar const * format, va_list args);

namespace Core
{
	String::String() : _vctr(Vector::CtorModeEnum::Pod)
	{
	}

	String::String(UInt capacity) : _vctr(capacity, Vector::CtorModeEnum::Pod)
	{
	}

	String::String(TChar const * val) : _vctr(Vector::CtorModeEnum::Pod)
	{
		UInt n = GetTCharLength(val);
		if(n) _vctr.AddRange(val, val + n + 1);
	}

	String::String(TChar const * begin, TChar const * end) : _vctr(Vector::CtorModeEnum::Pod)
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

	String& String::operator=(TChar const * val)
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

	String& String::operator+=(TChar const * val)
	{
		UInt n = GetTCharLength(val);
		if(n)
		{
			_vctr.Remove(_vctr.GetLength() - 1);
			_vctr.AddRange(val, val + n + 1);
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

	String String::operator+(TChar const * val) const
	{
		return String(*this) += val;
	}

	String String::operator+(String const & val) const
	{
		return String(*this) += val;
	}

	Bool String::operator==(TChar  const * val) const { return Compare(val) ==  0; }
	Bool String::operator==(String const & val) const { return Compare(val) ==  0; }
	Bool String::operator!=(TChar  const * val) const { return Compare(val) !=  0; }
	Bool String::operator!=(String const & val) const { return Compare(val) !=  0; }
	Bool String::operator> (TChar  const * val) const { return Compare(val) ==  1; }
	Bool String::operator> (String const & val) const { return Compare(val) ==  1; }
	Bool String::operator< (TChar  const * val) const { return Compare(val) == -1; }
	Bool String::operator< (String const & val) const { return Compare(val) == -1; }
	Bool String::operator>=(TChar  const * val) const { return Compare(val) >=  0; }
	Bool String::operator>=(String const & val) const { return Compare(val) >=  0; }
	Bool String::operator<=(TChar  const * val) const { return Compare(val) <=  0; }
	Bool String::operator<=(String const & val) const { return Compare(val) <=  0; }

	TChar String::operator[](UInt index) const
	{
		return _vctr.operator[](index);
	}

	UInt String::GetTCharLength(TChar const * val)
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

	TChar const * String::GetTChar() const
	{
		return _vctr.Begin();
	}

	void String::Format(TChar* buffer, UInt buffer_size, TChar const * format, ...)
	{
		va_list args;
		va_start(args, format);
		FormatImpl(buffer, buffer_size, format, args);
		va_end(args);
	}

	String String::FormatStr(TChar const * format, ...)
	{
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

	//Return
	//	 0 when source == target
	//	 1 when source >  target
	//	-1 when source <  target
	Int String::Compare(TChar const * source, TChar const * target)
	{
		TChar const * empty = Text("");

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

	Int String::Compare(String const & source, String const & target)
	{
		return Compare(source.GetTChar(), target.GetTChar());
	}

	Int String::Compare(TChar const * target) const
	{
		return Compare(GetTChar(), target);
	}

	Int String::Compare(String const & target) const
	{
		return Compare(GetTChar(), target.GetTChar());
	}

	void String::Reserve(UInt capacity)
	{
		_vctr.Reserve(capacity);
	}

	void String::Shrink()
	{
		_vctr.Shrink();
	}

	void String::Append(TChar const * str)
	{
		*this += str;
	}

	void String::Append(String const & str)
	{
		*this += str;
	}

	void String::AppendLine(TChar const * str)
	{
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

	Int String::IndexOf(TChar const chr, Int position) const
	{
		Int idx, length = GetLength();

		if(length == 0 || position < 0 || position >= length) return -1;

		for(idx = position; idx < length; ++idx)
			if(_vctr[idx] == chr)
				return idx;

		return -1;
	}

	Int String::LastIndexOf(TChar const chr, Int position) const
	{
		Int idx, length = GetLength();

		if(position == -1) position = length - 1;
		if(length == 0 || position < 0 || position >= length) return -1;

		for(idx = position; idx >= 0; --idx)
		{
			if(_vctr[idx] == chr)
			{
				return idx;
			}
		}

		return -1;
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
}
