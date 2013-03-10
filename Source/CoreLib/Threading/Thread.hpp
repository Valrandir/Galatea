#pragma once
#include "../../Types.hpp"

namespace Core
{
	namespace Threading
	{
		typedef VoidPtr (*ThreadFonc)(VoidPtr threadParam);

		class Thread
		{
			public:
			virtual VoidPtr Join() = 0;
			virtual ~Thread(){}
		};

		Thread* CreateThread(ThreadFonc threadEntry, VoidPtr threadParam);
		//Thread* GetCurrentThread();
	}
}
