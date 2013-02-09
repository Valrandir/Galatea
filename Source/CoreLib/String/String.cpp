#include <stdarg.h>
#include "String.hpp"

void FormatImpl(Core::TChar* buffer, Core::UInt buffer_size, Core::TChar const * format, va_list args);
Core::UInt FormatImplGetRequiredSize(Core::TChar const * format, va_list args);

namespace Core
{
	String::String() : Vector(Vector::CtorModeEnum::Pod)
	{
	}

	String::String(UInt capacity) : Vector(capacity, Vector::CtorModeEnum::Pod)
	{
	}

	String::String(TChar const * val) : Vector(Vector::CtorModeEnum::Pod)
	{
		UInt n = GetTCharLength(val);
		if(n) AddRange(val, val + n + 1);
	}

	String::String(String const & val) : Vector(val)
	{
	}

	String::String(String && val) : Vector((Vector&&)val)
	{
	}

	String::~String()
	{
	}

	String& String::operator=(TChar const * val)
	{
		UInt n = GetTCharLength(val);
		Vector::Clear();
		if(n) AddRange(val, val + n + 1);
		return *this;
	}

	String& String::operator=(String const & val)
	{
		if(this != &val)
		{
			if(val.IsEmpty())
				Clear();
			else
				*this = val.GetTChar();
		}

		return *this;
	}

	String& String::operator=(String && val)
	{
		Vector::operator=((Vector&&)val);
		return *this;
	}

	String& String::operator+=(TChar const * val)
	{
		UInt n = GetTCharLength(val);
		if(n)
		{
			Vector::Remove(Vector::GetLength() - 1);
			AddRange(val, val + n + 1);
		}
		return *this;
	}

	String& String::operator+=(String const & val)
	{
		if(!val.IsEmpty())
		{
			Vector::Remove(Vector::GetLength() - 1);
			Vector::operator+=(val);
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
		return Vector::operator[](index);
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
		return Vector::IsEmpty();
	}

	UInt String::GetCapacity() const
	{
		return Vector::GetCapacity();
	}

	UInt String::GetLength() const
	{
		return Vector::IsEmpty() ? 0U : Vector::GetLength() - 1;
	}

	TChar const * String::GetTChar() const
	{
		return Vector::Begin();
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
		FormatImpl(str.DrivePointer(size), size, format, args);
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
		Vector::Reserve(capacity);
	}

	void String::Shrink()
	{
		Vector::Shrink();
	}

	void String::Append(TChar const * val)
	{
		*this += val;
	}

	void String::Append(String const & val)
	{
		*this += val;
	}
}
