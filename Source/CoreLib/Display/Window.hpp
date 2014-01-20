#pragma once
#include "../Types.hpp"

namespace Core
{
	namespace Display
	{
		class Window
		{
			public:
			virtual void Show() = 0;
			virtual Bool Update() = 0;
			virtual void Close() = 0;
			virtual ~Window() {}
		};

		Window* CreateWindow();
	};
}
