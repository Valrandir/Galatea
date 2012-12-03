#pragma once

#ifndef NULL
	#define NULL ((void*)0)
#endif

namespace Core
{
	typedef signed short Int16;
	typedef signed int Int32;
	typedef signed long long Int64;
	typedef unsigned short UInt16;
	typedef unsigned int UInt32;
	typedef unsigned long long UInt64;

	#if defined(CoreTargetWin32) && defined(UNICODE)
		#define Text(quote)L##quote
		typedef wchar_t Char;
		typedef wchar_t* String;
		typedef wchar_t const CChar;
		typedef wchar_t const * CString;
	#else
		#define Text(quote)quote
		typedef char Char;
		typedef char* String;
		typedef char const CChar;
		typedef char const * CString;
	#endif
}
