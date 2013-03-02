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
		static UInt GetTCharLength(TChar const *);
		static void Format(TChar* buffer, UInt buffer_size, TChar const * format, ...);
		static String FormatToStr(TChar const * format, ...);
		static Int Compare(TChar const * source, TChar const * target);
		static const UInt NoMatch = (UInt)-1;
		static const UInt MaxSize = NoMatch - 1;

		/* Constructors && Destructor */
		String();
		String(UInt capacity);
		String(TChar const *);
		String(TChar const * begin, TChar const *end);
		String(String const &);
		String(String &&);
		~String();

		/* Operators */
		operator TChar const * () const;
		String& operator=(TChar const *);
		String& operator=(String const &);
		String& operator=(String &&);
		String& operator+=(TChar const *);
		String& operator+=(String const &);
		String operator+(TChar const *) const;
		String operator+(String const &) const;
		Bool operator==(TChar const *) const;
		Bool operator!=(TChar const *) const;
		Bool operator>(TChar const *) const;
		Bool operator<(TChar const *) const;
		Bool operator>=(TChar const *) const;
		Bool operator<=(TChar const *) const;
		TChar operator[](UInt index) const;

		/* Public Const Functions */
		Bool IsEmpty() const;
		UInt GetCapacity() const;
		UInt GetLength() const;
		TChar const * GetTChar() const;
		Int Compare(TChar const * target) const;
		UInt IndexOf(TChar const chr, UInt position = 0) const;
		UInt LastIndexOf(TChar const chr, UInt position = NoMatch) const;
		String SubString(UInt start, UInt length) const;

		/* Public Functions */
		void Reserve(UInt capacity);
		void Shrink();
		void Append(TChar const * str);
		void Append(String const & str);
		void AppendLine(TChar const * str);
		void AppendLine(String const & str);
		TChar* DrivePointer(UInt future_length);
	};
}
