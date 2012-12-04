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
				ThreadFonc ThreadEntry;
				VoidPtr ThreadParam;
				VoidPtr ReturnValue;

				protected:
				IThread(ThreadFonc ThreadEntry, VoidPtr ThreadParam);

				public:
				void Execute();
				VoidPtr GetReturnValue();
				virtual VoidPtr Join() = 0;
				virtual ~IThread(){}
			};

			IThread* CreateThread(ThreadFonc ThreadEntry, VoidPtr ThreadParam);
		}
	}
}
