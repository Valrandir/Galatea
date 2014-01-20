#include "Window.Win32.hpp"

namespace Core
{
	namespace Display
	{
		WindowImpl::WindowImpl()
		{
			_window = new WindowBase(TEXT("Title"), 640, 480);
		}

		Bool WindowImpl::Update()
		{
			return _window ? _window->Update() : false;
		}

		void WindowImpl::Show()
		{
			_window->Show();
		}

		void WindowImpl::Close()
		{
			DeletePtr(_window);
		}

		#undef CreateWindow
		Window* CreateWindow()
		{
			return new WindowImpl();
		}
	}
}
