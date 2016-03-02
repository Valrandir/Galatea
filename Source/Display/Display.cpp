#include "Display.hpp"
#include "Window.hpp"
#include "SDL/WindowSDL.hpp"

namespace Galatea
{
	namespace Display
	{
		Window* CreateWindow(const char* title, int width, int height)
		{
			WindowStyle style = WindowStyle::Caption | WindowStyle::SysMenu | WindowStyle::MinimizeBox | WindowStyle::MaximizeBox;
			return WindowSDL::Create(title, width, height, style);
		}

		Window* CreateWindow(const char* title, int width, int height, WindowStyle style)
		{
			return WindowSDL::Create(title, width, height, style);
		}
	}
}
