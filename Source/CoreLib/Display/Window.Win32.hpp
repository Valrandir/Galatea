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
			static void OnKeydown(unsigned int key_code, void* param);
			OnKeydownCallback _on_keydown_proc;
			void* _on_keydown_param;

			public:
			WindowImpl();
			void Show();
			Bool Update();
			void Close();
			void SetOnKeydownCallback(OnKeydownCallback proc, VoidPtr param);
		};
	}
}
