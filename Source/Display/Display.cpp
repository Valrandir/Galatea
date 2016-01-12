#include "Window.hpp"
#include "SDL/WindowSDL.hpp"

namespace Galatea
{
	namespace Display
	{
		Window* CreateWindow(const char* title, int width, int height)
		{
			return WindowSDL::Create(title, width, height);
		}
	}
}
