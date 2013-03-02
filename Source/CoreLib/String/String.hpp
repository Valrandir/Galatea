#pragma once
#include "../Types.hpp"
#include "../DataStruct/Vector.hpp"

namespace Core
{
	class String
	{
		static UInt NewLineLength;
		typedef DataStruct::Vector<TChar> Vector;
		Vector _vctr;

		public:
		/* public static */
		static UInt GetTCharLength(CStr);
		static void Format(TChar* buffer, UInt buffer_size, CStr format, ...);
		static String FormatToStr(CStr format, ...);
		static Int Compare(CStr source, CStr target);
		static const UInt NoMatch = (UInt)-1;
		static const UInt MaxSize = NoMatch - 1;

		/* Constructors && Destructor */
		String();
		String(UInt capacity);
		String(CStr);
		String(CStr begin, CStr end);
		String(String const &);
		String(String &&);
		~String();

		/* Operators */
		operator CStr () const;
		String& operator=(CStr);
		String& operator=(String const &);
		String& operator=(String &&);
		String& operator+=(CStr);
		String& operator+=(String const &);
		String operator+(CStr) const;
		String operator+(String const &) const;
		Bool operator==(CStr) const;
		Bool operator!=(CStr) const;
		Bool operator>(CStr) const;
		Bool operator<(CStr) const;
		Bool operator>=(CStr) const;
		Bool operator<=(CStr) const;
		TChar operator[](UInt index) const;

		/* Public Const Functions */
		Bool IsEmpty() const;
		UInt GetCapacity() const;
		UInt GetLength() const;
		CStr GetTChar() const;
		Int Compare(CStr target) const;
		UInt IndexOf(TChar const chr, UInt position = 0) const;
		UInt LastIndexOf(TChar const chr, UInt position = NoMatch) const;
		String SubString(UInt start, UInt length) const;

		/* Public Functions */
		void Reserve(UInt capacity);
		void Shrink();
		void Append(CStr str);
		void Append(String const & str);
		void AppendLine(CStr str);
		void AppendLine(String const & str);
		TChar* DrivePointer(UInt future_length);
	};
}
