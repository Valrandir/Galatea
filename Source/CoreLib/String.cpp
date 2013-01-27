#include "String.hpp"

namespace Core
{
	UInt String::GetTCharLength(TChar const * val)
	{
		UInt length = 0U;

		while(*val != '\0')
		{
			++val;
			++length;
		}

		return length;
	}

	String::String()
	{
	}

	String::String(UInt capacity)
	{
		Reserve(capacity);
	}

	String::String(String const & val) : Vector(val)
	{
	}

	String::String(TChar const * val)
	{
		Reserve(GetTCharLength(val));
	}

	String& String::operator=(String const & val)
	{
		Vector::operator=(val);
		return *this;
	}

	String::~String()
	{
	}

	Bool String::operator==(String const & val)
	{
		return true;
	}

	String& String::operator+(String const & val)
	{
		return *this;
	}

	UInt String::GetCapacity() const
	{
		return Vector::GetCapacity();
	}

	UInt String::GetLength() const
	{
		return Vector::GetLength();
	}

	TChar const * String::GetTChar() const
	{
		return Vector::Begin();
	}

	Int String::Compare(TChar const * target) const
	{
		TChar const * val = GetTChar();

		while(true)
		{
			if(*val == '\0' && *target == '\0') return 0;
			if(*val == '\0') return 1;
			if(*target == '\0') return -1;
			if(*val > *target) return 1;
			if(*val < *target) return -1;
			++val;
			++target;
		}
	}

	Int String::Compare(String const & target) const
	{
		return Compare(target.GetTChar());
	}
}
