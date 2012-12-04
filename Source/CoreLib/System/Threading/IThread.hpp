#pragma once
#include "../../Types.hpp"

namespace Core
{
	namespace System
	{
		namespace Threading
		{
			typedef void* (*ThreadFonc)(void* ThreadParam);

			class IThread
			{
				public:
				struct ThreadLink
				{
					ThreadFonc ThreadEntry;
					void* ThreadParam;
					void* ReturnValue;
				};

				private:
				ThreadLink Link;

				protected:
				IThread(ThreadLink Link);

				public:
				ThreadLink* GetLink();
				virtual void Join(void** ReturnValue = 0) = 0;
				virtual ~IThread(){}
			};

			IThread* CreateThread(ThreadFonc ThreadEntry, void* ThreadParam);
		}
	}
}
