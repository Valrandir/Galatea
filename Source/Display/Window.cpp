#include "SDL\WindowSDL.hpp"
#include "Window.hpp"

namespace Galatea
{
	namespace Display
	{
		Window* Window::Create(const char* title, int width, int height)
		{
			return new WindowSDL(title, width, height);
		}

		Window::~Window(){}

		Window::OnKeyProc& Window::OnKeyEvent(void* userdata)
		{
			_on_key.userdata = userdata;
			return _on_key.proc;
		}

		void Window::OnKey(KeyEvent ke)
		{
			if(_on_key.proc)
				_on_key.proc(ke, _on_key.userdata);
		}
	}
}
