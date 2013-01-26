//#include "String.hpp"
//
//namespace Core
//{
//	String::String()
//	{
//	}
//
//	String::String(UInt Capacity)
//	{
//		Vector.Reserve(Capacity);
//	}
//
//	String::String(String const & Source)
//	{
//		Vector = Source.Vector;
//	}
//
//	String::String(TChar const * Source)
//	{
//		Vector.Reserve(GetTCharLength(Source));
//	}
//
//	String& String::operator=(String const & Source)
//	{
//		Vector = Source.Vector;
//		return *this;
//	}
//
//	String::~String()
//	{
//	}
//
//	Bool String::operator==(String const & Source)
//	{
//		return true;
//	}
//
//	String& String::operator+(String const & Source)
//	{
//		return *this;
//	}
//
//	UInt String::GetCapacity() const
//	{
//		return Vector.GetCapacity();
//	}
//
//	UInt String::GetLength() const
//	{
//		return Vector.GetLength();
//	}
//
//	TChar const * String::GetTChar() const
//	{
//		return Vector.Begin();
//	}
//
//	Int String::Compare(TChar const * Target) const
//	{
//		TChar const * Source = GetTChar();
//
//		while(true)
//		{
//			if(*Source == '\0' && *Target == '\0') return 0;
//			if(*Source == '\0') return 1;
//			if(*Target == '\0') return -1;
//			if(*Source > *Target) return 1;
//			if(*Source < *Target) return -1;
//			++Source;
//			++Target;
//		}
//	}
//
//	Int String::Compare(String const & Target) const
//	{
//		return Compare(Target.GetTChar());
//	}
//
//	UInt String::GetTCharLength(TChar const * Source)
//	{
//		UInt Length = 0U;
//
//		while(*Source != '\0')
//		{
//			++Source;
//			++Length;
//		}
//
//		return Length;
//	}
//}
