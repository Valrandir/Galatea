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
				static File* Create(TChar const * fileName);
				static File* Open(TChar const * fileName);
				static File* CreateOrOpen(TChar const * fileName);

				File();
				File(File const &);
				File& operator=(File&);

				virtual ~File(){}
				void Close();
			};
		}
	}
}
