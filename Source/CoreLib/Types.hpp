#pragma once

#ifndef NULL
	#define NULL 0
#endif

#define DeletePtr(ptr) if(ptr) { delete(ptr); (ptr) = NULL; }

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
	#elif CoreTargetLinux
		typedef signed short Int16;
		typedef signed int Int32;
		typedef signed long long Int64;
		typedef unsigned short UInt16;
		typedef unsigned int UInt32;
		typedef unsigned long long UInt64;
	#endif

	#ifndef CoreTarget64Bits
		typedef Int32 Int;
		typedef UInt32 UInt;
		typedef Int32* IntPtr;
		typedef UInt32* UIntPtr;
	#else
		typedef Int64 Int;
		typedef UInt64 UInt;
		typedef Int64* IntPtr;
		typedef UInt64* UIntPtr;
	#endif

	typedef bool Bool;

	#if CoreTargetWin32 && UNICODE
		#define _Text(quote)L##quote
		#define Text(quote)_Text(quote)
		typedef wchar_t TChar;
	#else
		#define Text(quote)quote
		typedef char TChar;
	#endif

	typedef TChar const * CStr;

	#ifdef CoreTargetWin32
		#define NewLine Text("\r\n")
	#elif CoreTargetLinux
		#define NewLine Text("\n")
	#endif

	Int32 ToInt32(Int64 value);
	UInt32 ToUInt32(UInt64 value);
	Int ToInt(Int64 value);
	UInt ToUInt(UInt64 value);
}
