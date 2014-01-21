#pragma once
#include "../Types.hpp"

namespace Core
{
	namespace Display
	{
		class Window
		{
			public:
			typedef void (*OnKeydownCallback)(UInt32 key_code, VoidPtr param);

			virtual void Show() = 0;
			virtual Bool Update() = 0;
			virtual void Close() = 0;
			virtual void SetOnKeydownCallback(OnKeydownCallback proc, VoidPtr param) = 0;
			virtual ~Window() {}
		};

		Window* CreateWindow();
	};
}
