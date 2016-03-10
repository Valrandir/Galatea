#include "Display.hpp"
#include "Window.hpp"
#include "SDL/WindowSDL.hpp"
#include "OpenGL/WindowGL.hpp"

namespace Galatea
{
	namespace Display
	{
		Window* CreateWindow(RendererImpl renderer, CStr title, int width, int height, WindowStyle style)
		{
			switch(renderer)
			{
				case RendererImpl::SDL: return WindowSDL::Create(title, width, height, style);
				case RendererImpl::OpenGL: return WindowGL::Create(title, width, height, style);
			}

			return nullptr;
		}

		Window* CreateWindow(RendererImpl renderer, CStr title, int width, int height)
		{
			WindowStyle style = WindowStyle::Caption | WindowStyle::SysMenu | WindowStyle::MinimizeBox | WindowStyle::MaximizeBox;
			return CreateWindow(renderer, title, width, height, style);
		}
	}
}
