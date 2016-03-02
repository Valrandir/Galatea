#include "Display.hpp"
#include "Window.hpp"
#include "SDL/WindowSDL.hpp"
#include "OpenGL/WindowGL.hpp"

namespace Galatea
{
	namespace Display
	{
		Window* CreateWindow(CStr title, int width, int height)
		{
			//WindowStyle style = WindowStyle::Caption | WindowStyle::SysMenu | WindowStyle::MinimizeBox | WindowStyle::MaximizeBox;
			//return WindowGL::Create(title, width, height, style);
			WindowStyle style = WindowStyle::Caption | WindowStyle::SysMenu | WindowStyle::MinimizeBox | WindowStyle::MaximizeBox;
			return WindowSDL::Create(title, width, height, style);
		}

		Window* CreateWindow(CStr title, int width, int height, WindowStyle style)
		{
			//return WindowGL::Create(title, width, height, style);
			return WindowSDL::Create(title, width, height, style);
		}
	}
}
