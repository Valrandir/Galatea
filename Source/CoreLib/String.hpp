#pragma once
#include "Types.hpp"
#include "DataStruct/Vector.hpp"

namespace Core
{
	class String : private DataStruct::Vector<TChar>
	{
		static UInt GetTCharLength(TChar const * val);

		public:
		String();
		String(UInt capacity);
		String(TChar const * val);
		String(String const & val);
		String(String const && val);
		~String();

		String& operator=(String const & val);
		Bool operator==(TChar const * val);
		Bool operator==(String const & val);
		String& operator+(TChar const * val);
		String& operator+(String const & val);
		String& operator+=(TChar const * val);
		String& operator+=(String const & val);

		UInt GetCapacity() const;
		UInt GetLength() const;
		TChar const * GetTChar() const;

		Int Compare(TChar const * val) const;
		Int Compare(String const & val) const;
	};
}
