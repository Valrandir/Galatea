#pragma once
#include "../../Types.hpp"

namespace Core
{
	namespace System
	{
		namespace Threading
		{
			typedef VoidPtr (*ThreadFonc)(VoidPtr ThreadParam);

			class Thread
			{
				public:
				virtual VoidPtr Join() = 0;
				virtual ~Thread(){}
			};

			Thread* CreateThread(ThreadFonc ThreadEntry, VoidPtr ThreadParam);
		}
	}
}
