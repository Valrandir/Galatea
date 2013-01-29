#include "String.hpp"

namespace Core
{
	String::String() : Vector(Vector::RawCopyEnabled)
	{
	}

	String::String(UInt capacity) : Vector(Vector::RawCopyEnabled)
	{
		Reserve(capacity);
	}

	String::String(TChar const * val)
	{
		UInt n = GetTCharLength(val);
		AddRange(val, val + n);
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
		AddRange(val, val + n);
		return *this;
	}

	String& String::operator=(String const & val)
	{
		if(this != &val)
			if(val.IsEmpty())
				Clear();
			else
				*this = val.GetTChar();

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
		AddRange(val, val + n);
		return *this;
	}

	String& String::operator+=(String const & val)
	{
		Vector::operator+=(val);
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
	Int  String::operator> (TChar  const * val) const { return Compare(val) ==  1; }
	Int  String::operator> (String const & val) const { return Compare(val) ==  1; }
	Int  String::operator< (TChar  const * val) const { return Compare(val) == -1; }
	Int  String::operator< (String const & val) const { return Compare(val) == -1; }
	Int  String::operator>=(TChar  const * val) const { return Compare(val) >=  1; }
	Int  String::operator>=(String const & val) const { return Compare(val) >=  1; }
	Int  String::operator<=(TChar  const * val) const { return Compare(val) <= -1; }
	Int  String::operator<=(String const & val) const { return Compare(val) <= -1; }

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

		return length + 1;
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
		return Vector::GetLength();
	}

	TChar const * String::GetTChar() const
	{
		return Vector::Begin();
	}

	//Return 0 when self == target, 1 when self > target, -1 when self < target
	Int String::Compare(TChar const * target) const
	{
		TChar const * val = GetTChar();
		TChar const * empty = Text("");

		if(val == NULL) val = empty;
		if(target == NULL) target = empty;

		while(true)
		{
			if(*val == '\0' && *target == '\0') return 0;
			if(*val == '\0') return -1;
			if(*target == '\0') return 1;
			if(*val < *target) return -1;
			if(*val > *target) return 1;
			++val;
			++target;
		}

		return 0;
	}

	Int String::Compare(String const & target) const
	{
		return Compare(target.GetTChar());
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
