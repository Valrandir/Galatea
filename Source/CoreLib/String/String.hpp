#pragma once
#include "../Types.hpp"
#include "../DataStruct/Vector.hpp"

namespace Core
{
	class String
	{
		private:
		typedef DataStruct::Vector<TChar> Vector;
		Vector _vctr;
		static UInt NewLineLength;

		public:
		String();
		String(UInt capacity);
		String(TChar const *);
		String(TChar const * begin, TChar const *end);
		String(String const &);
		String(String &&);
		~String();

		String& operator=(TChar const *);
		String& operator=(String const &);
		String& operator=(String &&);
		String& operator+=(TChar const *);
		String& operator+=(String const &);
		String operator+(TChar const *) const;
		String operator+(String const &) const;
		Bool operator==(TChar const *) const;
		Bool operator==(String const &) const;
		Bool operator!=(TChar const *) const;
		Bool operator!=(String const &) const;
		Bool operator>(TChar const *) const;
		Bool operator>(String const &) const;
		Bool operator<(TChar const *) const;
		Bool operator<(String const &) const;
		Bool operator>=(TChar const *) const;
		Bool operator>=(String const &) const;
		Bool operator<=(TChar const *) const;
		Bool operator<=(String const &) const;
		TChar operator[](UInt index) const;

		static UInt GetTCharLength(TChar const *);

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
		void Append(TChar const * str);
		void Append(String const & str);
		void AppendLine(TChar const * str);
		void AppendLine(String const & str);

		TChar* DrivePointer(UInt future_length);

		Int IndexOf(TChar const chr, Int position = 0) const;
		Int LastIndexOf(TChar const chr, Int position = -1) const;

		String SubString(UInt start, UInt length) const;
	};
}
