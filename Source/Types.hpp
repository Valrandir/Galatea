#pragma once

#define GALATEA_DELETE_PTR(ptr) if(ptr) { delete(ptr); (ptr) = nullptr; }

#if !defined(GALATEA_BUILD_SYS_WINDOWS) && !defined(GALATEA_BUILD_SYS_LINUX)
	#ifdef __linux__
		#define GALATEA_BUILD_SYS_LINUX
		#define GALATEA_BUILD_X64
	#else
		#define GALATEA_BUILD_SYS_WINDOWS
		#if _WIN64
			#define GALATEA_BUILD_X64
		#elif defined(_WIN32)
			#define GALATEA_BUILD_X86
		#endif
	#endif
#endif

#if !defined(GALATEA_BUILD_DEBUG) && !defined(GALATEA_BUILD_RELEASE)
	#ifdef _DEBUG
		#define GALATEA_BUILD_DEBUG
	#else
		#define GALATEA_BUILD_RELEASE
	#endif
#endif

namespace Galatea
{
	typedef bool Bool;
	typedef float Float;
	typedef double Double;
	typedef void Void;
	typedef void* VoidPtr;

	#ifdef GALATEA_BUILD_SYS_WINDOWS
		typedef signed __int8 Int8;
		typedef signed __int16 Int16;
		typedef signed __int32 Int32;
		typedef signed __int64 Int64;
		typedef unsigned __int8 UInt8;
		typedef unsigned __int16 UInt16;
		typedef unsigned __int32 UInt32;
		typedef unsigned __int64 UInt64;
	#elif GALATEA_BUILD_SYS_LINUX
		typedef signed char Int8;
		typedef signed short Int16;
		typedef signed int Int32;
		typedef signed long long Int64;
		typedef unsigned char UInt8;
		typedef unsigned short UInt16;
		typedef unsigned int UInt32;
		typedef unsigned long long UInt64;
	#endif

	#ifndef GALATEA_BUILD_X64
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

	Int32 ToInt32(Int64 value);
	UInt32 ToUInt32(UInt64 value);
	Int ToInt(Int64 value);
	UInt ToUInt(UInt64 value);
	Bool WithinInt32Limit(Int value);
	Bool WithinUInt32Limit(UInt value);

	#if defined(GALATEA_BUILD_SYS_WINDOWS) && defined(UNICODE)
		#define _Text(quote)L##quote
		#define Text(quote)_Text(quote)
		typedef wchar_t TChar;
		#define WIDE_CSTR
	#else
		#define Text(quote)quote
		typedef char TChar;
	#endif

	typedef TChar const * CStr;

	#ifdef GALATEA_BUILD_SYS_WINDOWS
		#define NewLine Text("\r\n")
	#elif GALATEA_BUILD_SYS_LINUX
		#define NewLine Text("\n")
	#endif
}
