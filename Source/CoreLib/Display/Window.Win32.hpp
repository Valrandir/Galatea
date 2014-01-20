#pragma once
#include "Window.hpp"
#include "Win32/WindowBase.hpp"

namespace Core
{
	namespace Display
	{
		class WindowImpl : public Window
		{
			WindowBase* _window;

			public:
			WindowImpl();
			void Show();
			Bool Update();
			void Close();
		};
	}
}
