#pragma once

#ifndef NULL
	#define NULL 0
#endif

#define Delete(ptr) delete(ptr); (ptr) = NULL

namespace Core
{
	typedef void* VoidPtr;

	#if CoreTargetWin32 || CoreTargetWin64
		typedef signed __int16 Int16;
		typedef signed __int32 Int32;
		typedef signed __int64 Int64;
		typedef unsigned __int16 UInt16;
		typedef unsigned __int32 UInt32;
		typedef unsigned __int64 UInt64;
		#if CoreTargetWin32
			typedef Int32 IntPtr;
			typedef UInt32 UIntPtr;
		#elif CoreTargetWin64
			typedef Int64 IntPtr;
			typedef UInt64 UIntPtr;
		#endif
	#else
		typedef signed short Int16;
		typedef signed int Int32;
		typedef signed long long Int64;
		typedef unsigned short UInt16;
		typedef unsigned int UInt32;
		typedef unsigned long long UInt64;
		typedef Int32 IntPtr;
		typedef UInt32 UIntPtr;
	#endif

	#if (CoreTargetWin32 || CoreTargetWin64) && UNICODE
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
