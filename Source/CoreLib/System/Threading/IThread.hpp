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
				struct ThreadLink
				{
					ThreadFonc ThreadEntry;
					VoidPtr ThreadParam;
					VoidPtr ReturnValue;
				};

				private:
				ThreadLink Link;

				protected:
				IThread(ThreadLink Link);

				public:
				ThreadLink* GetLink();
				virtual void Join(VoidPtr* ReturnValue = 0) = 0;
				virtual ~IThread(){}
			};

			IThread* CreateThread(ThreadFonc ThreadEntry, VoidPtr ThreadParam);
		}
	}
}
