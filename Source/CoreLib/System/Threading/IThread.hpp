#pragma once
#include "../../Types.hpp"

namespace Core
{
	namespace System
	{
		namespace Threading
		{
			typedef VoidPtr (*ThreadFonc)(VoidPtr ThreadParam);

			class IThread
			{
				public:
				virtual VoidPtr Join() = 0;
				virtual ~IThread(){}
			};

			IThread* CreateThread(ThreadFonc ThreadEntry, VoidPtr ThreadParam);
		}
	}
}
