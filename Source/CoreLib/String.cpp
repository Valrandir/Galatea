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

	String::String(TChar const * val) : Vector(Vector::RawCopyEnabled)
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
