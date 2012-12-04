#pragma once
#include "../../Types.hpp"

#ifdef CoreTargetWin32
	#define ThreadFoncDef(FoncName) unsigned long __stdcall FoncName(void* ThreadParam)
#elif CoreTargetLinux
	#define ThreadFoncDef(FoncName) void*FoncName(void* ThreadParam)
#endif

namespace Core
{
	namespace System
	{
		namespace Threading
		{
			class IThread
			{
				public:
				virtual UInt32 Join() = 0;
				virtual ~IThread(){}
			};

			#ifdef CoreTargetWin32
				typedef unsigned long (__stdcall *ThreadFonc)(void* ThreadParam);
			#elif CoreTargetLinux
				typedef void* (*ThreadFonc)(void* ThreadParam);
			#endif

			IThread* CreateThread(ThreadFonc ThreadEntry, void* ThreadParam);
		}
	}
}
