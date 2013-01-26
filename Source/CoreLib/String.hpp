/*
#pragma once
#include "Types.hpp"
#include "DataStruct/Vector.hpp"

namespace Core
{
	class String
	{
		DataStruct::Vector<TChar> Vector;

		public:
		String();
		String(UInt Capacity);
		String(TChar const * Source);
		String(String const & Source);
		~String();

		String& operator=(String const & Source);
		Bool operator==(String const & Source);
		String& operator+(String const & Source);

		UInt GetCapacity() const;
		UInt GetLength() const;
		TChar const * GetTChar() const;

		Int Compare(TChar const * Target) const;
		Int Compare(String const & Target) const;

		private:
		static UInt GetTCharLength(TChar const * Source);
	};
}
*/
