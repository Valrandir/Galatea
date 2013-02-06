//TODO Add behavior mode to either Clean() or Free().
//Clean keeps extra capacity and favor speed over memory
//Free always shrink when the string gets shorter, using minimal memory at the cost of extra allocations

#pragma once
#include "../Types.hpp"
#include "../DataStruct/Vector.hpp"

namespace Core
{
	class String : private DataStruct::Vector<TChar>
	{
		public:
		String();
		String(UInt capacity);
		String(TChar const * val);
		String(String const & val);
		String(String && val);
		~String();

		String& operator=(TChar const * val);
		String& operator=(String const & val);
		String& operator=(String && val);
		String& operator+=(TChar const * val);
		String& operator+=(String const & val);
		String operator+(TChar const * val) const;
		String operator+(String const & val) const;
		Bool operator==(TChar const * val) const;
		Bool operator==(String const & val) const;
		Bool operator!=(TChar const * val) const;
		Bool operator!=(String const & val) const;
		Bool operator>(TChar const * val) const;
		Bool operator>(String const & val) const;
		Bool operator<(TChar const * val) const;
		Bool operator<(String const & val) const;
		Bool operator>=(TChar const * val) const;
		Bool operator>=(String const & val) const;
		Bool operator<=(TChar const * val) const;
		Bool operator<=(String const & val) const;

		static UInt GetTCharLength(TChar const * val);

		Bool IsEmpty() const;
		UInt GetCapacity() const;
		UInt GetLength() const;
		TChar const * GetTChar() const;

		static void Format(TChar* buffer, UInt buffer_size, TChar const * format, ...);
		static String FormatStr(TChar const * format, ...);

		static Int Compare(TChar const * source, TChar const * target);
		static Int Compare(String const & source, String const & target);

		Int Compare(TChar const * target) const;
		Int Compare(String const & target) const;

		void Reserve(UInt capacity);
		void Shrink();
		void Append(TChar const * val);
		void Append(String const & val);

		//String& Substring(UInt start);
		//String& Substring(UInt start, UInt length);
		//String& Format(TChar const * format, ...);
		//String& Format(String const & format, ...);
		//Bool StartsWith(TChar const * val);
		//Bool StartsWith(String const & val);
		//Bool EndsWith(TChar const * val);
		//Bool EndsWith(String const & val);
	};
}
