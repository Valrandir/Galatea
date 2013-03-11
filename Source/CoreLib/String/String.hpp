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
		/* StrPtrVec internal class */
		class StrPtrVec : public DataStruct::Vector<String*>
		{
			public:
			StrPtrVec();
			StrPtrVec(UInt capacity);
			~StrPtrVec();
		};

		/* public static */
		static UInt CStrLength(CStr);
		static void Format(TChar* buffer, UInt buffer_size, CStr format, ...);
		static String FormatToStr(CStr format, ...);
		static Int Compare(CStr source, CStr target);
		static UInt IndexOf(CStr text, UInt textLength, TChar const chr, UInt start = 0);
		static UInt IndexOf(CStr text, TChar const chr, UInt start = 0);
		static UInt LastIndexOf(CStr text, UInt textLength, TChar const chr, UInt start = NoMatch);
		static UInt LastIndexOf(CStr text, TChar const chr, UInt start = NoMatch);
		static Bool StartsWith(CStr text, UInt textLength, CStr startText);
		static Bool StartsWith(CStr text, CStr startText);
		static Bool EndsWith(CStr text, UInt textLength, CStr endText);
		static Bool EndsWith(CStr text, CStr endText);
		static String SubString(CStr text, UInt textLength, UInt start, UInt length);
		static String SubString(CStr text, UInt start, UInt length);
		static StrPtrVec* Split(CStr text, UInt charCount, CStr delimiters);
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
		UInt Capacity() const;
		UInt Length() const;
		CStr CStrPtr() const;
		Int Compare(CStr target) const;
		UInt IndexOf(TChar const chr, UInt start = 0) const;
		UInt LastIndexOf(TChar const chr, UInt start = NoMatch) const;
		Bool StartsWith(CStr startText);
		Bool EndsWith(CStr endText);
		String SubString(UInt start, UInt length) const;
		StrPtrVec* Split(CStr delimiters) const;

		/* Public Functions */
		void Reserve(UInt capacity);
		void Shrink();
		void Append(CStr str);
		void Append(String const & str);
		void AppendLine(CStr str);
		void AppendLine(String const & str);
		TChar* DrivePointer(UInt future_length);
		String& TrimLeft();
		String& TrimRight();
		String& Trim();
	};
}
