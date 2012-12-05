#pragma once

#define NULL 0
#define Delete(ptr) delete(ptr); (ptr) = NULL

namespace Core
{
	typedef void* VoidPtr;

	#ifdef CoreTargetWin32
		typedef signed __int16 Int16;
		typedef signed __int32 Int32;
		typedef signed __int64 Int64;
		typedef unsigned __int16 UInt16;
		typedef unsigned __int32 UInt32;
		typedef unsigned __int64 UInt64;
	#else
		typedef signed short Int16;
		typedef signed int Int32;
		typedef signed long long Int64;
		typedef unsigned short UInt16;
		typedef unsigned int UInt32;
		typedef unsigned long long UInt64;
	#endif

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
