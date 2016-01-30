#include "SDL\WindowSDL.hpp"
#include "Window.hpp"

namespace Galatea
{
	namespace Display
	{
		Window::~Window(){}

		Window::OnKeyProc& Window::OnKeyEvent(void* userdata)
		{
			_on_key.userdata = userdata;
			return _on_key.proc;
		}

		Window::OnMouseUpProc& Window::OnMouseUpEvent(void* userdata)
		{
			_on_mouse_up.userdata = userdata;
			return _on_mouse_up.proc;
		}

		Window::OnMouseDownProc& Window::OnMouseDownEvent(void* userdata)
		{
			_on_mouse_down.userdata = userdata;
			return _on_mouse_down.proc;
		}

		Window::OnMouseMoveProc& Window::OnMouseMoveEvent(void* userdata)
		{
			_on_mouse_move.userdata = userdata;
			return _on_mouse_move.proc;
		}

		void Window::OnKey(Input::KeyEvent ke)
		{
			if(ke.key == Input::Keys::KeyEscape)
				Close();
			else
				if(_on_key.proc)
					_on_key.proc(ke, _on_key.userdata);
		}

		void Window::OnMouseUp(int button)
		{
			if(_on_mouse_up.proc)
				_on_mouse_up.proc(button, _on_mouse_up.userdata);
		}

		void Window::OnMouseDown(int button)
		{
			if(_on_mouse_down.proc)
				_on_mouse_down.proc(button, _on_mouse_down.userdata);
		}

		void Window::OnMouseMove(int x, int y)
		{
			if(_on_mouse_move.proc)
				_on_mouse_move.proc(x, y, _on_mouse_move.userdata);
		}
	}
}
