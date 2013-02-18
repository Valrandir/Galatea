#pragma once
#include "../../Types.hpp"
#include "../../String/String.hpp"

namespace Core
{
	namespace System
	{
		namespace Storage
		{
			class File
			{
				public:
				static File* Create();
				static File* Open();
				static File* CreateOrOpen();

				virtual ~File(){}
			};
		}
	}
}
