/*
	String defaults to String::Empty
*/

#pragma once
#include "../Types.hpp"
#include "../DataStruct/Vector.hpp"

namespace Core
{
	class String
	{
		static UInt NewLineLength;

		public:
		static CStr const Empty;

		private:
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
		static UInt CStrByteSize(CStr);
		static void FormatToBuffer(TChar* buffer, UInt buffer_size, CStr format, ...);
		static String FormatToString(CStr format, ...);
		static Int Compare(CStr source, CStr target);
		static Bool StartsWith(CStr text, UInt textLength, CStr value);
		static Bool StartsWith(CStr text, CStr value);
		static Bool EndsWith(CStr text, UInt textLength, CStr value);
		static Bool EndsWith(CStr text, CStr value);
		static UInt IndexOf(CStr text, UInt textLength, CStr value, UInt valueLength, UInt start = 0);
		static UInt IndexOf(CStr text, UInt textLength, CStr value, UInt start = 0);
		static UInt IndexOf(CStr text, CStr value, UInt start = 0);
		static UInt LastIndexOf(CStr text, UInt textLength, CStr value, UInt valueLength, UInt start = Default);
		static UInt LastIndexOf(CStr text, UInt textLength, CStr value, UInt start = Default);
		static UInt LastIndexOf(CStr text, CStr value, UInt start = Default);
		static String SubString(CStr text, UInt textLength, UInt start, UInt length);
		static String SubString(CStr text, UInt start, UInt length);

		//StrPtrVec* must be manually deleted to avoid leaks
		static StrPtrVec* Split(CStr text, UInt textLength, CStr delimiters, UInt delimitersLength);
		static StrPtrVec* Split(CStr text, UInt textLength, CStr delimiters);
		static StrPtrVec* Split(CStr text, CStr delimiters);

		static Bool IsDigit(TChar chr);
		static Bool IsDigit(CStr text, UInt textLength);
		static Bool IsDigit(CStr text);
		static const UInt NoMatch = (UInt)-1;
		static const UInt Default = NoMatch;
		static const UInt MaxSize = NoMatch - 1;

		/* Constructors && Destructor */
		String();
		String(UInt capacity);
		String(CStr value);
		String(CStr value, UInt length);
		String(CStr begin, CStr end);
		String(String const & value);
		String(String && value);
		~String();

		/* Operators */
		operator CStr () const;
		String& operator=(CStr text);
		String& operator=(String const &text);
		String& operator=(String && text);
		String& operator+=(CStr text);
		String& operator+=(String const & text);
		String operator+(CStr text) const;
		String operator+(String const & text) const;
		Bool operator==(CStr text) const;
		Bool operator!=(CStr text) const;
		Bool operator>(CStr text) const;
		Bool operator<(CStr text) const;
		Bool operator>=(CStr text) const;
		Bool operator<=(CStr text) const;
		TChar operator[](UInt index) const;

		/* Public Const Functions */
		Bool IsEmpty() const;
		UInt Capacity() const;
		UInt Length() const;
		UInt ByteSize() const;
		CStr CStrPtr() const;
		Int Compare(CStr value) const;
		Bool StartsWith(CStr value);
		Bool EndsWith(CStr value);
		UInt IndexOf(CStr value, UInt start = 0) const;
		UInt LastIndexOf(CStr value, UInt start = Default) const;
		String SubString(UInt start, UInt length) const;
		StrPtrVec* Split(CStr delimiters) const;

		/* Public No-Const Functions */
		void Clear();
		void Reserve(UInt capacity);
		void Shrink();
		String& Append(CStr value);
		String& Append(String const & value);
		String& AppendLine(CStr value = String::Empty);
		String& AppendLine(String const & value);
		TChar* DrivePointer(UInt future_length);
		String& TrimLeft();
		String& TrimRight();
		String& Trim();
		Bool IsDigit();
		String& Overwrite(UInt start, CStr begin, CStr end);
		String& Replace(CStr oldValue, CStr newValue);
	};
}
