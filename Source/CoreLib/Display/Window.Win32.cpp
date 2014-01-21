#include "Window.Win32.hpp"

namespace Core
{
	namespace Display
	{
		#undef CreateWindow
		Window* CreateWindow()
		{
			return new WindowImpl();
		}

		void WindowImpl::OnKeydown(unsigned int key_code, void* param)
		{
			WindowImpl& impl = *(WindowImpl*)param;
			impl._on_keydown_proc(key_code, impl._on_keydown_param);
		}

		WindowImpl::WindowImpl() : _on_keydown_proc(0)
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

		void WindowImpl::SetOnKeydownCallback(OnKeydownCallback proc, VoidPtr param)
		{
			_on_keydown_proc = proc;
			_on_keydown_param = param;
			_window->SetOnKeyDownCallback(proc ? OnKeydown : proc, this);
		}
	}
}
